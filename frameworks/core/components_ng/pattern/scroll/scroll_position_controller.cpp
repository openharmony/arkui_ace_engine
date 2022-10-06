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

#include "core/components_ng/pattern/scroll/scroll_position_controller.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void ScrollPositionController::JumpTo(int32_t index, int32_t source)
{
    auto pattern = scroll_.Upgrade();
    if (pattern) {
        auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
        if (scrollPattern) {
            LOGW("jumpTo is not supported now");
        }
    }
}

bool ScrollPositionController::AnimateTo(const Dimension& position, float duration, const RefPtr<Curve>& curve)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (scrollPattern && scrollPattern->GetAxis() != Axis::NONE) {
        // TODO: percent support
        if (position.Unit() == DimensionUnit::PERCENT) {
            LOGW("not support percent dimension now");
            return false;
        }
        scrollPattern->AnimateTo(-position.ConvertToPx(), duration, curve, true, nullptr);
        return true;
    }
    return false;
}

void ScrollPositionController::ScrollBy(double pixelX, double pixelY, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->ScrollBy(-pixelX, -pixelY, smooth);
}

double ScrollPositionController::GetCurrentPosition() const
{
    auto pattern = scroll_.Upgrade();
    if (!pattern) {
        return 0.0;
    }
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (!scrollPattern) {
        return 0.0;
    }
    return scrollPattern->GetCurrentPosition();
}

Axis ScrollPositionController::GetScrollDirection() const
{
    auto pattern = scroll_.Upgrade();
    if (pattern) {
        auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
        if (scrollPattern) {
            return scrollPattern->GetAxis();
        }
    }
    return Axis::NONE;
}

void ScrollPositionController::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (scrollPattern && scrollPattern->GetAxis() != Axis::NONE) {
        scrollPattern->ScrollToEdge(scrollEdgeType, smooth);
    }
}

void ScrollPositionController::ScrollPage(bool reverse, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (scrollPattern && scrollPattern->GetAxis() != Axis::NONE) {
        scrollPattern->ScrollPage(reverse, smooth);
    }
}

Offset ScrollPositionController::GetCurrentOffset() const
{
    auto pattern = scroll_.Upgrade();
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (!scrollPattern) {
        return Offset::Zero();
    }
    auto pxOffset = scrollPattern->GetCurrentOffset();
    // need to reverse the coordinate
    auto x = Dimension(-pxOffset.GetX(), DimensionUnit::PX);
    auto y = Dimension(-pxOffset.GetY(), DimensionUnit::PX);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, Offset::Zero());
    Offset offset(pipeline->ConvertPxToVp(x), pipeline->ConvertPxToVp(y));
    return offset;
}

} // namespace OHOS::Ace::NG
