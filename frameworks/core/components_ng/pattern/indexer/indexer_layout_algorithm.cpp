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

#include "core/components_ng/pattern/indexer/indexer_layout_algorithm.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5;
}

void IndexerLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(indexerLayoutProperty);
    LayoutConstraintF layoutConstraint;
    if (indexerLayoutProperty->GetLayoutConstraint().has_value()) {
        layoutConstraint = indexerLayoutProperty->GetLayoutConstraint().value();
    }
    auto indexerItemSize = Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP);
    auto itemSize = indexerLayoutProperty->GetItemSize().value_or(indexerItemSize);
    if (GreatNotEqual(itemSize.ConvertToPx(), 0.0)) {
        itemSize_ = ConvertToPx(itemSize, layoutConstraint.scaleProperty, layoutConstraint.maxSize.Height()).value();
    } else {
        itemSize_ = 0.0f;
    }
    auto padding = frameNode->GetLayoutProperty()->CreatePaddingAndBorder();
    auto verticalPadding = (padding.top.value_or(0) + padding.bottom.value_or(0));
    auto horizontalPadding = padding.left.value_or(0.0f) + padding.right.value_or(0.0f);
    auto contentWidth = itemSize_ + horizontalPadding;
    auto contentHeight = itemCount_ * itemSize_ + verticalPadding;
    auto selfIdealSize = layoutConstraint.selfIdealSize;
    auto actualWidth = selfIdealSize.Width().has_value() ? selfIdealSize.Width().value() :
        std::clamp(contentWidth, 0.0f, layoutConstraint.maxSize.Width());
    auto actualHeight = selfIdealSize.Height().has_value() ? selfIdealSize.Height().value() :
        std::clamp(contentHeight, 0.0f, layoutConstraint.maxSize.Height());
    itemWidth_ = GreatOrEqual(actualWidth - horizontalPadding, 0.0f) ? actualWidth - horizontalPadding : 0.0f;
    itemSizeRender_ =
        GreatOrEqual(actualHeight - verticalPadding, 0.0f) ? (actualHeight - verticalPadding) / itemCount_ : 0.0f;
    auto childLayoutConstraint = indexerLayoutProperty->CreateChildConstraint();
    for (int32_t index = 0; index < itemCount_; index++) {
        auto child = frameNode->GetFrameNodeByIndex(index);
        CHECK_NULL_VOID(child);
        auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(child->GetLayoutProperty());
        CHECK_NULL_VOID(childLayoutProperty);
        childLayoutConstraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(itemWidth_, itemSizeRender_));
        childLayoutProperty->UpdateAlignment(Alignment::CENTER);
        child->Measure(childLayoutConstraint);
    }
    frameNode->GetGeometryNode()->SetFrameSize(SizeF(actualWidth, actualHeight));
}

void IndexerLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(indexerLayoutProperty);

    auto padding = frameNode->GetLayoutProperty()->CreatePaddingAndBorder();
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);

    auto indexerWidth = frameNode->GetGeometryNode()->GetFrameSize().Width();
    auto indexerHeight = frameNode->GetGeometryNode()->GetFrameSize().Height();

    auto firstChild = frameNode->GetFrameNodeByIndex(0);
    CHECK_NULL_VOID(firstChild);
    auto childWidth = firstChild->GetGeometryNode()->GetFrameSize().Width();
    auto childHeight = firstChild->GetGeometryNode()->GetFrameSize().Height();
    auto originMarginLeft = (indexerWidth - childWidth) * HALF;
    auto adjustMarginLeft = left < originMarginLeft ? originMarginLeft : left;
    auto originMarginTop = (indexerHeight - childHeight * itemCount_) * HALF;
    auto adjustMarginTop = top < originMarginTop ? originMarginTop : top;
    auto marginOffset = OffsetF(adjustMarginLeft, adjustMarginTop);
    for (int32_t index = 0; index < itemCount_; index++) {
        auto child = frameNode->GetFrameNodeByIndex(index);
        CHECK_NULL_VOID(child);
        auto layoutProperty = child->GetLayoutProperty();
        CHECK_NULL_VOID(child);
        child->GetGeometryNode()->SetMarginFrameOffset(marginOffset);
        child->Layout();
        marginOffset = marginOffset + OffsetF(0, itemSizeRender_);
    }
}
} // namespace OHOS::Ace::NG
