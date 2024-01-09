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
#include "core/interfaces/native/node/alphabet_indexer_modifier.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_POPUPITEMFONT_SIZE = 24.0;
const std::string DEFAULT_SELECTEDFONT_SIZE = "12.0";
const std::string DEFAULT_POPUPFONT_SIZE = "24.0vp";
const std::string DEFAULT_FONT_SIZE = "12.0";
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
const std::string DEFAULT_FONT_WEIGHT = "normal";
constexpr int FONT_SIZE_INDEX = 0;
constexpr int FONT_WEIGHT_INDEX = 1;
constexpr int FONT_FAMILY_INDEX = 2;
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
constexpr uint32_t DEFAULT_ITEM_BG_COLOR = 0xFFFFFF;
constexpr uint32_t DEFAULT_COLOR = 0x99000000;
constexpr uint32_t DEFAULT_POPUP_COLOR = 0xFF254FF7;
constexpr uint32_t DEFAULT_SELECTED_COLOR = 0xFF254FF7;
constexpr uint32_t DEFAULT_POPUP_BG_COLOR = 0xFFFFFFFF;
constexpr uint32_t DEFAULT_SELECTED_BG_COLOR = 0x1F0A59F7;
constexpr uint32_t DEFAULT_POPUP_SELECTED_COLOR = 0xFF182431;
constexpr bool DEFAULT_USINGPOPUP = false;
constexpr int32_t DEFAULT_SELECTED = 0;
constexpr Dimension DEFAULT_POPUPHORIZONTALSPACE = -1.0_vp;
constexpr int32_t DEFAULT_ALIGN_STYLE = static_cast<int32_t>(NG::AlignStyle::RIGHT);
constexpr double DEFAULT_ITEM_SIZE = 16.0;
constexpr double DEFAULT_POPUP_POSITION_X = 60.0;
constexpr double DEFAULT_POPUP_POSITION_Y = 48.0;
} // namespace

void SetPopupItemFont(NodeHandle node, double size, int unit, const char* weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fontSize = Dimension(size, static_cast<OHOS::Ace::DimensionUnit>(unit));
    IndexerModelNG::SetFontSize(frameNode, fontSize);
    IndexerModelNG::SetFontWeight(frameNode, StringUtils::StringToFontWeight(std::string(weight), FontWeight::MEDIUM));
}

void ResetPopupItemFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetFontSize(frameNode, Dimension(DEFAULT_POPUPITEMFONT_SIZE, DimensionUnit::FP));
    IndexerModelNG::SetFontWeight(frameNode, FontWeight::MEDIUM);
}

void SetSelectedFont(NodeHandle node, const char* fontInfo, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, '|', res);
    std::optional<Dimension> fontSize =
        StringUtils::StringToCalcDimension(res[FONT_SIZE_INDEX], false, DimensionUnit::FP);
    std::optional<FontWeight> fontWeight = StringUtils::StringToFontWeight(res[FONT_WEIGHT_INDEX]);
    std::optional<std::vector<std::string>> fontFamily = Framework::ConvertStrToFontFamilies(res[FONT_FAMILY_INDEX]);
    std::optional<Ace::FontStyle> fontStyle = FONT_STYLES[0];
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        fontStyle = FONT_STYLES[style];
    };
    IndexerModelNG::SetSelectedFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void ResetSelectedFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> fontSize =
        StringUtils::StringToCalcDimension(DEFAULT_SELECTEDFONT_SIZE, false, DimensionUnit::FP);
    std::optional<FontWeight> fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    std::optional<std::vector<std::string>> fontFamily =
        Framework::ConvertStrToFontFamilies(std::string(DEFAULT_FONT_FAMILY));
    std::optional<Ace::FontStyle> fontStyle = FONT_STYLES[0];
    IndexerModelNG::SetSelectedFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void SetPopupFont(NodeHandle node, const char* fontInfo, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, '|', res);
    std::optional<Dimension> fontSize =
        StringUtils::StringToCalcDimension(res[FONT_SIZE_INDEX], false, DimensionUnit::FP);
    std::optional<FontWeight> fontWeight = StringUtils::StringToFontWeight(res[FONT_WEIGHT_INDEX]);
    std::optional<std::vector<std::string>> fontFamily = Framework::ConvertStrToFontFamilies(res[FONT_FAMILY_INDEX]);
    std::optional<Ace::FontStyle> fontStyle = FONT_STYLES[0];
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        fontStyle = FONT_STYLES[style];
    };
    IndexerModelNG::SetPopupFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void ResetPopupFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> fontSize =
        StringUtils::StringToCalcDimension(DEFAULT_POPUPFONT_SIZE, false, DimensionUnit::FP);
    std::optional<FontWeight> fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    std::optional<std::vector<std::string>> fontFamily =
        Framework::ConvertStrToFontFamilies(std::string(DEFAULT_FONT_FAMILY));
    std::optional<Ace::FontStyle> fontStyle = FONT_STYLES[0];
    IndexerModelNG::SetPopupFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void SetAlphabetIndexerFont(NodeHandle node, const char* fontInfo, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, '|', res);
    std::optional<Dimension> fontSize =
        StringUtils::StringToCalcDimension(res[FONT_SIZE_INDEX], false, DimensionUnit::FP);
    std::optional<FontWeight> fontWeight = StringUtils::StringToFontWeight(res[FONT_WEIGHT_INDEX]);
    std::optional<std::vector<std::string>> fontFamily = Framework::ConvertStrToFontFamilies(res[FONT_FAMILY_INDEX]);
    std::optional<Ace::FontStyle> fontStyle = FONT_STYLES[0];
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        fontStyle = FONT_STYLES[style];
    };
    IndexerModelNG::SetFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void ResetAlphabetIndexerFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> fontSize =
        StringUtils::StringToCalcDimension(DEFAULT_FONT_SIZE, false, DimensionUnit::FP);
    std::optional<FontWeight> fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    std::optional<std::vector<std::string>> fontFamily =
        Framework::ConvertStrToFontFamilies(std::string(DEFAULT_FONT_FAMILY));
    std::optional<Ace::FontStyle> fontStyle = FONT_STYLES[0];
    IndexerModelNG::SetFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void SetPopupItemBackgroundColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupItemBackground(frameNode, Color(color));
}

void ResetPopupItemBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupItemBackground(frameNode, Color(DEFAULT_ITEM_BG_COLOR));
}

void SetAlphabetIndexerColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetColor(frameNode, Color(color));
}

void ResetAlphabetIndexerColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetColor(frameNode, Color(DEFAULT_COLOR));
}

void SetPopupColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupColor(frameNode, Color(color));
}

void ResetPopupColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupColor(frameNode, Color(DEFAULT_POPUP_COLOR));
}

void SetAlphabetIndexerSelectedColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedColor(frameNode, Color(color));
}

void ResetAlphabetIndexerSelectedColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedColor(frameNode, Color(DEFAULT_SELECTED_COLOR));
}

void SetPopupBackground(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupBackground(frameNode, Color(color));
}

void ResetPopupBackground(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupBackground(frameNode, Color(DEFAULT_POPUP_BG_COLOR));
}

void SetSelectedBackgroundColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
}

void ResetSelectedBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedBackgroundColor(frameNode, Color(DEFAULT_SELECTED_BG_COLOR));
}

void SetPopupUnselectedColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupUnselectedColor(frameNode, Color(color));
}

void ResetPopupUnselectedColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupUnselectedColor(frameNode, Color(DEFAULT_POPUP_SELECTED_COLOR));
}

void SetAlignStyle(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAlignStyle(frameNode, value);
}

void ResetAlignStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAlignStyle(frameNode, DEFAULT_ALIGN_STYLE);
}

void SetPopupHorizontalSpace(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupHorizontalSpace(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetPopupHorizontalSpace(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupHorizontalSpace(frameNode, DEFAULT_POPUPHORIZONTALSPACE);
}

void SetUsingPopup(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetUsingPopup(frameNode, value);
}

void ResetUsingPopup(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetUsingPopup(frameNode, DEFAULT_USINGPOPUP);
}

void SetAlphabetIndexerSelected(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelected(frameNode, value);
}

void ResetAlphabetIndexerSelected(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelected(frameNode, DEFAULT_SELECTED);
}

void SetPopupSelectedColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupSelectedColor(frameNode, Color(color));
}
void ResetPopupSelectedColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupSelectedColor(frameNode, Color(DEFAULT_POPUP_SELECTED_COLOR));
}

void SetItemSize(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetItemSize(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetItemSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetItemSize(frameNode, Dimension(DEFAULT_ITEM_SIZE, DimensionUnit::VP));
}

void SetPopupPosition(NodeHandle node, double xValue, int xUnit, double yValue, int yUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupPositionX(frameNode, Dimension(xValue, static_cast<OHOS::Ace::DimensionUnit>(xUnit)));
    IndexerModelNG::SetPopupPositionY(frameNode, Dimension(yValue, static_cast<OHOS::Ace::DimensionUnit>(yUnit)));
}

void ResetPopupPosition(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupPositionX(frameNode, Dimension(DEFAULT_POPUP_POSITION_X, DimensionUnit::VP));
    IndexerModelNG::SetPopupPositionY(frameNode, Dimension(DEFAULT_POPUP_POSITION_Y, DimensionUnit::VP));
}

ArkUIAlphabetIndexerModifierAPI GetAlphabetIndexerModifier()
{
    static const ArkUIAlphabetIndexerModifierAPI modifier = { SetPopupItemFont, ResetPopupItemFont, SetSelectedFont,
        ResetSelectedFont, SetPopupFont, ResetPopupFont, SetAlphabetIndexerFont, ResetAlphabetIndexerFont,
        SetPopupItemBackgroundColor, ResetPopupItemBackgroundColor, SetAlphabetIndexerColor, ResetAlphabetIndexerColor,
        SetPopupColor, ResetPopupColor, SetAlphabetIndexerSelectedColor, ResetAlphabetIndexerSelectedColor,
        SetPopupBackground, ResetPopupBackground, SetSelectedBackgroundColor, ResetSelectedBackgroundColor,
        SetPopupUnselectedColor, ResetPopupUnselectedColor, SetAlignStyle, ResetAlignStyle, SetUsingPopup,
        ResetUsingPopup, SetAlphabetIndexerSelected, ResetAlphabetIndexerSelected, SetPopupHorizontalSpace,
        ResetPopupHorizontalSpace, SetPopupSelectedColor, ResetPopupSelectedColor, SetItemSize, ResetItemSize,
        SetPopupPosition, ResetPopupPosition };

    return modifier;
}
} // namespace OHOS::Ace::NG