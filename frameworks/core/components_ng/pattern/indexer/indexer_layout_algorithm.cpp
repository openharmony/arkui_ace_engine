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

void IndexerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
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
    if (itemCount_ <= 0) {
        LOGE("AlphabetIndexer arrayValue size is less than 0");
        return;
    }
    if (NearZero(itemSize_)) {
        LOGE("AlphabetIndexer itemSize is near zero");
        return;
    }
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto verticalPadding = (padding.top.value_or(0) + padding.bottom.value_or(0));
    auto horizontalPadding = padding.left.value_or(0.0f) + padding.right.value_or(0.0f);
    if (LessOrEqual(itemCount_ * itemSize_ + verticalPadding, layoutConstraint.maxSize.Height())) {
        itemSizeRender_ = itemSize_;
    } else {
        itemSizeRender_ = (layoutConstraint.maxSize.Height() - verticalPadding) / itemCount_;
    }

    auto childLayoutConstraint = indexerLayoutProperty->CreateChildConstraint();
    for (int32_t index = 0; index < itemCount_; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(childLayoutProperty);
        childLayoutConstraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(itemSizeRender_, itemSizeRender_));
        childLayoutProperty->UpdateAlignment(Alignment::CENTER);
        childWrapper->Measure(childLayoutConstraint);
    }

    auto indexerWidth = itemSizeRender_ + horizontalPadding;
    auto indexerHeight = itemSizeRender_ * itemCount_ + verticalPadding;
    auto selfIdealSize = layoutConstraint.selfIdealSize;
    if (selfIdealSize.Width().has_value() && selfIdealSize.Width().value() > indexerWidth) {
        indexerWidth = selfIdealSize.Width().value();
    }
    if (selfIdealSize.Height().has_value() && selfIdealSize.Height().value() > indexerHeight) {
        indexerHeight = selfIdealSize.Height().value();
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(indexerWidth, indexerHeight));
}

void IndexerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(indexerLayoutProperty);

    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto marginOffset = OffsetF(left, top);

    for (int32_t index = 0; index < itemCount_; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto layoutProperty = childWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(childWrapper);
        childWrapper->GetGeometryNode()->SetMarginFrameOffset(marginOffset);
        childWrapper->Layout();
        marginOffset = marginOffset + OffsetF(0, itemSizeRender_);
    }
}
} // namespace OHOS::Ace::NG
