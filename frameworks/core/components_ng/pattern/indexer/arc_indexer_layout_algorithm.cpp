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
    itemSize_ = ConvertToPx(itemSize, layoutConstraint.scaleProperty, layoutConstraint.maxSize.Height())
                    .value_or(Dimension(ARC_INDEXER_ITEM_SIZE, DimensionUnit::VP).ConvertToPx());
    auto selfIdealSize = layoutConstraint.selfIdealSize;
    auto actualWidth = selfIdealSize.Width().has_value()
                           ? selfIdealSize.Width().value()
                           : Dimension(ARC_INDEXER_SIZE, DimensionUnit::VP).ConvertToPx();
    auto actualHeight = selfIdealSize.Height().has_value()
                            ? selfIdealSize.Height().value()
                            : Dimension(ARC_INDEXER_SIZE, DimensionUnit::VP).ConvertToPx();
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        auto isMainMatchParent =
            (layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH)
                == LayoutCalPolicy::MATCH_PARENT);
        auto isCrossMatchParent =
            (layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH)
                == LayoutCalPolicy::MATCH_PARENT);

        // When the width parameter is MATCH_PARENT, set the width to be equal to the parent's width.
        if (isMainMatchParent) {
            auto parentMainSize = GetMainAxisSize(layoutConstraint.parentIdealSize, Axis::VERTICAL);
            if (parentMainSize) {
                actualHeight = parentMainSize.value();
            }
        }

        // When the height parameter is MATCH_PARENT, set the height to be equal to the parent's height.
        if (isCrossMatchParent) {
            auto parentCrossSize = GetCrossAxisSize(layoutConstraint.parentIdealSize, Axis::VERTICAL);
            if (parentCrossSize) {
                actualWidth = parentCrossSize.value();
            }
        }
    }
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
        auto offset = CalcArcItemPosition(layoutWrapper, i);
        child->GetHostNode()->GetRenderContext()->UpdatePosition(offset);
        child->Layout();
    }
}

OffsetT<Dimension> ArcIndexerLayoutAlgorithm::CalcArcItemPosition(LayoutWrapper* layoutWrapper, int32_t index)
{
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingWithoutBorder();
    float itemAngle = (startAngle_ + stepAngle_ * index) * M_PI / HALF_CIRCLE_ANGLE;
    auto positionX = arcCenter_.GetX() + arcRadius_ * cos(itemAngle) - itemRadius_ - padding.left.value_or(0);
    auto positionY = arcCenter_.GetY() + arcRadius_ * sin(itemAngle) - itemRadius_ - padding.top.value_or(0);
    return OffsetT<Dimension>(Dimension(positionX), Dimension(positionY));
}

OffsetT<Dimension> ArcIndexerLayoutAlgorithm::GetPositionOfPopupNode(LayoutWrapper* layoutWrapper)
{
    auto bubbleSize = Dimension(ARC_BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingWithoutBorder();
    auto popupDistance = Dimension(ARC_BUBBLE_POSITION_Y, DimensionUnit::VP).ConvertToPx();
    auto positionX = arcCenter_.GetX() - bubbleSize * HALF - padding.left.value_or(0);
    auto positionY = arcCenter_.GetY() - arcRadius_ - itemRadius_ +  popupDistance - padding.left.value_or(0);
    return OffsetT<Dimension>(Dimension(positionX), Dimension(positionY));
}

void ArcIndexerLayoutAlgorithm::MeasurePopup(LayoutWrapper* layoutWrapper, uint32_t childCount)
{
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(childCount - 1);
    CHECK_NULL_VOID(childWrapper);
    auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(childLayoutProperty);
    auto layoutConstraint = childLayoutProperty->GetLayoutConstraint();
    layoutConstraint->Reset();
    childWrapper->Measure(layoutConstraint);
}

void ArcIndexerLayoutAlgorithm::MeasureArc(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = DynamicCast<ArcIndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto width = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto height = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();

    const auto& paddingAndBorder = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorderWithDefault(0, 0, 0, 0);
    auto verticalPadding = paddingAndBorder.top.value_or(0) + paddingAndBorder.bottom.value_or(0);
    auto horizontalPadding = paddingAndBorder.left.value_or(0.0f) + paddingAndBorder.right.value_or(0.0f);
    auto centerX = (width - horizontalPadding) * HALF + paddingAndBorder.left.value_or(0);
    auto centerY = (height - verticalPadding) * HALF + paddingAndBorder.top.value_or(0);
    arcCenter_.SetX(centerX);
    arcCenter_.SetY(centerY);

    itemRadius_ = itemSize_ * HALF ;
    if (width - horizontalPadding < height - verticalPadding) {
        arcRadius_ = width * HALF - itemRadius_ - horizontalPadding * HALF;
    } else {
        arcRadius_ = height * HALF - itemRadius_ - verticalPadding * HALF;
    }

    stepAngle_ = DOUBLE * atan2f(itemRadius_, arcRadius_) * HALF_CIRCLE_ANGLE / M_PI;
    auto autoCollapse = layoutProperty->GetAutoCollapse().value_or(true);
    if (autoCollapse && fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        fullCount_ += 1;
    }
    if (fullCount_ > ARC_INDEXER_ITEM_MAX_COUNT) {
        fullCount_ = ARC_INDEXER_ITEM_MAX_COUNT + 1;
    }
    if (stepAngle_ * fullCount_ > FULL_CIRCLE_ANGLE) {
        stepAngle_ = FULL_CIRCLE_ANGLE / fullCount_;
    }
    if (fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        startAngle_ = -stepAngle_ * ARC_INDEXER_COLLAPSE_ITEM_COUNT * HALF;
    } else {
        startAngle_ = -stepAngle_ * fullCount_ * HALF + stepAngle_* HALF;
    }

    if (itemCount_ > 0) {
        sweepAngle_ = stepAngle_ * (itemCount_ - 1);
    }
}

} // namespace OHOS::Ace::NG
