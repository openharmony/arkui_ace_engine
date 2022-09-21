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

#include "base/log/ace_trace.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_view.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void IndexerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(indexerLayoutProperty);
    
    if (indexerLayoutProperty->GetArrayValue().has_value()) {
        arrayValue_ = indexerLayoutProperty->GetArrayValue().value();
        itemCount_ = arrayValue_.size();
    }
    if (!isInitialized_ && indexerLayoutProperty->GetSelected().has_value()) {
        selected_ = indexerLayoutProperty->GetSelected().value();
    }
    isInitialized_ = true;

    LayoutConstraintF layoutConstraint;
    if (indexerLayoutProperty->GetLayoutConstraint().has_value()) {
        layoutConstraint = indexerLayoutProperty->GetLayoutConstraint().value();
    }
    SizeF maxSize = layoutConstraint.maxSize;
    
    color_ = indexerLayoutProperty->GetColor().value_or(Color::BLACK);
    selectedColor_ = indexerLayoutProperty->GetSelectedColor().value_or(Color::BLACK);
    popupColor_ = indexerLayoutProperty->GetPopupColor().value_or(Color::BLACK);
    selectedBackgroundColor_ = indexerLayoutProperty->GetSelectedBackgroundColor().value_or(Color::BLACK);
    popupBackground_ = indexerLayoutProperty->GetPopupBackground().value_or(Color::BLACK);
    usingPopup_ = indexerLayoutProperty->GetUsingPopup().value_or(false);
    TextStyle textStyle;
    selectedFont_ = indexerLayoutProperty->GetSelectedFont().value_or(textStyle);
    popupFont_ = indexerLayoutProperty->GetPopupFont().value_or(textStyle);
    font_ = indexerLayoutProperty->GetFont().value_or(textStyle);
    auto itemSize = indexerLayoutProperty->GetItemSize().value_or(Dimension(0));
    itemSize_ = ConvertToPx(itemSize, layoutConstraint.scaleProperty, maxSize.Height()).value();
    alignStyle_ = indexerLayoutProperty->GetAlignStyle().value_or(V2::AlignStyle::RIGHT);
    
    if (itemCount_ <= 0) {
        LOGE("AlphabetIndexer arrayValue size is less than 0");
        return;
    }
    if (NearZero(itemSize_)) {
        LOGE("AlphabetIndexer itemSize is near zero");
        return;
    }

    if (LessOrEqual(itemCount_ * itemSize_, maxSize.Height())) {
        itemSizeRender_ = itemSize_;
    } else {
        itemSizeRender_ = maxSize.Height() / itemCount_;
    }
    // TODO:移动到onModifyDone
    auto childLayoutConstraint = indexerLayoutProperty->CreateChildConstraint();
    for (int32_t index = 0; index < itemCount_; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(childLayoutProperty);
        childLayoutConstraint.UpdateSelfIdealSizeWithCheck(OptionalSizeF(itemSizeRender_, itemSizeRender_));
        childLayoutProperty->UpdateAlignment(Alignment::CENTER);
        
        childLayoutProperty->UpdateTextColor(color_);
        auto fontSize = font_.GetFontSize();
        childLayoutProperty->UpdateFontSize(fontSize);
        auto fontWeight = font_.GetFontWeight();
        childLayoutProperty->UpdateFontWeight(fontWeight);

        auto childFrameNode = childWrapper->GetHostNode();
        auto childRenderContext = childFrameNode->GetRenderContext();
        childRenderContext->BlendBgColor(backgroundColor_);
            
        Dimension radius = Dimension(BOX_RADIUS);
        BorderRadiusProperty borderRadius { radius, radius, radius, radius };
        childRenderContext->UpdateBorderRadius(borderRadius);
        
        childWrapper->Measure(childLayoutConstraint);
    }

    if (usingPopup_) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(itemCount_);
        CHECK_NULL_VOID(childWrapper);
        auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(childLayoutProperty);
        
        childLayoutConstraint.UpdateSelfIdealSizeWithCheck(OptionalSizeF(BUBBLE_BOX_SIZE, BUBBLE_BOX_SIZE));
        childLayoutProperty->UpdateAlignment(Alignment::CENTER);
        childLayoutProperty->UpdateContent(arrayValue_[selected_]);
        childLayoutProperty->UpdateTextColor(popupColor_);
        auto fontSize = popupFont_.GetFontSize();
        childLayoutProperty->UpdateFontSize(fontSize);
        auto fontWeight = popupFont_.GetFontWeight();
        childLayoutProperty->UpdateFontWeight(fontWeight);
        
        auto childFrameNode = childWrapper->GetHostNode();
        auto childRenderContext = childFrameNode->GetRenderContext();
        childRenderContext->BlendBgColor(popupBackground_);

        Dimension radius = Dimension(BUBBLE_BOX_RADIUS);
        BorderRadiusProperty borderRadius { radius, radius, radius, radius };
        childRenderContext->UpdateBorderRadius(borderRadius);
        
        childWrapper->Measure(childLayoutConstraint);
    }
    auto size = SizeF(itemSizeRender_, itemSizeRender_ * itemCount_);
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(left + size.Width(), top + size.Height()));
    return;
}

void IndexerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(indexerLayoutProperty);
    
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    for (int32_t index = 0; index < itemCount_; index++) {
        auto offset = paddingOffset;
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            LOGI("indexerLayoutAlgorithm wrapper is out of boundary");
            continue;
        }
        offset = offset + OffsetF(0, index * itemSizeRender_);
        childWrapper->GetGeometryNode()->SetFrameOffset(offset);
        
        auto childNode = childWrapper->GetHostNode();
        CHECK_NULL_VOID(childNode);
        
        childWrapper->Layout(parentOffset);
    }

    if (usingPopup_) {
        auto offset = paddingOffset;
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(itemCount_);
        if (!childWrapper) {
            LOGI("indexerLayoutAlgorithm wrapper is out of boundary");
            return;
        }

        OffsetF bubblePosition;
        if (alignStyle_ == V2::AlignStyle::RIGHT) {
            bubblePosition = OffsetF(-BUBBLE_POSITION_X, BUBBLE_POSITION_Y);
        } else {
            bubblePosition = OffsetF(BUBBLE_POSITION_X + itemSizeRender_, BUBBLE_POSITION_Y);
        }
        offset = offset + bubblePosition;
        childWrapper->GetGeometryNode()->SetFrameOffset(offset);
        
        auto childNode = childWrapper->GetHostNode();
        CHECK_NULL_VOID(childNode);
        
        childWrapper->Layout(parentOffset);
    }
}
} // namespace OHOS::Ace::NG
