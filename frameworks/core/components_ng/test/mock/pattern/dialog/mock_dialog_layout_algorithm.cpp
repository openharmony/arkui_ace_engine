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

#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"

namespace OHOS::Ace::NG {
void DialogLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    (void)gridCount_;
    (void)alignment_;
}

void DialogLayoutAlgorithm::ComputeInnerLayoutParam(LayoutConstraintF& innerLayout)
{
}

double DialogLayoutAlgorithm::GetMaxWidthBasedOnGridType(
    const RefPtr<GridColumnInfo>& info, GridSizeType type, DeviceType deviceType)
{
    return 0;
}

void DialogLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
}

OffsetF DialogLayoutAlgorithm::ComputeChildPosition(
    const SizeF& childSize, const RefPtr<DialogLayoutProperty>& prop, const SizeF& selfSize)
{
    return OffsetF(0, 0);
}

bool DialogLayoutAlgorithm::SetAlignmentSwitch(
    const SizeF& maxSize, const SizeF& childSize, OffsetF& topLeftPoint)
{
    return false;
}

void DialogLayoutAlgorithm::UpdateTouchRegion()
{
}
} // namespace OHOS::Ace::NG
