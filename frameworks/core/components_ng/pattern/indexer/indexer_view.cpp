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

#include "core/components_ng/pattern/indexer/indexer_view.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void IndexerView::Create(const std::vector<std::string>& arrayValue, int32_t selected)
{
    // TODO:需要考虑更新场景
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::INDEXER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndexerPattern>(); });
    
    int32_t indexerSize = arrayValue.size();
    for (int32_t index = 0; index < indexerSize; index++) {
        auto indexerChildNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(indexerChildNode);
        auto textLayoutProperty = indexerChildNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(arrayValue[index]);
        frameNode->AddChild(indexerChildNode);
    }
    auto indexerPopupNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(indexerPopupNode);
    frameNode->AddChild(indexerPopupNode);
    
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, ArrayValue, arrayValue);
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, selected);
}

void IndexerView::SetColor(const Color& color)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Color, color);
}

void IndexerView::SetSelectedColor(const Color& selectedColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedColor, selectedColor);
}

void IndexerView::SetPopupColor(const Color& popupColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupColor, popupColor);
}

void IndexerView::SetSelectedBackgroundColor(const Color& selectedBackgroundColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedBackgroundColor, selectedBackgroundColor);
}

void IndexerView::SetPopupBackground(const Color& popupBackground)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupBackground, popupBackground);
}

void IndexerView::SetUsingPopup(bool usingPopup)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, UsingPopup, usingPopup);
}

void IndexerView::SetSelectedFont(const TextStyle& selectedFont)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedFont, selectedFont);
}

void IndexerView::SetPopupFont(const TextStyle& popupFont)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupFont, popupFont);
}

void IndexerView::SetFont(const TextStyle& font)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Font, font);
}

void IndexerView::SetItemSize(const Dimension& itemSize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, ItemSize, itemSize);
}

void IndexerView::SetAlignStyle(V2::AlignStyle alignStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, AlignStyle, alignStyle);
}

void IndexerView::SetOnSelected(OnSelectedEvent&& onSelected)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelected(std::move(onSelected));
}

void IndexerView::SetOnRequestPopupData(OnRequestPopupDataEvent&& onRequestPopupData)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestPopupData(std::move(onRequestPopupData));
}

void IndexerView::SetOnPopupSelected(OnPopupSelectedEvent&& onPopupSelectedEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPopupSelected(std::move(onPopupSelectedEvent));
}
} // namespace OHOS::Ace::NG
