/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_v2/indexer/indexer_component.h"

#include "core/components/arc/arc_component.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/text/text_component.h"
#include "core/components_v2/indexer/indexer_element.h"
#include "core/components_v2/indexer/render_indexer.h"
#include "core/components_v2/indexer/popup_list_component.h"

namespace OHOS::Ace::V2 {
RefPtr<Element> IndexerComponent::CreateElement()
{
    LOGI("[indexer] CreateElement ");
    return AceType::MakeRefPtr<IndexerElement>();
}

RefPtr<RenderNode> IndexerComponent::CreateRenderNode()
{
    RefPtr<RenderIndexer> renderNode =  AceType::MakeRefPtr<RenderIndexer>();
    renderNode->SetFocusIndex(selectedIndex_);
    return renderNode;
}

void IndexerComponent::FormatLabelAlphabet()
{
    for (auto& item : indexerLabel_) {
        if (item == INDEXER_STR_DOT_EX) {
            item = INDEXER_STR_DOT;
        }
    }
}

void IndexerComponent::BuildIndexerAlphabet()
{
    std::vector<std::u16string> alphabet = Localization::GetInstance()->GetIndexAlphabet(); // get alphabet
    if (alphabet.empty()) {
        LOGE("fail to build indexer alphabet due to alphabet is empty");
        return;
    }
    FormatLabelAlphabet();

    sectionsLocal_.clear();
    labelLocal_.clear();

    for (size_t i = 0; i < indexerLabel_.size(); ++i) {
        if (indexerLabel_[i] != INDEXER_STR_DOT) {
            sectionsLocal_.push_back(indexerLabel_[i]);
            labelLocal_.push_back(indexerLabel_[i]);
        }
    }
}

void IndexerComponent::InitIndexerItemStyle()
{
    // Indexer item style when binding list item is not current.
    normalStyle_.SetFontSize(Dimension(INDEXER_LIST_ITEM_TEXT_SIZE, DimensionUnit::FP));
    normalStyle_.SetFontWeight(FontWeight::W400);
    normalStyle_.SetTextColor(Color(INDEXER_LIST_COLOR));

    // Indexer item style when binding list item is current.
    activeStyle_.SetFontSize(Dimension(INDEXER_LIST_ITEM_TEXT_SIZE, DimensionUnit::FP));
    activeStyle_.SetFontWeight(FontWeight::W500);
    activeStyle_.SetTextColor(Color(INDEXER_LIST_ACTIVE_COLOR));

    bubbleStyle_.SetTextAlign(TextAlign::CENTER);
    bubbleStyle_.SetFontSize(Dimension(BUBBLE_FONT_SIZE, DimensionUnit::VP));
    bubbleStyle_.SetTextColor(Color(BUBBLE_FONT_COLOR));
}

void IndexerComponent::BuildBubbleBox()
{
    if (!bubbleEnabled_) {
        return;
    }
    RefPtr<BoxComponent> bubble = AceType::MakeRefPtr<BoxComponent>();
    bubble->SetFlex(BoxFlex::FLEX_NO);
    bubble->SetAlignment(Alignment::CENTER);
    Radius radius = Radius(Dimension(BUBBLE_BOX_SIZE_CIRCLE, DimensionUnit::VP) * HALF);
    if (!bubbleBack_) {
        bubbleBack_ = AceType::MakeRefPtr<Decoration>();
    }

    // for shadow blur region
    bubble->SetWidth(BUBBLE_BOX_SIZE, DimensionUnit::VP);
    bubble->SetHeight(BUBBLE_BOX_SIZE, DimensionUnit::VP);
    radius = Radius(Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP));
    bubbleBack_->SetBackgroundColor(Color(BUBBLE_BG_COLOR).BlendOpacity(NINETY_OPACITY_IN_PERCENT));

    bubbleBack_->SetBorderRadius(radius);
    bubble->SetBackDecoration(bubbleBack_);
    bubbleText_ = AceType::MakeRefPtr<TextComponent>(StringUtils::Str16ToStr8(INDEXER_STR_SHARP));
    bubbleText_->SetTextStyle(bubbleStyle_);
    bubble->SetChild(bubbleText_);
    RefPtr<DisplayComponent> displayComponent = AceType::MakeRefPtr<DisplayComponent>(bubble);
    displayComponent->SetOpacity(ZERO_OPACITY);
    displayComponent->SetShadow(ShadowConfig::DefaultShadowL);
    AppendChild(displayComponent);
    nonItemCount_++;
}

void IndexerComponent::BuildPopupList()
{
    if (!bubbleEnabled_ && !popupListEnabled_) {
        return;
    }

    if (!popupList_) {
        popupList_ = AceType::MakeRefPtr<PopupListComponent>();
    }
    RefPtr<DisplayComponent> displayComponent = AceType::MakeRefPtr<DisplayComponent>(popupList_);
    displayComponent->SetOpacity(POPUP_LIST_OPACITY);
    displayComponent->SetShadow(ShadowConfig::DefaultShadowL);

    AppendChild(displayComponent);
    nonItemCount_++;
}

void IndexerComponent::BuildTextItem(const std::u16string& strSection, const std::u16string& strLabel, int32_t itemType)
{
    RefPtr<IndexerItemComponent> textItem =
        AceType::MakeRefPtr<IndexerItemComponent>(strSection, strLabel, itemSize_, false);
    textItem->SetNormalTextStyle(normalStyle_);
    textItem->SetActiveTextStyle(activeStyle_);
    textItem->SetTextStyle(false);
    textItem->SetItemType(itemType);
    textItem->SetSectionIndex(itemCount_);
    textItem->SetSelectedBackgroundColor(selectedBgColor_);
    listItem_.push_back(textItem);
    AppendChild(textItem);
    ++itemCount_;
}

void IndexerComponent::BuildIndexerItems()
{
    int32_t length = labelLocal_.size();
    if (length <= 0) {
        LOGE("[indexer] invalid section string");
        return;
    }

    BuildBubbleBox();
    itemCount_ = 0;

    for (int32_t i = 0; i < length; ++i) {
        std::u16string strItem = labelLocal_[i];
        BuildTextItem(sectionsLocal_[i], strItem);
    }
    LOGI("[indexer] BuildIndexerItems, itemCount_:%{public}d", itemCount_);
}

void IndexerComponent::UpdateTextStyle()
{
    for (auto& item : GetChildren()) {
        RefPtr<IndexerItemComponent> textItem = AceType::DynamicCast<IndexerItemComponent>(item);
        if (textItem) {
            textItem->SetNormalTextStyle(normalStyle_);
            textItem->SetActiveTextStyle(activeStyle_);
            textItem->SetTextStyle(false);
            textItem->SetSelectedBackgroundColor(selectedBgColor_);
            textItem->SetItemSize(itemSize_);
            textItem->UpdateSize();
        }
    }
}
} // namespace OHOS::Ace