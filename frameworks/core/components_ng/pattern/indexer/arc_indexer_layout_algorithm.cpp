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

#include "core/components_ng/pattern/indexer/arc_indexer_layout_algorithm.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/indexer/arc_indexer_pattern.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void ArcIndexerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<ArcIndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    LayoutConstraintF layoutConstraint;
    if (layoutProperty->GetLayoutConstraint().has_value()) {
        layoutConstraint = layoutProperty->GetLayoutConstraint().value();
    }
    auto itemSize = layoutProperty->GetItemSize().value_or(Dimension(ARC_INDEXER_ITEM_SIZE, DimensionUnit::VP));
    itemSize_ = ConvertToPx(itemSize, layoutConstraint.scaleProperty, layoutConstraint.maxSize.Height()).value();
    auto selfIdealSize = layoutConstraint.selfIdealSize;
    auto actualWidth = selfIdealSize.Width().has_value()
                           ? selfIdealSize.Width().value()
                           : Dimension(ARC_INDEXER_SIZE, DimensionUnit::VP).ConvertToPx();
    auto actualHeight = selfIdealSize.Height().has_value()
                            ? selfIdealSize.Height().value()
                            : Dimension(ARC_INDEXER_SIZE, DimensionUnit::VP).ConvertToPx();
    actualSize_ = actualWidth > actualHeight ? actualHeight : actualWidth;
    layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(actualWidth, actualHeight));
    MeasureArc(layoutWrapper);

    auto childCount = layoutWrapper->GetTotalChildCount();
    if (layoutProperty->GetIsPopupValue(false)) {
        MeasurePopup(layoutWrapper, childCount);
        childCount--;
    }
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    for (int32_t index = 0; index < childCount; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        childLayoutConstraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(itemSize_, itemSize_));
        childWrapper->Measure(childLayoutConstraint);
    }
}

void ArcIndexerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = DynamicCast<ArcIndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto childCount = layoutWrapper->GetTotalChildCount();
    if (layoutProperty->GetIsPopupValue(false)) {
        const auto& child = layoutWrapper->GetChildByIndex(childCount - 1);
        CHECK_NULL_VOID(child);
        auto offset = GetPositionOfPopupNode(layoutWrapper);
        child->GetHostNode()->GetRenderContext()->UpdatePosition(offset);
        child->Layout();
        childCount -= 1;
    }
    for (int32_t i = 0; i < childCount; i++) {
        const auto& child = layoutWrapper->GetChildByIndex(i);
        CHECK_NULL_VOID(child);
        auto offset = CalcArcItemPosition(i);
        child->GetHostNode()->GetRenderContext()->UpdatePosition(offset);
        child->Layout();
    }
}

OffsetT<Dimension> ArcIndexerLayoutAlgorithm::CalcArcItemPosition(int32_t index)
{
    Offset position;
    float itemAngle = (startAngle_ + stepAngle_ * index) * M_PI / HALF_CIRCLE_ANGLE;
    position.SetX(arcCenter_.GetX() + arcRadius_ * cos(itemAngle) - itemRadius_);
    position.SetY(arcCenter_.GetY() + arcRadius_ * sin(itemAngle) - itemRadius_);
    auto offset = OffsetT<Dimension>(Dimension(position.GetX()), Dimension(position.GetY()));
    return offset;
}

OffsetT<Dimension> ArcIndexerLayoutAlgorithm::GetPositionOfPopupNode(
    LayoutWrapper* layoutWrapper)
{
    auto bubbleSize = Dimension(ARC_BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto positionX = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() * HALF - bubbleSize * HALF;
    auto positionY = Dimension(ARC_BUBBLE_POSITION_Y, DimensionUnit::VP).ConvertToPx();
    return OffsetT<Dimension>(Dimension(positionX), Dimension(positionY));
}

void ArcIndexerLayoutAlgorithm::MeasurePopup(LayoutWrapper* layoutWrapper, uint32_t childCount)
{
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(childCount - 1);
    CHECK_NULL_VOID(childWrapper);
    auto childLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(childWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(childLayoutProperty);
    auto layoutConstraint = childLayoutProperty->GetLayoutConstraint();
    layoutConstraint->Reset();
    childWrapper->Measure(layoutConstraint);
}

void ArcIndexerLayoutAlgorithm::MeasureArc(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = DynamicCast<ArcIndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto positionX = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() * HALF;
    auto positionY = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() * HALF;
    arcCenter_.SetX(positionX);
    arcCenter_.SetY(positionY);

    itemRadius_ = itemSize_ * HALF ;
    arcRadius_ = positionX < positionY ? positionX - itemRadius_: positionY - itemRadius_;
    stepAngle_ = DOUBLE * atan2f(itemRadius_, arcRadius_) * HALF_CIRCLE_ANGLE / M_PI;
    auto autoCollapse = layoutProperty->GetAutoCollapse().value_or(false);
    if (autoCollapse && fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        fullCount_ += 1;
    }
    if (stepAngle_ * fullCount_ > FULL_CIRCLE_ANGLE) {
        stepAngle_ = FULL_CIRCLE_ANGLE / fullCount_;
    }
    if (fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        startAngle_ = -stepAngle_ * ARC_INDEXER_COLLAPSE_ITEM_COUNT * HALF;
    } else {
        startAngle_ = -stepAngle_ * fullCount_ * HALF + stepAngle_* HALF;
    }

    sweepAngle_ = stepAngle_ * (itemCount_ - 1);
}

} // namespace OHOS::Ace::NG
