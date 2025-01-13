/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/arc_indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"

namespace OHOS::Ace::NG {
void IndexerModelNG::Create(std::vector<std::string>& arrayValue, int32_t selected, bool isArc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    const char* tag = isArc ? V2::ARC_INDEXER_ETS_TAG : V2::INDEXER_ETS_TAG;
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag, nodeId);
    RefPtr<FrameNode> frameNode = nullptr;
    if (isArc) {
        frameNode = FrameNode::GetOrCreateFrameNode(
            tag, nodeId, []() { return AceType::MakeRefPtr<ArcIndexerPattern>(); });
    } else {
        frameNode = FrameNode::GetOrCreateFrameNode(
            tag, nodeId, []() { return AceType::MakeRefPtr<IndexerPattern>(); });
    }

    stack->Push(frameNode);
    if (selected < 0 || selected >= static_cast<int32_t>(arrayValue.size())) {
        selected = 0;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, ArrayValue, arrayValue);
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, selected);
}

void IndexerModelNG::SetSelectedColor(const std::optional<Color>& selectedColor)
{
    if (selectedColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedColor, selectedColor.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, SelectedColor, PROPERTY_UPDATE_NORMAL);
    }
}

void IndexerModelNG::SetColor(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Color, color.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, Color, PROPERTY_UPDATE_NORMAL);
    }
}

void IndexerModelNG::SetPopupColor(const std::optional<Color>& popupColor)
{
    if (popupColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupColor, popupColor.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, PopupColor, PROPERTY_UPDATE_NORMAL);
    }
}

void IndexerModelNG::SetSelectedBackgroundColor(const std::optional<Color>& selectedBackgroundColor)
{
    if (selectedBackgroundColor.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, SelectedBackgroundColor, selectedBackgroundColor.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, SelectedBackgroundColor, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetPopupBackground(const std::optional<Color>& popupBackground)
{
    if (popupBackground.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupBackground, popupBackground.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupBackground, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetUsingPopup(bool usingPopup)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, UsingPopup, usingPopup);
}

void IndexerModelNG::SetSelectedFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
    std::optional<std::vector<std::string>>& fontFamily, std::optional<OHOS::Ace::FontStyle>& fontStyle)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle selectTextStyle = indexerTheme->GetSelectTextStyle();
    TextStyle textStyle;
    textStyle.SetFontSize(fontSize.value_or(selectTextStyle.GetFontSize()));
    textStyle.SetFontWeight(fontWeight.value_or(selectTextStyle.GetFontWeight()));
    textStyle.SetFontFamilies(fontFamily.value_or(selectTextStyle.GetFontFamilies()));
    textStyle.SetFontStyle(fontStyle.value_or(selectTextStyle.GetFontStyle()));
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedFont, textStyle);
}

void IndexerModelNG::SetPopupFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
    std::optional<std::vector<std::string>>& fontFamily, std::optional<OHOS::Ace::FontStyle>& fontStyle)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle popupTextStyle = indexerTheme->GetPopupTextStyle();
    TextStyle textStyle;
    textStyle.SetFontSize(fontSize.value_or(popupTextStyle.GetFontSize()));
    textStyle.SetFontWeight(fontWeight.value_or(popupTextStyle.GetFontWeight()));
    textStyle.SetFontFamilies(fontFamily.value_or(popupTextStyle.GetFontFamilies()));
    textStyle.SetFontStyle(fontStyle.value_or(popupTextStyle.GetFontStyle()));
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupFont, textStyle);
}

void IndexerModelNG::SetFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
    std::optional<std::vector<std::string>>& fontFamily, std::optional<OHOS::Ace::FontStyle>& fontStyle)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle defaultTextStyle = indexerTheme->GetDefaultTextStyle();
    TextStyle textStyle;
    textStyle.SetFontSize(fontSize.value_or(defaultTextStyle.GetFontSize()));
    textStyle.SetFontWeight(fontWeight.value_or(defaultTextStyle.GetFontWeight()));
    textStyle.SetFontFamilies(fontFamily.value_or(defaultTextStyle.GetFontFamilies()));
    textStyle.SetFontStyle(fontStyle.value_or(defaultTextStyle.GetFontStyle()));
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Font, textStyle);
}

