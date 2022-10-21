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

    color_ = indexerLayoutProperty->GetColor().value_or(Color(INDEXER_LIST_COLOR));
    selectedColor_ = indexerLayoutProperty->GetSelectedColor().value_or(Color(INDEXER_LIST_ACTIVE_COLOR));
    popupColor_ = indexerLayoutProperty->GetPopupColor().value_or(Color(BUBBLE_FONT_COLOR));
    selectedBackgroundColor_ = indexerLayoutProperty->GetSelectedBackgroundColor()
        .value_or(Color(INDEXER_ACTIVE_BG_COLOR));
    popupBackground_ = indexerLayoutProperty->GetPopupBackground().value_or(Color(BUBBLE_BG_COLOR));
    usingPopup_ = indexerLayoutProperty->GetUsingPopup().value_or(false);
    TextStyle textStyle;
    selectedFont_ = indexerLayoutProperty->GetSelectedFont().value_or(textStyle);
    popupFont_ = indexerLayoutProperty->GetPopupFont().value_or(textStyle);
    font_ = indexerLayoutProperty->GetFont().value_or(textStyle);
    auto itemSize = indexerLayoutProperty->GetItemSize().value_or(Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
    itemSize_ = ConvertToPx(itemSize, layoutConstraint.scaleProperty, maxSize.Height()).value();
    alignStyle_ = indexerLayoutProperty->GetAlignStyle().value_or(NG::AlignStyle::RIGHT);

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
    
    auto childLayoutConstraint = indexerLayoutProperty->CreateChildConstraint();
    for (int32_t index = 0; index < itemCount_; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(childLayoutProperty);
        childLayoutConstraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(itemSizeRender_, itemSizeRender_));
        childLayoutProperty->UpdateAlignment(Alignment::CENTER);

        if (index == selected_) {
            childLayoutProperty->UpdateTextColor(selectedColor_);
            auto fontSize = selectedFont_.GetFontSize();
            childLayoutProperty->UpdateFontSize(fontSize);
            auto fontWeight = selectedFont_.GetFontWeight();
            childLayoutProperty->UpdateFontWeight(fontWeight);

            auto childFrameNode = childWrapper->GetHostNode();
            auto childRenderContext = childFrameNode->GetRenderContext();
            childRenderContext->BlendBgColor(selectedBackgroundColor_);

            Dimension radius = Dimension(NG::BOX_RADIUS);
            BorderRadiusProperty borderRadius { radius, radius, radius, radius };
            childRenderContext->UpdateBorderRadius(borderRadius);
        } else {
            childLayoutProperty->UpdateTextColor(color_);
            auto fontSize = font_.GetFontSize();
            childLayoutProperty->UpdateFontSize(fontSize);
            auto fontWeight = font_.GetFontWeight();
            childLayoutProperty->UpdateFontWeight(fontWeight);

            auto childFrameNode = childWrapper->GetHostNode();
            auto childRenderContext = childFrameNode->GetRenderContext();
            childRenderContext->ResetBlendBgColor();

            Dimension radius = Dimension(NG::BOX_RADIUS);
            BorderRadiusProperty borderRadius { radius, radius, radius, radius };
            childRenderContext->UpdateBorderRadius(borderRadius);
        }
        childWrapper->Measure(childLayoutConstraint);
    }

    if (usingPopup_) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(itemCount_);
        CHECK_NULL_VOID(childWrapper);
        childLayoutConstraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(NG::BUBBLE_BOX_SIZE, NG::BUBBLE_BOX_SIZE));
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
    
    auto layoutConstraint = indexerLayoutProperty->GetContentLayoutConstraint().value();
    auto selfIdealSize = layoutConstraint.selfIdealSize;
    constexpr float half = 0.5f;
    if (selfIdealSize.Width().has_value() && selfIdealSize.Width().value() >= size.Width()) {
       left = left + half * (selfIdealSize.Width().value() - size.Width());
    }
    if (selfIdealSize.Height().has_value() && selfIdealSize.Height().value() >= size.Height()) {
        top = top + half * (selfIdealSize.Height().value() - size.Height());
    }
    auto paddingOffset = OffsetF(left, top);

    float popupPositionX = 0.0f;
    float popupPositionY = 0.0f;
    if (indexerLayoutProperty->GetPopupPositionX().has_value()) {
        popupPositionX = indexerLayoutProperty->GetPopupPositionX().value();
    } else {
        if (alignStyle_ == NG::AlignStyle::LEFT) {
            popupPositionX = -NG::BUBBLE_POSITION_X + itemSizeRender_ * half;
        } else {
            popupPositionX = NG::BUBBLE_POSITION_X + itemSizeRender_ * half;
        }
    }
    popupPositionY = indexerLayoutProperty->GetPopupPositionY().value_or(NG::BUBBLE_POSITION_Y);
    
    for (int32_t index = 0; index < itemCount_; index++) {
        auto offset = paddingOffset;
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            LOGI("indexerLayoutAlgorithm wrapper is out of boundary");
            continue;
        }
        offset = offset + OffsetF(0, index * itemSizeRender_);
        childWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);

        auto childNode = childWrapper->GetHostNode();
        CHECK_NULL_VOID(childNode);

        childWrapper->Layout();
    }

    if (usingPopup_) {
        auto offset = paddingOffset;
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(itemCount_);
        if (!childWrapper) {
            LOGI("indexerLayoutAlgorithm wrapper is out of boundary");
            return;
        }

        OffsetF bubblePosition = OffsetF(popupPositionX, popupPositionY);
        offset = offset + bubblePosition;
        childWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);

        auto childNode = childWrapper->GetHostNode();
        CHECK_NULL_VOID(childNode);

        childWrapper->Layout();
    }
}
} // namespace OHOS::Ace::NG
