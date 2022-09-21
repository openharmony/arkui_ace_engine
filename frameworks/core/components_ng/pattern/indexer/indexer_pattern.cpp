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

#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_view.h"
#include "core?components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void IndexerPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    if (touchListener_) {
        return;
    }
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto indexerPattern = weak.Upgrade();
        CHECK_NULL_VOID(indexerPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            indexerPattern->OnTouchDown(info);
        }
        indexerPattern->SetIsTouch(true);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

bool IndexerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto indexerLayoutAlgorithm = DynamicCast<IndexerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(indexerLayoutAlgorithm, false);
    isInitialized_ = indexerLayoutAlgorithm->GetIsInitialized();
    selected_ = indexerLayoutAlgorithm->GetSelected();
    itemSizeRender_ = indexerLayoutAlgorithm->GetItemSizeRender();
    UpdateIndexer(dirty);
    return false;
}

void IndexerPattern::OnTouchDown(const TouchEventInfo& info)
{
    auto touchPosition = info.GetTouches().front().GetLocalLocation();
    if (itemSizeRender_ > 0) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto size = SizeF(itemSizeRender_, itemSizeRender_ * itemCount_);
        auto padding = layoutProperty->CreatePaddingAndBorder();
        MinusPaddingToSize(padding, size);
        auto top = padding.top.value_or(0.0f);

        int32_t itemIndex = static_cast<int32_t>(touchPosition.GetY() / itemSizeRender_);
        selected_ = itemIndex;

        auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
        CHECK_NULL_VOID(indexerEventHub);
        
        auto onSelected = indexerEventHub->GetOnSelected();
        if (onSelected && itemIndex >= 0 && itemIndex < itemCount_) {
            onSelected(itemIndex);
        }

        auto onRequestPopupData = indexerEventHub->GetOnRequestPopupData();
        if (onRequestPopupData && itemIndex >= 0 && itemIndex < itemCount_) {
            onRequestPopupData(itemIndex);
        }

        auto onPopupSelected = indexerEventHub->GetOnPopupSelected();
        if (onPopupSelected && itemIndex >= 0 && itemIndex < itemCount_) {
            onPopupSelected(itemIndex);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void IndexerPattern::UpdateIndexer(const RefPtr<LayoutWrapper>& layoutWrapper)
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

    auto color = indexerLayoutProperty->GetColor().value_or(Color::BLACK);
    auto selectedColor = indexerLayoutProperty->GetSelectedColor().value_or(Color::BLACK);
    auto popupColor = indexerLayoutProperty->GetPopupColor().value_or(Color::BLACK);
    auto selectedBackgroundColor = indexerLayoutProperty->GetSelectedBackgroundColor().value_or(Color::BLACK);
    auto popupBackground = indexerLayoutProperty->GetPopupBackground().value_or(Color::BLACK);
    auto usingPopup = indexerLayoutProperty->GetUsingPopup().value_or(false);
    TextStyle textStyle;
    auto selectedFont = indexerLayoutProperty->GetSelectedFont().value_or(textStyle);
    auto popupFont = indexerLayoutProperty->GetPopupFont().value_or(textStyle);
    auto font = indexerLayoutProperty->GetFont().value_or(textStyle);

    if (itemCount_ <= 0) {
        LOGE("AlphabetIndexer arrayValue size is less than 0");
        return;
    }

    auto childLayoutConstraint = indexerLayoutProperty->CreateChildConstraint();
    for (int32_t index = 0; index < itemCount_; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(childLayoutProperty);
        childLayoutConstraint.UpdateSelfIdealSizeWithCheck(OptionalSizeF(itemSizeRender_, itemSizeRender_));
        childLayoutProperty->UpdateAlignment(Alignment::CENTER);
        if (index == selected_) {
            childLayoutProperty->UpdateTextColor(selectedColor);
            auto fontSize = selectedFont.GetFontSize();
            childLayoutProperty->UpdateFontSize(fontSize);
            auto fontWeight = selectedFont.GetFontWeight();
            childLayoutProperty->UpdateFontWeight(fontWeight);

            auto childFrameNode = childWrapper->GetHostNode();
            auto childRenderContext = childFrameNode->GetRenderContext();
            childRenderContext->BlendBgColor(selectedBackgroundColor);
            
            Dimension radius = Dimension(BOX_RADIUS);
            BorderRadiusProperty borderRadius { radius, radius, radius, radius };
            childRenderContext->UpdateBorderRadius(borderRadius);
        } else {
            childLayoutProperty->UpdateTextColor(color);
            auto fontSize = font.GetFontSize();
            childLayoutProperty->UpdateFontSize(fontSize);
            auto fontWeight = font.GetFontWeight();
            childLayoutProperty->UpdateFontWeight(fontWeight);

            auto childFrameNode = childWrapper->GetHostNode();
            auto childRenderContext = childFrameNode->GetRenderContext();
            childRenderContext->BlendBgColor(Color::WHITE);

            Dimension radius = Dimension(BOX_RADIUS);
            BorderRadiusProperty borderRadius { radius, radius, radius, radius };
            childRenderContext->UpdateBorderRadius(borderRadius);
        }
    }
    if (usingPopup) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(itemCount_);
        CHECK_NULL_VOID(childWrapper);
        auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(childLayoutProperty);
        
        childLayoutConstraint.UpdateSelfIdealSizeWithCheck(OptionalSizeF(BUBBLE_BOX_SIZE, BUBBLE_BOX_SIZE));
        childLayoutProperty->UpdateContent(arrayValue_[selected_]);
        childLayoutProperty->UpdateTextColor(popupColor);
        auto fontSize = popupFont.GetFontSize();
        childLayoutProperty->UpdateFontSize(fontSize);
        auto fontWeight = popupFont.GetFontWeight();
        childLayoutProperty->UpdateFontWeight(fontWeight);
        
        auto childFrameNode = childWrapper->GetHostNode();
        auto childRenderContext = childFrameNode->GetRenderContext();
        childRenderContext->BlendBgColor(popupBackground);

        Dimension radius = Dimension(BUBBLE_BOX_RADIUS);
        BorderRadiusProperty borderRadius { radius, radius, radius, radius };
        childRenderContext->UpdateBorderRadius(borderRadius);
    }
}
} // namespace OHOS::Ace::NG