void IndexerModelNG::SetItemSize(const Dimension& itemSize)
{
    auto itemSizeValue = itemSize.Value();
    if (itemSizeValue > 0) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, ItemSize, itemSize);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, ItemSize, Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
    }
}

void IndexerModelNG::SetAlignStyle(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, AlignStyle, NG_ALIGN_STYLE[value]);
}

void IndexerModelNG::SetPopupHorizontalSpace(const Dimension& popupHorizontalSpace)
{
    auto spaceValue = popupHorizontalSpace.Value();
    if (spaceValue >= 0) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupHorizontalSpace, popupHorizontalSpace);
    } else {
        ACE_RESET_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupHorizontalSpace);
    }
}

void IndexerModelNG::SetSelected(int32_t selected)
{
    if (selected >= 0) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, selected);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, 0);
    }
}

void IndexerModelNG::SetPopupPositionX(const std::optional<Dimension>& popupPositionXOpt)
{
    if (popupPositionXOpt.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionX, popupPositionXOpt.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, PopupPositionX, PROPERTY_UPDATE_NORMAL);
    }
}

void IndexerModelNG::SetPopupPositionY(const std::optional<Dimension>& popupPositionYOpt)
{
    if (popupPositionYOpt.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionY, popupPositionYOpt.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, PopupPositionY, PROPERTY_UPDATE_NORMAL);
    }
}

void IndexerModelNG::SetPopupItemBackground(const std::optional<Color>& popupItemBackground)
{
    if (popupItemBackground.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupItemBackground, popupItemBackground.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupItemBackground, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetPopupSelectedColor(const std::optional<Color>& popupSelectedColor)
{
    if (popupSelectedColor.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupSelectedColor, popupSelectedColor.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupSelectedColor, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetPopupUnselectedColor(const std::optional<Color>& popupUnselectedColor)
{
    if (popupUnselectedColor.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupUnselectedColor, popupUnselectedColor.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupUnselectedColor, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetFontSize(const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontSize, fontSize);
    } else {
        ACE_RESET_LAYOUT_PROPERTY(IndexerLayoutProperty, FontSize);
    }
}

void IndexerModelNG::SetFontWeight(const FontWeight weight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontWeight, weight);
}

void IndexerModelNG::SetOnSelected(std::function<void(const int32_t selected)>&& onSelect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelected(std::move(onSelect));
}

void IndexerModelNG::SetOnRequestPopupData(
    std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestPopupData(std::move(RequestPopupData));
}

void IndexerModelNG::SetOnPopupSelected(std::function<void(const int32_t selected)>&& onPopupSelected)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPopupSelected(std::move(onPopupSelected));
}

void IndexerModelNG::SetChangeEvent(std::function<void(const int32_t selected)>&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void IndexerModelNG::SetCreatChangeEvent(std::function<void(const int32_t selected)>&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCreatChangeEvent(std::move(changeEvent));
}

void IndexerModelNG::SetAutoCollapse(bool autoCollapse)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, AutoCollapse, autoCollapse);
}

void IndexerModelNG::SetEnableHapticFeedback(bool state)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, EnableHapticFeedback, state);
}

void IndexerModelNG::SetPopupBorderRadius(const Dimension& radius)
{
    ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupBorderRadius, radius);
}

void IndexerModelNG::SetPopupItemBorderRadius(const Dimension& radius)
{
    ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupItemBorderRadius, radius);
}

void IndexerModelNG::SetItemBorderRadius(const Dimension& radius)
{
    ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, ItemBorderRadius, radius);
}

void IndexerModelNG::SetIndexerBorderRadius(const Dimension& radius)
{
    ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, IndexerBorderRadius, radius);
}

void IndexerModelNG::SetPopupBackgroundBlurStyle(const BlurStyleOption& indexerBlurStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupBackgroundBlurStyle, indexerBlurStyle);
}

void IndexerModelNG::SetPopupTitleBackground(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupTitleBackground, color.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupTitleBackground, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetAdaptiveWidth(bool state)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, AdaptiveWidth, state);
}

RefPtr<FrameNode> IndexerModelNG::CreateFrameNode(int32_t nodeId, bool isArc)
{
    const char* tag = isArc ? V2::ARC_INDEXER_ETS_TAG : V2::INDEXER_ETS_TAG;
    RefPtr<FrameNode> frameNode = nullptr;
    if (isArc) {
        frameNode = FrameNode::GetOrCreateFrameNode(
            tag, nodeId, []() { return AceType::MakeRefPtr<ArcIndexerPattern>(); });
    } else {
        frameNode = FrameNode::GetOrCreateFrameNode(
            tag, nodeId, []() { return AceType::MakeRefPtr<IndexerPattern>(); });
    }
    return frameNode;
}

