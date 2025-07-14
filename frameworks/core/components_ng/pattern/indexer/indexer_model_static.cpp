/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/indexer/indexer_model_static.h"

#include "core/components_ng/pattern/indexer/indexer_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> IndexerModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::INDEXER_ETS_TAG, nodeId);
    return FrameNode::GetOrCreateFrameNode(
        V2::REFRESH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndexerPattern>(); });
}

void IndexerModelStatic::SetArrayValue(FrameNode* frameNode, const std::vector<std::string>& arrayValue)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, ArrayValue, arrayValue, frameNode);
}

void IndexerModelStatic::SetSelected(FrameNode* frameNode, int32_t selected)
{
    if (selected >= 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, selected, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, 0, frameNode);
    }
}

void IndexerModelStatic::SetColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, Color, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, Color, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelStatic::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor)
{
    if (selectedColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedColor, selectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            IndexerLayoutProperty, SelectedColor, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelStatic::SetPopupColor(FrameNode* frameNode, const std::optional<Color>& popupColor)
{
    if (popupColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupColor, popupColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, PopupColor, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelStatic::SetSelectedBackgroundColor(
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

void IndexerModelStatic::SetPopupBackground(FrameNode* frameNode, const std::optional<Color>& popupBackground)
{
    if (popupBackground.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupBackground, popupBackground.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupBackground, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelStatic::SetPopupSelectedColor(FrameNode* frameNode, const std::optional<Color>& popupSelectedColor)
{
    if (popupSelectedColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupSelectedColor, popupSelectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupSelectedColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelStatic::SetPopupUnselectedColor(FrameNode* frameNode, const std::optional<Color>& popupUnselectedColor)
{
    if (popupUnselectedColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            IndexerPaintProperty, PopupUnselectedColor, popupUnselectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupUnselectedColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelStatic::SetPopupItemBackground(FrameNode* frameNode, const std::optional<Color>& popupItemBackground)
{
    if (popupItemBackground.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            IndexerPaintProperty, PopupItemBackground, popupItemBackground.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupItemBackground, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelStatic::SetUsingPopup(FrameNode* frameNode, const std::optional<bool>& usingPopup)
{
    if (usingPopup.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, UsingPopup, usingPopup.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, UsingPopup, frameNode);
    }
}

void IndexerModelStatic::SetFont(FrameNode* frameNode, const std::optional<Dimension>& fontSize,
    const std::optional<FontWeight>& fontWeight, const std::optional<std::vector<std::string>>& fontFamily,
    const std::optional<OHOS::Ace::FontStyle>& fontStyle)
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

void IndexerModelStatic::SetSelectedFont(FrameNode* frameNode, const std::optional<Dimension>& fontSize,
    const std::optional<FontWeight>& fontWeight, const std::optional<std::vector<std::string>>& fontFamily,
    const std::optional<OHOS::Ace::FontStyle>& fontStyle)
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

void IndexerModelStatic::SetPopupFont(FrameNode* frameNode, const std::optional<Dimension>& fontSize,
    const std::optional<FontWeight>& fontWeight, const std::optional<std::vector<std::string>>& fontFamily,
    const std::optional<OHOS::Ace::FontStyle>& fontStyle)
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

void IndexerModelStatic::SetFontSize(FrameNode* frameNode, const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontSize, fontSize, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontSize, frameNode);
    }
}

void IndexerModelStatic::SetFontWeight(FrameNode* frameNode, const FontWeight weight)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontWeight, weight, frameNode);
}

void IndexerModelStatic::SetItemSize(FrameNode* frameNode, const Dimension& itemSize)
{
    auto itemSizeValue = itemSize.Value();
    if (itemSizeValue > 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, ItemSize, itemSize, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            IndexerLayoutProperty, ItemSize, Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP), frameNode);
    }
}

void IndexerModelStatic::SetPopupPositionX(FrameNode* frameNode, const std::optional<Dimension>& popupPositionXOpt)
{
    if (popupPositionXOpt.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionX, popupPositionXOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            IndexerLayoutProperty, PopupPositionX, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelStatic::SetPopupPositionY(FrameNode* frameNode, const std::optional<Dimension>& popupPositionYOpt)
{
    if (popupPositionYOpt.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionY, popupPositionYOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            IndexerLayoutProperty, PopupPositionY, PROPERTY_UPDATE_NORMAL, frameNode);
    }
}

void IndexerModelStatic::SetAutoCollapse(FrameNode* frameNode, const std::optional<bool>& autoCollapse)
{
    if (autoCollapse.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, AutoCollapse, autoCollapse.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, AutoCollapse, frameNode);
    }
}

void IndexerModelStatic::SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& state)
{
    if (state.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, EnableHapticFeedback, state.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, EnableHapticFeedback, frameNode);
    }
}

void IndexerModelStatic::SetPopupBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
{
    if (radius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupBorderRadius, radius.value(), frameNode);
    }
}

void IndexerModelStatic::SetPopupItemBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
{
    if (radius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupItemBorderRadius, radius.value(), frameNode);
    }
}

void IndexerModelStatic::SetItemBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
{
    if (radius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, ItemBorderRadius, radius.value(), frameNode);
    }
}

void IndexerModelStatic::SetIndexerBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
{
    if (radius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, IndexerBorderRadius, radius.value(), frameNode);
    }
}

void IndexerModelStatic::SetPopupBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& indexerBlurStyle)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupBackgroundBlurStyle, indexerBlurStyle, frameNode);
}

void IndexerModelStatic::SetPopupTitleBackground(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(IndexerPaintProperty, PopupTitleBackground, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            IndexerPaintProperty, PopupTitleBackground, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void IndexerModelStatic::SetAlignStyle(FrameNode* frameNode, const std::optional<AlignStyle>& alignStyle)
{
    if (alignStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, AlignStyle, alignStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, AlignStyle, frameNode);
    }
}

void IndexerModelStatic::SetPopupHorizontalSpace(
    FrameNode* frameNode, const std::optional<Dimension>& popupHorizontalSpace)
{
    if (popupHorizontalSpace.has_value() && popupHorizontalSpace.value().Value() >= 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            IndexerLayoutProperty, PopupHorizontalSpace, popupHorizontalSpace.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupHorizontalSpace, frameNode);
    }
}

void IndexerModelStatic::SetOnSelected(FrameNode* frameNode, std::function<void(const int32_t selected)>&& onSelect)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelected(std::move(onSelect));
}

void IndexerModelStatic::SetOnRequestPopupData(
    FrameNode* frameNode, std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestPopupData(std::move(RequestPopupData));
}

void IndexerModelStatic::SetOnPopupSelected(
    FrameNode* frameNode, std::function<void(const int32_t selected)>&& onPopupSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPopupSelected(std::move(onPopupSelected));
}

void IndexerModelStatic::SetChangeEvent(FrameNode* frameNode, std::function<void(const int32_t selected)>&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void IndexerModelStatic::SetCreatChangeEvent(
    FrameNode* frameNode, std::function<void(const int32_t selected)>&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCreatChangeEvent(std::move(changeEvent));
}
} // namespace OHOS::Ace::NG
