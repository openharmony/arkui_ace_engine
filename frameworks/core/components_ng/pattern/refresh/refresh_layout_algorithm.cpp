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

#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_algorithm.h"

#include "frameworks/base/utils/utils.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "frameworks/core/components_ng/property/measure_property.h"
#include "frameworks/core/components_ng/property/measure_utils.h"
#include "frameworks/core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

RefreshLayoutAlgorithm::RefreshLayoutAlgorithm() = default;

std::optional<SizeF> RefreshLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* /*layoutWrapper*/)
{
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }

    return contentConstraint.maxSize;
}

void RefreshLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    PerformLayout(layoutWrapper);

    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
}
// Called to perform layout render node and child.
void RefreshLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::TOP_LEFT;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    auto layoutProperty = AceType::DynamicCast<NG::RefreshLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    // Update child position.
    int32_t index = 0;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto paddingOffsetChild = paddingOffset;
        auto alignChild = align;
        if (index == layoutWrapper->GetTotalChildCount() - 2) {
            paddingOffsetChild += layoutProperty->GetShowTimeOffsetValue();
            alignChild = Alignment::TOP_CENTER;
        } else if (index == layoutWrapper->GetTotalChildCount() - 1) {
            paddingOffsetChild += layoutProperty->GetLoadingProcessOffsetValue();
            alignChild = Alignment::TOP_CENTER;
        }
        auto translate = Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetMarginFrameSize(), alignChild) +
                         paddingOffsetChild;
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        index++;
    }
}

} // namespace OHOS::Ace::NG