void IndexerModelNG::SetArrayValue(FrameNode* frameNode, const std::vector<std::string>& arrayValue)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, ArrayValue, arrayValue, frameNode);
}

void IndexerModelNG::SetAdaptiveWidth(FrameNode* frameNode, bool state)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, AdaptiveWidth, state, frameNode);
}

void IndexerModelNG::SetPopupBorderRadius(FrameNode* frameNode, const Dimension& radius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupBorderRadius, radius, frameNode);
}

void IndexerModelNG::SetPopupItemBorderRadius(FrameNode* frameNode, const Dimension& radius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupItemBorderRadius, radius, frameNode);
}

void IndexerModelNG::SetItemBorderRadius(FrameNode* frameNode, const Dimension& radius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, ItemBorderRadius, radius, frameNode);
}

void IndexerModelNG::SetIndexerBorderRadius(FrameNode* frameNode, const Dimension& radius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, IndexerBorderRadius, radius, frameNode);
}

void IndexerModelNG::SetPopupBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& indexerBlurStyle)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupBackgroundBlurStyle, indexerBlurStyle, frameNode);
}

void IndexerModelNG::SetPopupTitleBackground(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupTitleBackground, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupTitleBackground, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelNG::SetFontSize(FrameNode* frameNode, const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontSize, fontSize, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontSize, frameNode);
    }
}

void IndexerModelNG::SetFontWeight(FrameNode* frameNode, const FontWeight weight)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontWeight, weight, frameNode);
}

void IndexerModelNG::SetSelectedFont(FrameNode* frameNode, std::optional<Dimension>& fontSize,
    std::optional<FontWeight>& fontWeight, std::optional<std::vector<std::string>>& fontFamily,
    std::optional<OHOS::Ace::FontStyle>& fontStyle)
{
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle selectTextStyle = indexerTheme->GetSelectTextStyle();
    TextStyle textStyle;
    textStyle.SetFontSize(fontSize.value_or(selectTextStyle.GetFontSize()));
    textStyle.SetFontWeight(fontWeight.value_or(selectTextStyle.GetFontWeight()));
    textStyle.SetFontFamilies(fontFamily.value_or(selectTextStyle.GetFontFamilies()));
    textStyle.SetFontStyle(fontStyle.value_or(selectTextStyle.GetFontStyle()));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedFont, textStyle, frameNode);
}

void IndexerModelNG::SetPopupFont(FrameNode* frameNode, std::optional<Dimension>& fontSize,
    std::optional<FontWeight>& fontWeight, std::optional<std::vector<std::string>>& fontFamily,
    std::optional<OHOS::Ace::FontStyle>& fontStyle)
{
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle popupTextStyle = indexerTheme->GetPopupTextStyle();
    TextStyle textStyle;
    textStyle.SetFontSize(fontSize.value_or(popupTextStyle.GetFontSize()));
    textStyle.SetFontWeight(fontWeight.value_or(popupTextStyle.GetFontWeight()));
    textStyle.SetFontFamilies(fontFamily.value_or(popupTextStyle.GetFontFamilies()));
    textStyle.SetFontStyle(fontStyle.value_or(popupTextStyle.GetFontStyle()));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupFont, textStyle, frameNode);
}

void IndexerModelNG::SetFont(FrameNode* frameNode, std::optional<Dimension>& fontSize,
    std::optional<FontWeight>& fontWeight, std::optional<std::vector<std::string>>& fontFamily,
    std::optional<OHOS::Ace::FontStyle>& fontStyle)
{
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle defaultTextStyle = indexerTheme->GetDefaultTextStyle();
    TextStyle textStyle;
    textStyle.SetFontSize(fontSize.value_or(defaultTextStyle.GetFontSize()));
    textStyle.SetFontWeight(fontWeight.value_or(defaultTextStyle.GetFontWeight()));
    textStyle.SetFontFamilies(fontFamily.value_or(defaultTextStyle.GetFontFamilies()));
    textStyle.SetFontStyle(fontStyle.value_or(defaultTextStyle.GetFontStyle()));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, Font, textStyle, frameNode);
}

