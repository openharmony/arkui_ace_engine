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

#include "base/geometry/dimension.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
void IndexerModelNG::Create(std::vector<std::string>& arrayValue, int32_t selected)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::INDEXER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndexerPattern>(); });

    frameNode->Clean();
    int32_t indexerSize = arrayValue.size();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    for (int32_t index = 0; index < indexerSize; index++) {
        auto indexerChildNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(indexerChildNode);
        auto textLayoutProperty = indexerChildNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(arrayValue[index]);
        Dimension borderWidth;
        textLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
        auto defaultFont = indexerTheme->GetDefaultTextStyle();
        textLayoutProperty->UpdateFontSize(defaultFont.GetFontSize());
        textLayoutProperty->UpdateFontWeight(defaultFont.GetFontWeight());
        textLayoutProperty->UpdateFontFamily(defaultFont.GetFontFamilies());
        textLayoutProperty->UpdateItalicFontStyle(defaultFont.GetFontStyle());
        textLayoutProperty->UpdateTextColor(indexerTheme->GetDefaultTextColor());
        auto childRenderContext = indexerChildNode->GetRenderContext();
        CHECK_NULL_VOID(childRenderContext);
        childRenderContext->ResetBlendBorderColor();
        childRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        Dimension radiusZeroSize;
        childRenderContext->UpdateBorderRadius({ radiusZeroSize, radiusZeroSize, radiusZeroSize, radiusZeroSize });
        frameNode->AddChild(indexerChildNode);
    }
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, ArrayValue, arrayValue);
    if (selected >= 0 && selected < indexerSize) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, selected);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Selected, 0);
    }
}

void IndexerModelNG::SetSelectedColor(const std::optional<Color>& selectedColor)
{
    if (selectedColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, SelectedColor, selectedColor.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, SelectedColor, PROPERTY_UPDATE_MEASURE);
    }
}

void IndexerModelNG::SetColor(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, Color, color.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, Color, PROPERTY_UPDATE_MEASURE);
    }
}

void IndexerModelNG::SetPopupColor(const std::optional<Color>& popupColor)
{
    if (popupColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupColor, popupColor.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(IndexerLayoutProperty, PopupColor, PROPERTY_UPDATE_MEASURE);
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
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
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupHorizontalSpace, popupHorizontalSpace);
    } else {
        LOGW("PopupHorizontalSpace value is not valid");
        ACE_RESET_PAINT_PROPERTY(IndexerPaintProperty, PopupHorizontalSpace);
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

void IndexerModelNG::SetPopupPositionX(const Dimension& popupPositionX)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionX, popupPositionX);
}

void IndexerModelNG::SetPopupPositionY(const Dimension& popupPositionY)
{
    ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, PopupPositionY, popupPositionY);
}

void IndexerModelNG::SetPopupItemBackground(const std::optional<Color>& popupItemBackground)
{
    if (popupItemBackground.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupItemBackground, popupItemBackground.value());
    } else {
        LOGW("PopupItemBackgroundColor value is not valid");
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupItemBackground, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetPopupSelectedColor(const std::optional<Color>& popupSelectedColor)
{
    if (popupSelectedColor.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupSelectedColor, popupSelectedColor.value());
    } else {
        LOGW("PopupSelectedColor value is not valid");
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupSelectedColor, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetPopupUnselectedColor(const std::optional<Color>& popupUnselectedColor)
{
    if (popupUnselectedColor.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(IndexerPaintProperty, PopupUnselectedColor, popupUnselectedColor.value());
    } else {
        LOGW("PopupUnselectedColor value is not valid");
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(IndexerPaintProperty, PopupUnselectedColor, PROPERTY_UPDATE_RENDER);
    }
}

void IndexerModelNG::SetFontSize(const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(IndexerLayoutProperty, FontSize, fontSize);
    } else {
        LOGW("FontSize value is not valid");
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
} // namespace OHOS::Ace::NG
