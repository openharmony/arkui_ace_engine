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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
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
    return false;
}

void IndexerPattern::OnTouchDown(const TouchEventInfo& info)
{
    auto touchPosition = info.GetTouches().front().GetLocalLocation();
    if (itemSizeRender_ > 0) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto size = SizeF(itemSizeRender_, itemSizeRender_ * itemCount_);
        auto padding = layoutProperty->CreatePaddingAndBorder();
        MinusPaddingToSize(padding, size);
        auto top = padding.top.value_or(0.0f);

        int32_t itemIndex = static_cast<int32_t>((touchPosition.GetY() - top) / itemSizeRender_);
        selected_ = itemIndex;

        if (layoutProperty->GetArrayValue().has_value()) {
            arrayValue_ = layoutProperty->GetArrayValue().value();
            itemCount_ = arrayValue_.size();
        }
        if (!isInitialized_ && layoutProperty->GetSelected().has_value()) {
            selected_ = layoutProperty->GetSelected().value();
        }
        isInitialized_ = true;
        if (itemCount_ <= 0) {
            LOGE("AlphabetIndexer arrayValue size is less than 0");
            return;
        }

        auto color = layoutProperty->GetColor().value_or(Color::BLACK);
        auto selectedColor = layoutProperty->GetSelectedColor().value_or(Color::BLACK);
        auto popupColor = layoutProperty->GetPopupColor().value_or(Color::BLACK);
        auto selectedBackgroundColor = layoutProperty->GetSelectedBackgroundColor().value_or(Color::BLACK);
        auto usingPopup = layoutProperty->GetUsingPopup().value_or(false);
        TextStyle textStyle;
        auto selectedFont = layoutProperty->GetSelectedFont().value_or(textStyle);
        auto popupFont = layoutProperty->GetPopupFont().value_or(textStyle);
        auto font = layoutProperty->GetFont().value_or(textStyle);

        int32_t index = 0;
        auto childrenNode = host->GetChildren();
        for (auto iter = childrenNode.begin(); iter != childrenNode.end(); iter++) {
            auto childNode = AceType::DynamicCast<FrameNode>(*(iter));
            auto nodeLayoutProperty = childNode->GetLayoutProperty<TextLayoutProperty>();
            if (index == selected_) {
                nodeLayoutProperty->UpdateTextColor(selectedColor);
                auto fontSize = selectedFont.GetFontSize();
                nodeLayoutProperty->UpdateFontSize(fontSize);
                auto fontWeight = selectedFont.GetFontWeight();
                nodeLayoutProperty->UpdateFontWeight(fontWeight);

                auto childRenderContext = childNode->GetRenderContext();
                childRenderContext->BlendBgColor(selectedBackgroundColor);
            } else if (index == itemCount_) {
                if (usingPopup) {
                    nodeLayoutProperty->UpdateContext(arrayValue_[selected_]);
                    nodeLayoutProperty->UpdateTextColor(popupColor);
                    auto fontSize = popupFont.GetFontSize();
                    nodeLayoutProperty->UpdateFontSize(fontSize);
                    auto fontWeight = popupFont.GetFontWeight();
                    nodeLayoutProperty->UpdateFontWeight(fontWeight);
                }
            } else {
                nodeLayoutProperty->UpdateTextColor(color);
                auto fontSize = font.GetFontSize();
                nodeLayoutProperty->UpdateFontSize(fontSize);
                auto fontWeight = font.GetFontWeight();
                nodeLayoutProperty->UpdateFontWeight(fontWeight);

                auto childRenderContext = childNode->GetRenderContext();
                childRenderContext->ResetBlendBgColor();
            }
            index++;
        }
    
        auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
        CHECK_NULL_VOID(indexerEventHub);
        
        auto onSelected = indexerEventHub->GetOnSelected();
        if (onSelected && itemIndex >= 0 && itemIndex < itemCount_) {
            onSelected(itemIndex);
        }

        auto onRequestPopupData = indexerEventHub->GetOnRequestPopupData();
        if (onRequestPopupData && itemIndex >= 0 && itemIndex < itemCount_) {
            // TODO: 需要接受返回值覆盖默认的弹窗文本
            onRequestPopupData(itemIndex);
        }

        auto onPopupSelected = indexerEventHub->GetOnPopupSelected();
        if (onPopupSelected && itemIndex >= 0 && itemIndex < itemCount_) {
            onPopupSelected(itemIndex);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}
} // namespace OHOS::Ace::NG