void IndexerModelNG::SetPopupUnselectedColor(FrameNode* frameNode, const std::optional<Color>& popupUnselectedColor)
{
    if (popupUnselectedColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            IndexerPaintProperty, PopupUnselectedColor, popupUnselectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupUnselectedColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelNG::SetPopupItemBackground(FrameNode* frameNode, const std::optional<Color>& popupItemBackground)
{
    if (popupItemBackground.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            IndexerPaintProperty, PopupItemBackground, popupItemBackground.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupItemBackground, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelNG::SetColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, Color, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, Color, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelNG::SetPopupColor(FrameNode* frameNode, const std::optional<Color>& popupColor)
{
    if (popupColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupColor, popupColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, PopupColor, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelNG::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor)
{
    if (selectedColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedColor, selectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            IndexerLayoutProperty, SelectedColor, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelNG::SetPopupBackground(FrameNode* frameNode, const std::optional<Color>& popupBackground)
{
    if (popupBackground.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupBackground, popupBackground.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupBackground, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelNG::SetSelectedBackgroundColor(
    FrameNode* frameNode, const std::optional<Color>& selectedBackgroundColor)
{
    if (selectedBackgroundColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            IndexerPaintProperty, SelectedBackgroundColor, selectedBackgroundColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, SelectedBackgroundColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelNG::SetAlignStyle(FrameNode* frameNode, int32_t value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, AlignStyle, NG_ALIGN_STYLE[value], frameNode);
}

void IndexerModelNG::SetPopupHorizontalSpace(FrameNode* frameNode, const Dimension& popupHorizontalSpace)
{
    auto spaceValue = popupHorizontalSpace.Value();
    if (spaceValue >= 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupHorizontalSpace, popupHorizontalSpace, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupHorizontalSpace, frameNode);
    }
}

void IndexerModelNG::SetUsingPopup(FrameNode* frameNode, bool usingPopup)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, UsingPopup, usingPopup, frameNode);
}

void IndexerModelNG::SetSelected(FrameNode* frameNode, int32_t selected)
{
    if (selected >= 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, selected, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, 0, frameNode);
    }
}

void IndexerModelNG::SetPopupSelectedColor(FrameNode* frameNode, const std::optional<Color>& popupSelectedColor)
{
    if (popupSelectedColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupSelectedColor, popupSelectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupSelectedColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelNG::SetItemSize(FrameNode* frameNode, const Dimension& itemSize)
{
    auto itemSizeValue = itemSize.Value();
    if (itemSizeValue > 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, ItemSize, itemSize, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            IndexerLayoutProperty, ItemSize, Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP), frameNode);
    }
}

void IndexerModelNG::SetPopupPositionX(FrameNode* frameNode, const std::optional<Dimension>& popupPositionXOpt)
{
    if (popupPositionXOpt.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionX, popupPositionXOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            IndexerLayoutProperty, PopupPositionX, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelNG::SetPopupPositionY(FrameNode* frameNode, const std::optional<Dimension>& popupPositionYOpt)
{
    if (popupPositionYOpt.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionY, popupPositionYOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            IndexerLayoutProperty, PopupPositionY, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelNG::SetAutoCollapse(FrameNode* frameNode, bool autoCollapse)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, AutoCollapse, autoCollapse, frameNode);
}

void IndexerModelNG::SetEnableHapticFeedback(FrameNode* frameNode, bool state)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, EnableHapticFeedback, state, frameNode);
}

void IndexerModelNG::SetOnSelected(FrameNode* frameNode, std::function<void(const int32_t selected)>&& onSelect)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelected(std::move(onSelect));
}

void IndexerModelNG::SetOnRequestPopupData(FrameNode* frameNode,
    std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestPopupData(std::move(RequestPopupData));
}

void IndexerModelNG::SetOnPopupSelected(FrameNode* frameNode,
    std::function<void(const int32_t selected)>&& onPopupSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPopupSelected(std::move(onPopupSelected));
}

void IndexerModelNG::SetChangeEvent(FrameNode* frameNode, std::function<void(const int32_t selected)>&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void IndexerModelNG::SetCreatChangeEvent(FrameNode* frameNode,
    std::function<void(const int32_t selected)>&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCreatChangeEvent(std::move(changeEvent));
}
} // namespace OHOS::Ace::NG
