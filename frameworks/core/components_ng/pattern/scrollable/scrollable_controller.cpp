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

#include "core/components_ng/pattern/scrollable/scrollable_controller.h"

namespace OHOS::Ace::NG {
bool ScrollableController::AnimateTo(
    const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    if (pattern->GetAxis() != Axis::NONE) {
        if (position.Unit() == DimensionUnit::PERCENT) {
            LOGW("not support percent dimension now");
            return false;
        }
        if (Positive(duration) || smooth) {
            pattern->AnimateTo(position.ConvertToPx(), duration, curve, smooth);
        } else {
            pattern->ScrollTo(position.ConvertToPx());
        }
        return true;
    }
    return false;
}

Offset ScrollableController::GetCurrentOffset() const
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN_NOLOG(pattern, Offset::Zero());
    auto axis = pattern->GetAxis();
    if (axis == Axis::NONE) {
        return Offset::Zero();
    }
    auto pxOffset = pattern->GetTotalOffset();
    auto vpOffset = Dimension(pxOffset, DimensionUnit::PX).ConvertToVp();
    return (axis == Axis::HORIZONTAL) ? Offset(vpOffset, 0) : Offset(0, vpOffset);
}

Axis ScrollableController::GetScrollDirection() const
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN_NOLOG(pattern, Axis::NONE);
    return pattern->GetAxis();
}
} // namespace OHOS::Ace::NG
