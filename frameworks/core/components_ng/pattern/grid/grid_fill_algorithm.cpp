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

#include "core/components_ng/pattern/grid/grid_fill_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/scroll_window_adapter.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_utils.h"

namespace OHOS::Ace::NG {
namespace {
// TODO: need to merge it with grid layoutAlgorithm.
LayoutConstraintF CreateChildConstraint(
    const SizeF& contentSize, Axis axis, GridLayoutProperty* gridLayoutProperty, int32_t crossSpan)
{
    auto itemMainSize = Infinity<float>();
    auto gapLength = GridUtils::GetCrossGap(AceType::Claim(gridLayoutProperty), contentSize, axis);
    auto crossLength = axis == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width();
    auto crossCount = gridLayoutProperty->GetCrossCount();
    auto spanLength = (crossLength - (crossCount - 1) * gapLength) / crossCount;
    auto itemCrossSize = crossSpan * spanLength + gapLength * (crossSpan - 1);

    SizeF itemIdealSize =
        gridLayoutProperty->IsVertical() ? SizeF(itemCrossSize, itemMainSize) : SizeF(itemMainSize, itemCrossSize);
    auto itemConstraint = gridLayoutProperty->CreateChildConstraint();

    // The percent size of GridItem is based on the fraction size, for e.g., if a GridItem has width of "50%" in Grid
    // configured with columnsTemplate = "1fr 1fr", rowsTemplate = "1fr 1fr",
    // then the GridItem width = [width of 1fr] * 50%,
    // [itemFractionCount] is now only in direction of cross axis
    float widthPercentBase = itemCrossSize;
    float heightPercentBase = itemConstraint.percentReference.Height();
    if (axis == Axis::VERTICAL) {
        itemConstraint.percentReference = SizeF(widthPercentBase, itemConstraint.percentReference.Height());
    } else {
        itemConstraint.percentReference = SizeF(itemConstraint.percentReference.Width(), heightPercentBase);
    }
    itemConstraint.maxSize = itemIdealSize;
    itemConstraint.UpdateIllegalSelfMarginSizeWithCheck(axis == Axis::VERTICAL
                                                            ? OptionalSizeF(itemCrossSize, std::nullopt)
                                                            : OptionalSizeF(std::nullopt, itemCrossSize));
    return itemConstraint;
}
} // namespace

RectF GridFillAlgorithm::CalcMarkItemRect(
    const SizeF& viewPort, Axis axis, FrameNode* node, int32_t index, const std::optional<OffsetF>& slidingOffset)
{
    // measure item to get real size.
    // TODO: Get the realy cross span in GridItem.
    auto layoutConstraint = CreateChildConstraint(viewPort, axis, layoutProperty_, 1);
    node->Measure(layoutConstraint);
    auto offset = slidingOffset.has_value() ? node->GetGeometryNode()->GetMarginFrameOffset() + slidingOffset.value()
                                            : node->GetGeometryNode()->GetMarginFrameOffset();
    auto size = node->GetGeometryNode()->GetMarginFrameSize();
    return { offset, size };
}

RectF GridFillAlgorithm::CalcItemRectAfterMarkItem(
    const SizeF& viewPort, Axis axis, FrameNode* node, int32_t index, const RectF& markItem)
{
    // measure item to get real size.
    // TODO: Get the realy cross span in GridItem.
    auto layoutConstraint = CreateChildConstraint(viewPort, axis, layoutProperty_, 1);
    node->Measure(layoutConstraint);
    auto crossCount = layoutProperty_->GetCrossCount();
    if (index % crossCount == 0) {
        // new line.
        auto mainGap = GridUtils::GetMainGap(AceType::Claim(layoutProperty_), viewPort, axis);
        OffsetF offset = axis == Axis::VERTICAL ? OffsetF(0.0f, markItem.Bottom() + mainGap)
                                                : OffsetF(markItem.Right() + mainGap, 0.0f);
        return { offset, node->GetGeometryNode()->GetMarginFrameSize() };
    }
    auto crossGap = GridUtils::GetCrossGap(AceType::Claim(layoutProperty_), viewPort, axis);
    OffsetF offset = axis == Axis::VERTICAL ? OffsetF(markItem.Right() + crossGap, markItem.Top())
                                            : OffsetF(markItem.Left(), markItem.Bottom() + crossGap);
    return { offset, node->GetGeometryNode()->GetMarginFrameSize() };
}

RectF GridFillAlgorithm::CalcItemRectBeforeMarkItem(
    const SizeF& viewPort, Axis axis, FrameNode* node, int32_t index, const RectF& markItem)
{
    // measure item to get real size.
    // TODO: Get the realy cross span in GridItem.
    auto layoutConstraint = CreateChildConstraint(viewPort, axis, layoutProperty_, 1);
    node->Measure(layoutConstraint);
    auto crossCount = layoutProperty_->GetCrossCount();
    auto size = node->GetGeometryNode()->GetMarginFrameSize();
    if (index % crossCount == crossCount - 1) {
        // new line.
        auto mainGap = GridUtils::GetMainGap(AceType::Claim(layoutProperty_), viewPort, axis);
        OffsetF offset = axis == Axis::VERTICAL
                             ? OffsetF(viewPort.Width() - size.Width(), markItem.Top() - mainGap - size.Height())
                             : OffsetF(markItem.Left() - mainGap - size.Width(), viewPort.Height() - size.Height());
        return { offset, size };
    }
    auto crossGap = GridUtils::GetCrossGap(AceType::Claim(layoutProperty_), viewPort, axis);
    OffsetF offset = axis == Axis::VERTICAL ? OffsetF(markItem.Left() - crossGap - size.Width(), markItem.Top())
                                            : OffsetF(markItem.Left(), markItem.Top() - crossGap - size.Height());
    return { offset, size };
}

} // namespace OHOS::Ace::NG