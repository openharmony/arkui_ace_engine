/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "ui/base/ace_type.h"

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/common/resource/resource_object.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_model.h"
#include "core/components_ng/pattern/indexer/indexer_model_impl.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/alphabet_indexer_modifier.h"
#include "frameworks/bridge/common/utils/utils.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
Framework::IndexerModelImpl* GetIndexerModelImpl()
{
    static Framework::IndexerModelImpl instance;
    return &instance;
}
} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
namespace {
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
constexpr int FONT_SIZE_INDEX = 0;
constexpr int FONT_WEIGHT_INDEX = 1;
constexpr int FONT_FAMILY_INDEX = 2;
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
constexpr bool DEFAULT_USINGPOPUP = false;
constexpr int32_t DEFAULT_SELECTED = 0;
constexpr Dimension DEFAULT_POPUPHORIZONTALSPACE = -1.0_vp;
constexpr int32_t DEFAULT_ALIGN_STYLE = static_cast<int32_t>(NG::AlignStyle::RIGHT);
constexpr double DEFAULT_ITEM_SIZE = 16.0;
constexpr double DEFAULT_POPUP_POSITION_X = 60.0;
constexpr double DEFAULT_POPUP_POSITION_Y = 48.0;
constexpr double POPUP_ITEM_DEFAULT_RADIUS = 24.0;
constexpr double ITEM_DEFAULT_RADIUS = 8.0;
constexpr double RADIUS_OFFSET = 4.0;
} // namespace

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetPopupItemFont(ArkUINodeHandle node, ArkUI_Float32 size, int unit, const char* weight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fontSize = Dimension(size, static_cast<OHOS::Ace::DimensionUnit>(unit));
    IndexerModelNG::SetFontSize(frameNode, fontSize);
    IndexerModelNG::SetFontWeight(frameNode, StringUtils::StringToFontWeight(std::string(weight), FontWeight::MEDIUM));
}

void ResetPopupItemFont(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto fontSize = indexerTheme->GetPopupTextSize();
    IndexerModelNG::SetFontSize(frameNode, fontSize);
    auto fontWeight = indexerTheme->GetPopupTextStyle().GetFontWeight();
    IndexerModelNG::SetFontWeight(frameNode, fontWeight);
}

void SetSelectedFont(ArkUINodeHandle node, const char* fontInfo, int32_t style)
{
    auto* frameNode = GetFrameNode(node);
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

void ResetSelectedFont(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle selectTextStyle = indexerTheme->GetSelectTextStyle();
    std::optional<Dimension> fontSize = selectTextStyle.GetFontSize();
    std::optional<FontWeight> fontWeight = selectTextStyle.GetFontWeight();
    std::optional<std::vector<std::string>> fontFamily = selectTextStyle.GetFontFamilies();
    std::optional<Ace::FontStyle> fontStyle = selectTextStyle.GetFontStyle();
    IndexerModelNG::SetSelectedFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void SetPopupFont(ArkUINodeHandle node, const char* fontInfo, int32_t style)
{
    auto* frameNode = GetFrameNode(node);
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

void ResetPopupFont(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle popupTextStyle = indexerTheme->GetPopupTextStyle();
    std::optional<Dimension> fontSize = popupTextStyle.GetFontSize();
    std::optional<FontWeight> fontWeight = popupTextStyle.GetFontWeight();
    std::optional<std::vector<std::string>> fontFamily = popupTextStyle.GetFontFamilies();
    std::optional<Ace::FontStyle> fontStyle = popupTextStyle.GetFontStyle();
    IndexerModelNG::SetPopupFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void SetAlphabetIndexerFont(ArkUINodeHandle node, const char* fontInfo, int32_t style)
{
    auto* frameNode = GetFrameNode(node);
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

void ResetAlphabetIndexerFont(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle defaultTextStyle = indexerTheme->GetDefaultTextStyle();
    std::optional<Dimension> fontSize = defaultTextStyle.GetFontSize();
    std::optional<FontWeight> fontWeight = defaultTextStyle.GetFontWeight();
    std::optional<std::vector<std::string>> fontFamily = defaultTextStyle.GetFontFamilies();
    std::optional<Ace::FontStyle> fontStyle = defaultTextStyle.GetFontStyle();
    IndexerModelNG::SetFont(frameNode, fontSize, fontWeight, fontFamily, fontStyle);
}

void SetPopupItemBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupItemBackground(frameNode, Color(color));
    IndexerModelNG::SetPopupItemBackgroundByUser(frameNode, true);
}

void ResetPopupItemBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemovePopupItemBackground(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetPopupUnclickedBgAreaColor();
    IndexerModelNG::SetPopupItemBackground(frameNode, color);
    IndexerModelNG::SetPopupItemBackgroundByUser(frameNode, false);
}

void SetAlphabetIndexerColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetColor(frameNode, Color(color));
    IndexerModelNG::SetColorByUser(frameNode, true);
}

void ResetAlphabetIndexerColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemoveColor(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetDefaultTextColor();
    IndexerModelNG::SetColor(frameNode, color);
    IndexerModelNG::SetColorByUser(frameNode, false);
}

void SetPopupColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupColor(frameNode, Color(color));
    IndexerModelNG::SetPopupColorByUser(frameNode, true);
}

void ResetPopupColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemovePopupColor(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetPopupTextColor();
    IndexerModelNG::SetPopupColor(frameNode, color);
    IndexerModelNG::SetPopupColorByUser(frameNode, false);
}

void SetAlphabetIndexerSelectedColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedColor(frameNode, Color(color));
    IndexerModelNG::SetSelectedColorByUser(frameNode, true);
}

void ResetAlphabetIndexerSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemoveSelectedColor(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetSelectedTextColor();
    IndexerModelNG::SetSelectedColor(frameNode, color);
    IndexerModelNG::SetSelectedColorByUser(frameNode, false);
}

void SetPopupBackground(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupBackground(frameNode, Color(color));
    IndexerModelNG::SetPopupBackgroundByUser(frameNode, true);
}

void ResetPopupBackground(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemovePopupBackground(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetPopupBackgroundColor();
    IndexerModelNG::SetPopupBackground(frameNode, color);
    IndexerModelNG::SetPopupBackgroundByUser(frameNode, false);
}

void SetSelectedBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
    IndexerModelNG::SetSelectedBGColorByUser(frameNode, true);
}

void ResetSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemoveSelectedBackgroundColor(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetSelectedBackgroundColor();
    IndexerModelNG::SetSelectedBackgroundColor(frameNode, color);
    IndexerModelNG::SetSelectedBGColorByUser(frameNode, false);
}

void SetPopupUnselectedColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupUnselectedColor(frameNode, Color(color));
    IndexerModelNG::SetPopupUnselectedColorByUser(frameNode, true);
}

void ResetPopupUnselectedColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemovePopupUnselectedColor(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetPopupUnselectedTextColor();
    IndexerModelNG::SetPopupUnselectedColor(frameNode, color);
    IndexerModelNG::SetPopupUnselectedColorByUser(frameNode, false);
}

void SetAlignStyle(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAlignStyle(frameNode, value);
}

void ResetAlignStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAlignStyle(frameNode, DEFAULT_ALIGN_STYLE);
}

void SetPopupHorizontalSpace(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupHorizontalSpace(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetPopupHorizontalSpace(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupHorizontalSpace(frameNode, DEFAULT_POPUPHORIZONTALSPACE);
}

void SetUsingPopup(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetUsingPopup(frameNode, value);
}

void ResetUsingPopup(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetUsingPopup(frameNode, DEFAULT_USINGPOPUP);
}

void SetAlphabetIndexerSelected(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelected(frameNode, value);
}

void ResetAlphabetIndexerSelected(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelected(frameNode, DEFAULT_SELECTED);
}

void SetPopupSelectedColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupSelectedColor(frameNode, Color(color));
    IndexerModelNG::SetPopupSelectedColorByUser(frameNode, true);
}
void ResetPopupSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemovePopupSelectedColor(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetPopupSelectedTextColor();
    IndexerModelNG::SetPopupSelectedColor(frameNode, color);
    IndexerModelNG::SetPopupSelectedColorByUser(frameNode, false);
}

void SetItemSize(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetItemSize(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetItemSize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetItemSize(frameNode, Dimension(DEFAULT_ITEM_SIZE, DimensionUnit::VP));
}

void SetPopupPosition(ArkUINodeHandle node, ArkUI_Float32 xValue, int xUnit, ArkUI_Float32 yValue, int yUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupPositionX(frameNode, Dimension(xValue, static_cast<OHOS::Ace::DimensionUnit>(xUnit)));
    IndexerModelNG::SetPopupPositionY(frameNode, Dimension(yValue, static_cast<OHOS::Ace::DimensionUnit>(yUnit)));
}

void ResetPopupPosition(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupPositionX(frameNode, Dimension(DEFAULT_POPUP_POSITION_X, DimensionUnit::VP));
    IndexerModelNG::SetPopupPositionY(frameNode, Dimension(DEFAULT_POPUP_POSITION_Y, DimensionUnit::VP));
}

void SetPopupItemBorderRadius(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit,
    ArkUI_Float32 popupValue, ArkUI_Int32 popupUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupItemBorderRadius(
        frameNode, Dimension(radiusValue, static_cast<OHOS::Ace::DimensionUnit>(radiusUnit)));
    IndexerModelNG::SetPopupBorderRadius(
        frameNode, Dimension(popupValue, static_cast<OHOS::Ace::DimensionUnit>(popupUnit)));
}
void ResetPopupItemBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
    auto popupRadius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
    radius.SetValue(POPUP_ITEM_DEFAULT_RADIUS);
    radius.SetUnit(DimensionUnit::VP);
    popupRadius.SetValue(radius.Value() + RADIUS_OFFSET);
    popupRadius.SetUnit(DimensionUnit::VP);
    IndexerModelNG::SetPopupItemBorderRadius(frameNode, radius);
    IndexerModelNG::SetPopupBorderRadius(frameNode, popupRadius);
}
void SetItemBorderRadius(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit,
    ArkUI_Float32 indexerValue, ArkUI_Int32 indexerUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetItemBorderRadius(
        frameNode, Dimension(radiusValue, static_cast<OHOS::Ace::DimensionUnit>(radiusUnit)));
    IndexerModelNG::SetIndexerBorderRadius(
        frameNode, Dimension(indexerValue, static_cast<OHOS::Ace::DimensionUnit>(indexerUnit)));
}
void ResetItemBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
    auto indexerRadius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
    radius.SetValue(ITEM_DEFAULT_RADIUS);
    radius.SetUnit(DimensionUnit::VP);
    indexerRadius.SetValue(radius.Value() + RADIUS_OFFSET);
    indexerRadius.SetUnit(DimensionUnit::VP);
    IndexerModelNG::SetIndexerBorderRadius(frameNode, indexerRadius);
    IndexerModelNG::SetItemBorderRadius(frameNode, radius);
}
void SetPopupBackgroundBlurStyle(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption styleOption;
    if (value >= static_cast<ArkUI_Uint32>(BlurStyle::NO_MATERIAL) &&
        value <= static_cast<ArkUI_Uint32>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(value);
    }
    IndexerModelNG::SetPopupBackgroundBlurStyle(frameNode, styleOption);
}
void ResetPopupBackgroundBlurStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
    IndexerModelNG::SetPopupBackgroundBlurStyle(frameNode, styleOption);
}
void SetPopupTitleBackground(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupTitleBackground(frameNode, Color(color));
    IndexerModelNG::SetPopupTitleBackgroundByUser(frameNode, true);
}
void ResetPopupTitleBackground(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        IndexerModelNG::RemovePopupTitleBackground(frameNode);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color color = indexerTheme->GetPopupTitleBackground();
    IndexerModelNG::SetPopupTitleBackground(frameNode, color);
    IndexerModelNG::SetPopupTitleBackgroundByUser(frameNode, false);
}

void SetAdaptiveWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAdaptiveWidth(frameNode, true);
}

void ResetAdaptiveWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAdaptiveWidth(frameNode, false);
}

void SetArrayValue(ArkUINodeHandle node, ArkUI_CharPtr* value, ArkUI_Uint32 length)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::vector<std::string> valueVector;
    for (uint32_t i = 0; i < length; i++) {
        valueVector.emplace_back(value[i]);
    }
    IndexerModelNG::SetArrayValue(frameNode, valueVector);
}

void ResetArrayValue(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> valueVector;
    IndexerModelNG::SetArrayValue(frameNode, valueVector);
}

void SetAutoCollapse(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAutoCollapse(frameNode, value);
}

void ResetAutoCollapse(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAutoCollapse(frameNode, true);
}

void SetEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetEnableHapticFeedback(frameNode, value);
}

void ResetEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetEnableHapticFeedback(frameNode, true);
}

void SetOnIndexerSelect(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onSelectEvent = reinterpret_cast<std::function<void(int32_t)>*>(extraParam);
        IndexerModelNG::SetOnSelected(frameNode, std::move(*onSelectEvent));
    } else {
        IndexerModelNG::SetOnSelected(frameNode, nullptr);
    }
}

void ResetOnIndexerSelect(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetOnSelected(frameNode, nullptr);
}

void SetOnRequestPopupData(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onRequestPopupData = reinterpret_cast<std::function<std::vector<std::string>(int32_t)>*>(extraParam);
        IndexerModelNG::SetOnRequestPopupData(frameNode, std::move(*onRequestPopupData));
    } else {
        IndexerModelNG::SetOnRequestPopupData(frameNode, nullptr);
    }
}

void ResetOnRequestPopupData(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetOnRequestPopupData(frameNode, nullptr);
}

void SetOnPopupSelected(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onSelectEvent = reinterpret_cast<std::function<void(int32_t)>*>(extraParam);
        IndexerModelNG::SetOnPopupSelected(frameNode, std::move(*onSelectEvent));
    } else {
        IndexerModelNG::SetOnPopupSelected(frameNode, nullptr);
    }
}

void ResetOnPopupSelected(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetOnPopupSelected(frameNode, nullptr);
}

void CreateWithResourceObj(ArkUINodeHandle node, ArkUI_Int32 jsType, void* resObj)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    IndexerModelNG::CreateWithResourceObj(
        frameNode, static_cast<IndexerJsResourceType>(jsType), AceType::Claim(resourceObj));
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId, ArkUI_Bool isArc)
{
    auto frameNode = IndexerModelNG::CreateFrameNode(nodeId, isArc);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void SetIndexerChangeEvent(void* callback)
{
    CHECK_NULL_VOID(callback);
    auto changeEvent = reinterpret_cast<std::function<void(const int32_t selected)>*>(callback);
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetChangeEvent(frameNode, std::move(*changeEvent));
}

void SetIndexerCreateChangeEvent(void* callback)
{
    CHECK_NULL_VOID(callback);
    auto changeEvent = reinterpret_cast<std::function<void(const int32_t selected)>*>(callback);
    CHECK_NULL_VOID(changeEvent);
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetChangeEvent(frameNode, std::move(*changeEvent));
}

void Create(void* arrayValue, ArkUI_Int32 selected, ArkUI_Bool isArc)
{
    CHECK_NULL_VOID(arrayValue);
    auto vecPtr = reinterpret_cast<std::vector<std::string>*>(arrayValue);
    IndexerModelNG::CreateStatic(*vecPtr, selected, isArc);
}

void SetOnIndexerSelected(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const int32_t selected) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ALPHABET_INDEXER_SELECTED;
        event.componentAsyncEvent.data[0].i32 = selected;
        SendArkUISyncEvent(&event);
    };
    IndexerModelNG::SetOnSelected(frameNode, std::move(onEvent));
}

void SetOnIndexerRequestPopupData(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const int32_t selected) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ALPHABET_INDEXER_REQUEST_POPUP_DATA;
        event.componentAsyncEvent.data[0].i32 = selected;
        SendArkUISyncEvent(&event);
        char** valueArray = reinterpret_cast<char**>(event.textArrayEvent.nativeStringArrayPtr);
        ArkUI_Int32 length = event.textArrayEvent.length;
        std::vector<std::string> valueVector;
        if (length != 0 && valueArray != nullptr) {
            for (ArkUI_Int32 i = 0; i < length; i++) {
                valueVector.emplace_back(valueArray[i]);
                free(valueArray[i]);
            }
            free(valueArray);
        }
        return valueVector;
    };
    IndexerModelNG::SetOnRequestPopupData(frameNode, std::move(onEvent));
}

void SetOnIndexerPopupSelected(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const int32_t selected) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ALPHABET_INDEXER_POPUP_SELECTED;
        event.componentAsyncEvent.data[0].i32 = selected;
        SendArkUISyncEvent(&event);
    };
    IndexerModelNG::SetOnPopupSelected(frameNode, std::move(onEvent));
}

void SetIndexerChangeEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const int32_t selected) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ALPHABET_INDEXER_CHANGE_EVENT;
        event.componentAsyncEvent.data[0].i32 = selected;
        SendArkUISyncEvent(&event);
    };
    IndexerModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}

void SetIndexerCreatChangeEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const int32_t selected) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ALPHABET_INDEXER_CREAT_CHANGE_EVENT;
        event.componentAsyncEvent.data[0].i32 = selected;
        SendArkUISyncEvent(&event);
    };
    IndexerModelNG::SetCreatChangeEvent(frameNode, std::move(onEvent));
}

void* GetAsyncEventHandlers(uint32_t kind)
{
    static const ComponentAsyncEventHandler alphabetIndexerNodeAsyncEventHandlers[] = {
        SetOnIndexerSelected,
        SetOnIndexerRequestPopupData,
        SetOnIndexerPopupSelected,
        SetIndexerChangeEvent,
        SetIndexerCreatChangeEvent,
    };
    kind = sizeof(alphabetIndexerNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler);
    if (kind >= sizeof(alphabetIndexerNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(alphabetIndexerNodeAsyncEventHandlers[kind]);
}

void SetSelectedFontJs(void* textStyle)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textStyleObj = reinterpret_cast<IndexerTextStyle*>(textStyle);
    IndexerModelNG::SetSelectedFont(
        frameNode, textStyleObj->fontSize, textStyleObj->fontWeight, textStyleObj->fontFamily, textStyleObj->fontStyle);
}

void SetPopupFontJs(void* textStyle)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textStyleObj = reinterpret_cast<IndexerTextStyle*>(textStyle);
    IndexerModelNG::SetPopupFont(
        frameNode, textStyleObj->fontSize, textStyleObj->fontWeight, textStyleObj->fontFamily, textStyleObj->fontStyle);
}

void SetFontJs(void* textStyle)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textStyleObj = reinterpret_cast<IndexerTextStyle*>(textStyle);
    IndexerModelNG::SetFont(
        frameNode, textStyleObj->fontSize, textStyleObj->fontWeight, textStyleObj->fontFamily, textStyleObj->fontStyle);
}

void SetPopupItemBackgroundColorJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetPopupItemBackground(frameNode, *colorOpt);
}

void SetPopupItemBackgroundColorByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupItemBackgroundByUser(frameNode, setByUser);
}

void SetAlphabetIndexerColorJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetColor(frameNode, *colorOpt);
}

void SetAlphabetIndexerColorByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetColorByUser(frameNode, setByUser);
}

void SetPopupColorJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetPopupColor(frameNode, *colorOpt);
}

void SetPopupColorByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupColorByUser(frameNode, setByUser);
}

void SetSelectedColorJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetSelectedColor(frameNode, *colorOpt);
}

void SetSelectedColorByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedColorByUser(frameNode, setByUser);
}

void SetPopupBackgroundJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetPopupBackground(frameNode, *colorOpt);
}

void SetPopupBackgroundByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupBackgroundByUser(frameNode, setByUser);
}

void SetSelectedBackgroundColorJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetSelectedBackgroundColor(frameNode, *colorOpt);
}

void SetSelectedBackgroundColorByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedBGColorByUser(frameNode, setByUser);
}

void SetPopupUnselectedColorJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetPopupUnselectedColor(frameNode, *colorOpt);
}

void SetPopupUnselectedColorByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupUnselectedColorByUser(frameNode, setByUser);
}

void SetPopupSelectedColorJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetPopupSelectedColor(frameNode, *colorOpt);
}

void SetPopupSelectedColorByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupSelectedColorByUser(frameNode, setByUser);
}

void SetPopupTitleBackgroundJs(void* color)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    IndexerModelNG::SetPopupTitleBackground(frameNode, *colorOpt);
}

void SetPopupTitleBackgroundByUser(ArkUI_Bool setByUser)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupTitleBackgroundByUser(frameNode, setByUser);
}

void SetPopupPositionJs(void* x, void* y)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto xOpt = reinterpret_cast<std::optional<Dimension>*>(x);
    auto yOpt = reinterpret_cast<std::optional<Dimension>*>(y);
    IndexerModelNG::SetPopupPositionX(frameNode, *xOpt);
    IndexerModelNG::SetPopupPositionY(frameNode, *yOpt);
}

#ifndef CROSS_PLATFORM
void SetPopupItemFontImpl(ArkUINodeHandle node, ArkUI_Float32 size, int unit, const char* weight)
{
    Dimension fontSize = Dimension(size, static_cast<OHOS::Ace::DimensionUnit>(unit));
    GetIndexerModelImpl()->SetFontSize(fontSize);
    GetIndexerModelImpl()->SetFontWeight(StringUtils::StringToFontWeight(std::string(weight), FontWeight::MEDIUM));
}

void SetSelectedFontImpl(ArkUINodeHandle node, const char* fontInfo, int32_t style)
{
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
    GetIndexerModelImpl()->SetSelectedFont(fontSize, fontWeight, fontFamily, fontStyle);
}

void SetPopupFontImpl(ArkUINodeHandle node, const char* fontInfo, int32_t style)
{
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
    GetIndexerModelImpl()->SetPopupFont(fontSize, fontWeight, fontFamily, fontStyle);
}

void SetAlphabetIndexerFontImpl(ArkUINodeHandle node, const char* fontInfo, int32_t style)
{
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
    GetIndexerModelImpl()->SetFont(fontSize, fontWeight, fontFamily, fontStyle);
}

void SetPopupItemBackgroundColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetPopupItemBackground(Color(color));
}

void SetAlphabetIndexerColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetColor(Color(color));
    GetIndexerModelImpl()->SetColorByUser(true);
}

void SetPopupColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetPopupColor(Color(color));
    GetIndexerModelImpl()->SetPopupColorByUser(true);
}

void SetAlphabetIndexerSelectedColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetSelectedColor(Color(color));
    GetIndexerModelImpl()->SetSelectedColorByUser(true);
}

void SetPopupBackgroundImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetPopupBackground(Color(color));
}

void SetSelectedBackgroundColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetSelectedBackgroundColor(Color(color));
    GetIndexerModelImpl()->SetSelectedBGColorByUser(true);
}

void SetPopupUnselectedColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetPopupUnselectedColor(Color(color));
    GetIndexerModelImpl()->SetPopupUnselectedColorByUser(true);
}

void SetAlignStyleImpl(ArkUINodeHandle node, int32_t value)
{
    GetIndexerModelImpl()->SetAlignStyle(value);
}

void SetPopupHorizontalSpaceImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    GetIndexerModelImpl()->SetPopupHorizontalSpace(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetUsingPopupImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetIndexerModelImpl()->SetUsingPopup(value);
}

void SetAlphabetIndexerSelectedImpl(ArkUINodeHandle node, int32_t value)
{
    GetIndexerModelImpl()->SetSelected(value);
}

void SetPopupSelectedColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetIndexerModelImpl()->SetPopupSelectedColor(Color(color));
    GetIndexerModelImpl()->SetPopupSelectedColorByUser(true);
}

void SetItemSizeImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    GetIndexerModelImpl()->SetItemSize(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetPopupPositionImpl(ArkUINodeHandle node, ArkUI_Float32 xValue, int xUnit, ArkUI_Float32 yValue, int yUnit)
{
    GetIndexerModelImpl()->SetPopupPositionX(Dimension(xValue, static_cast<OHOS::Ace::DimensionUnit>(xUnit)));
    GetIndexerModelImpl()->SetPopupPositionY(Dimension(yValue, static_cast<OHOS::Ace::DimensionUnit>(yUnit)));
}

void SetPopupItemBorderRadiusImpl(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit,
    ArkUI_Float32 popupValue, ArkUI_Int32 popupUnit)
{
    GetIndexerModelImpl()->SetPopupItemBorderRadius(
        Dimension(radiusValue, static_cast<OHOS::Ace::DimensionUnit>(radiusUnit)));
    GetIndexerModelImpl()->SetPopupBorderRadius(
        Dimension(popupValue, static_cast<OHOS::Ace::DimensionUnit>(popupUnit)));
}

void SetItemBorderRadiusImpl(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit,
    ArkUI_Float32 indexerValue, ArkUI_Int32 indexerUnit)
{
    GetIndexerModelImpl()->SetItemBorderRadius(
        Dimension(radiusValue, static_cast<OHOS::Ace::DimensionUnit>(radiusUnit)));
    GetIndexerModelImpl()->SetIndexerBorderRadius(
        Dimension(indexerValue, static_cast<OHOS::Ace::DimensionUnit>(indexerUnit)));
}

void SetPopupBackgroundBlurStyleImpl(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    BlurStyleOption styleOption;
    if (value >= static_cast<ArkUI_Uint32>(BlurStyle::NO_MATERIAL) &&
        value <= static_cast<ArkUI_Uint32>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(value);
    }
    GetIndexerModelImpl()->SetPopupBackgroundBlurStyle(styleOption);
}

void SetPopupTitleBackgroundImpl(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    GetIndexerModelImpl()->SetPopupTitleBackground(Color(color));
    GetIndexerModelImpl()->SetPopupTitleBackgroundByUser(true);
}

void SetAdaptiveWidthImpl(ArkUINodeHandle node)
{
    GetIndexerModelImpl()->SetAdaptiveWidth(true);
}

void SetAutoCollapseImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetIndexerModelImpl()->SetAutoCollapse(value);
}

void SetEnableHapticFeedbackImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetIndexerModelImpl()->SetEnableHapticFeedback(value);
}

void SetOnIndexerSelectImpl(ArkUINodeHandle node, void* extraParam)
{
    if (extraParam) {
        auto onSelectEvent = reinterpret_cast<std::function<void(int32_t)>*>(extraParam);
        GetIndexerModelImpl()->SetOnSelected(std::move(*onSelectEvent));
    } else {
        GetIndexerModelImpl()->SetOnSelected(nullptr);
    }
}

void SetOnRequestPopupDataImpl(ArkUINodeHandle node, void* extraParam)
{
    if (extraParam) {
        auto onRequestPopupData = reinterpret_cast<std::function<std::vector<std::string>(int32_t)>*>(extraParam);
        GetIndexerModelImpl()->SetOnRequestPopupData(std::move(*onRequestPopupData));
    } else {
        GetIndexerModelImpl()->SetOnRequestPopupData(nullptr);
    }
}

void SetOnPopupSelectedImpl(ArkUINodeHandle node, void* extraParam)
{
    if (extraParam) {
        auto onSelectEvent = reinterpret_cast<std::function<void(int32_t)>*>(extraParam);
        GetIndexerModelImpl()->SetOnPopupSelected(std::move(*onSelectEvent));
    } else {
        GetIndexerModelImpl()->SetOnPopupSelected(nullptr);
    }
}

void CreateWithResourceObjImpl(ArkUINodeHandle node, ArkUI_Int32 jsType, void* resObj)
{
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    GetIndexerModelImpl()->CreateWithResourceObj(
        static_cast<IndexerJsResourceType>(jsType), AceType::Claim(resourceObj));
}

void SetIndexerChangeEventImpl(void* callback)
{
    CHECK_NULL_VOID(callback);
    auto changeEvent = reinterpret_cast<std::function<void(const int32_t selected)>*>(callback);
    GetIndexerModelImpl()->SetChangeEvent(std::move(*changeEvent));
}

void SetIndexerCreateChangeEventImpl(void* callback)
{
    CHECK_NULL_VOID(callback);
    auto changeEvent = reinterpret_cast<std::function<void(const int32_t selected)>*>(callback);
    CHECK_NULL_VOID(changeEvent);
    GetIndexerModelImpl()->SetChangeEvent(std::move(*changeEvent));
}

void CreateImpl(void* arrayValue, ArkUI_Int32 selected, ArkUI_Bool isArc)
{
    CHECK_NULL_VOID(arrayValue);
    auto vecPtr = reinterpret_cast<std::vector<std::string>*>(arrayValue);
    GetIndexerModelImpl()->Create(*vecPtr, selected, isArc);
}

void SetSelectedFontJsImpl(void* textStyle)
{
    auto textStyleObj = reinterpret_cast<IndexerTextStyle*>(textStyle);
    GetIndexerModelImpl()->SetSelectedFont(
        textStyleObj->fontSize, textStyleObj->fontWeight, textStyleObj->fontFamily, textStyleObj->fontStyle);
}

void SetPopupFontJsImpl(void* textStyle)
{
    auto textStyleObj = reinterpret_cast<IndexerTextStyle*>(textStyle);
    GetIndexerModelImpl()->SetPopupFont(
        textStyleObj->fontSize, textStyleObj->fontWeight, textStyleObj->fontFamily, textStyleObj->fontStyle);
}

void SetFontJsImpl(void* textStyle)
{
    auto textStyleObj = reinterpret_cast<IndexerTextStyle*>(textStyle);
    GetIndexerModelImpl()->SetFont(
        textStyleObj->fontSize, textStyleObj->fontWeight, textStyleObj->fontFamily, textStyleObj->fontStyle);
}

void SetPopupItemBackgroundColorJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetPopupItemBackground(*colorOpt);
}

void SetPopupItemBackgroundColorByUserImpl(ArkUI_Bool setByUser) {}

void SetAlphabetIndexerColorJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetColor(*colorOpt);
}

void SetAlphabetIndexerColorByUserImpl(ArkUI_Bool setByUser)
{
    GetIndexerModelImpl()->SetColorByUser(setByUser);
}

void SetPopupColorJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetPopupColor(*colorOpt);
}

void SetPopupColorByUserImpl(ArkUI_Bool setByUser)
{
    GetIndexerModelImpl()->SetPopupColorByUser(setByUser);
}

void SetSelectedColorJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetSelectedColor(*colorOpt);
}

void SetSelectedColorByUserImpl(ArkUI_Bool setByUser)
{
    GetIndexerModelImpl()->SetSelectedColorByUser(setByUser);
}

void SetPopupBackgroundJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetPopupBackground(*colorOpt);
}

void SetPopupBackgroundByUserImpl(ArkUI_Bool setByUser) {}

void SetSelectedBackgroundColorJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetSelectedBackgroundColor(*colorOpt);
}

void SetSelectedBackgroundColorByUserImpl(ArkUI_Bool setByUser)
{
    GetIndexerModelImpl()->SetSelectedBGColorByUser(setByUser);
}

void SetPopupUnselectedColorJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetPopupUnselectedColor(*colorOpt);
}

void SetPopupUnselectedColorByUserImpl(ArkUI_Bool setByUser)
{
    GetIndexerModelImpl()->SetPopupUnselectedColorByUser(setByUser);
}

void SetPopupSelectedColorJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetPopupSelectedColor(*colorOpt);
}

void SetPopupSelectedColorByUserImpl(ArkUI_Bool setByUser)
{
    GetIndexerModelImpl()->SetPopupSelectedColorByUser(setByUser);
}

void SetPopupTitleBackgroundJsImpl(void* color)
{
    auto colorOpt = reinterpret_cast<std::optional<Color>*>(color);
    GetIndexerModelImpl()->SetPopupTitleBackground(*colorOpt);
}

void SetPopupTitleBackgroundByUserImpl(ArkUI_Bool setByUser)
{
    GetIndexerModelImpl()->SetPopupTitleBackgroundByUser(setByUser);
}

void SetPopupPositionJsImpl(void* x, void* y)
{
    auto xOpt = reinterpret_cast<std::optional<Dimension>*>(x);
    auto yOpt = reinterpret_cast<std::optional<Dimension>*>(y);
    GetIndexerModelImpl()->SetPopupPositionX(*xOpt);
    GetIndexerModelImpl()->SetPopupPositionY(*yOpt);
}
#endif

const ArkUIAlphabetIndexerModifier* GetAlphabetIndexerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIAlphabetIndexerModifier modifier = {
            .setPopupItemFont = SetPopupItemFontImpl,
            .resetPopupItemFont = nullptr,
            .setSelectedFont = SetSelectedFontImpl,
            .resetSelectedFont = nullptr,
            .setPopupFont = SetPopupFontImpl,
            .resetPopupFont = nullptr,
            .setAlphabetIndexerFont = SetAlphabetIndexerFontImpl,
            .resetAlphabetIndexerFont = nullptr,
            .setPopupItemBackgroundColor = SetPopupItemBackgroundColorImpl,
            .resetPopupItemBackgroundColor = nullptr,
            .setAlphabetIndexerColor = SetAlphabetIndexerColorImpl,
            .resetAlphabetIndexerColor = nullptr,
            .setPopupColor = SetPopupColor,
            .resetPopupColor = nullptr,
            .setAlphabetIndexerSelectedColor = SetAlphabetIndexerSelectedColorImpl,
            .resetAlphabetIndexerSelectedColor = nullptr,
            .setPopupBackground = SetPopupBackgroundImpl,
            .resetPopupBackground = nullptr,
            .setSelectedBackgroundColor = SetSelectedBackgroundColorImpl,
            .resetSelectedBackgroundColor = nullptr,
            .setPopupUnselectedColor = SetPopupUnselectedColorImpl,
            .resetPopupUnselectedColor = nullptr,
            .setAlignStyle = SetAlignStyleImpl,
            .resetAlignStyle = nullptr,
            .setUsingPopup = SetUsingPopupImpl,
            .resetUsingPopup = nullptr,
            .setAlphabetIndexerSelected = SetAlphabetIndexerSelectedImpl,
            .resetAlphabetIndexerSelected = nullptr,
            .setPopupHorizontalSpace = SetPopupHorizontalSpaceImpl,
            .resetPopupHorizontalSpace = nullptr,
            .setPopupSelectedColor = SetPopupSelectedColorImpl,
            .resetPopupSelectedColor = nullptr,
            .setItemSize = SetItemSizeImpl,
            .resetItemSize = nullptr,
            .setPopupPosition = SetPopupPositionImpl,
            .resetPopupPosition = nullptr,
            .setPopupItemBorderRadius = SetPopupItemBorderRadiusImpl,
            .resetPopupItemBorderRadius = nullptr,
            .setItemBorderRadius = SetItemBorderRadiusImpl,
            .resetItemBorderRadius = nullptr,
            .setPopupBackgroundBlurStyle = SetPopupBackgroundBlurStyleImpl,
            .resetPopupBackgroundBlurStyle = nullptr,
            .setPopupTitleBackground = SetPopupTitleBackgroundImpl,
            .resetPopupTitleBackground = nullptr,
            .setAdaptiveWidth = SetAdaptiveWidthImpl,
            .resetAdaptiveWidth = nullptr,
            .setArrayValue = nullptr,
            .resetArrayValue = nullptr,
            .setAutoCollapse = SetAutoCollapseImpl,
            .resetAutoCollapse = nullptr,
            .setEnableHapticFeedback = SetEnableHapticFeedbackImpl,
            .resetEnableHapticFeedback = nullptr,
            .setOnIndexerSelect = SetOnIndexerSelectImpl,
            .resetOnIndexerSelect = nullptr,
            .setOnRequestPopupData = SetOnRequestPopupDataImpl,
            .resetOnRequestPopupData = nullptr,
            .setOnPopupSelected = SetOnPopupSelectedImpl,
            .resetOnPopupSelected = nullptr,
            .createWithResourceObj = CreateWithResourceObjImpl,
            .createFrameNode = nullptr,
            .setIndexerChangeEvent = SetIndexerChangeEventImpl,
            .setIndexerCreateChangeEvent = SetIndexerCreateChangeEventImpl,
            .create = CreateImpl,
            .getAsyncEventHandlers = nullptr,
            .setSelectedFontJs = SetSelectedFontJsImpl,
            .setPopupFontJs = SetPopupFontJsImpl,
            .setFontJs = SetFontJs,
            .setPopupItemBackgroundColorJs = SetPopupItemBackgroundColorJsImpl,
            .setPopupItemBackgroundColorByUser = SetPopupItemBackgroundColorByUserImpl,
            .setAlphabetIndexerColorJs = SetAlphabetIndexerColorJsImpl,
            .setAlphabetIndexerColorByUser = SetAlphabetIndexerColorByUserImpl,
            .setPopupColorJs = SetPopupColorJsImpl,
            .setPopupColorByUser = SetPopupColorByUserImpl,
            .setSelectedColorJs = SetSelectedColorJsImpl,
            .setSelectedColorByUser = SetSelectedColorByUserImpl,
            .setPopupBackgroundJs = SetPopupBackgroundJsImpl,
            .setPopupBackgroundByUser = SetPopupBackgroundByUserImpl,
            .setSelectedBackgroundColorJs = SetSelectedBackgroundColorJsImpl,
            .setSelectedBackgroundColorByUser = SetSelectedBackgroundColorByUserImpl,
            .setPopupUnselectedColorJs = SetPopupUnselectedColorJsImpl,
            .setPopupUnselectedColorByUser = SetPopupUnselectedColorByUserImpl,
            .setPopupSelectedColorJs = SetPopupSelectedColorJsImpl,
            .setPopupSelectedColorByUser = SetPopupSelectedColorByUserImpl,
            .setPopupTitleBackgroundJs = SetPopupTitleBackgroundJsImpl,
            .setPopupTitleBackgroundByUser = SetPopupTitleBackgroundByUserImpl,
            .setPopupPositionJs = SetPopupPositionJsImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
#endif

    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIAlphabetIndexerModifier modifier = {
        .setPopupItemFont = SetPopupItemFont,
        .resetPopupItemFont = ResetPopupItemFont,
        .setSelectedFont = SetSelectedFont,
        .resetSelectedFont = ResetSelectedFont,
        .setPopupFont = SetPopupFont,
        .resetPopupFont = ResetPopupFont,
        .setAlphabetIndexerFont = SetAlphabetIndexerFont,
        .resetAlphabetIndexerFont = ResetAlphabetIndexerFont,
        .setPopupItemBackgroundColor = SetPopupItemBackgroundColor,
        .resetPopupItemBackgroundColor = ResetPopupItemBackgroundColor,
        .setAlphabetIndexerColor = SetAlphabetIndexerColor,
        .resetAlphabetIndexerColor = ResetAlphabetIndexerColor,
        .setPopupColor = SetPopupColor,
        .resetPopupColor = ResetPopupColor,
        .setAlphabetIndexerSelectedColor = SetAlphabetIndexerSelectedColor,
        .resetAlphabetIndexerSelectedColor = ResetAlphabetIndexerSelectedColor,
        .setPopupBackground = SetPopupBackground,
        .resetPopupBackground = ResetPopupBackground,
        .setSelectedBackgroundColor = SetSelectedBackgroundColor,
        .resetSelectedBackgroundColor = ResetSelectedBackgroundColor,
        .setPopupUnselectedColor = SetPopupUnselectedColor,
        .resetPopupUnselectedColor = ResetPopupUnselectedColor,
        .setAlignStyle = SetAlignStyle,
        .resetAlignStyle = ResetAlignStyle,
        .setUsingPopup = SetUsingPopup,
        .resetUsingPopup = ResetUsingPopup,
        .setAlphabetIndexerSelected = SetAlphabetIndexerSelected,
        .resetAlphabetIndexerSelected = ResetAlphabetIndexerSelected,
        .setPopupHorizontalSpace = SetPopupHorizontalSpace,
        .resetPopupHorizontalSpace = ResetPopupHorizontalSpace,
        .setPopupSelectedColor = SetPopupSelectedColor,
        .resetPopupSelectedColor = ResetPopupSelectedColor,
        .setItemSize = SetItemSize,
        .resetItemSize = ResetItemSize,
        .setPopupPosition = SetPopupPosition,
        .resetPopupPosition = ResetPopupPosition,
        .setPopupItemBorderRadius = SetPopupItemBorderRadius,
        .resetPopupItemBorderRadius = ResetPopupItemBorderRadius,
        .setItemBorderRadius = SetItemBorderRadius,
        .resetItemBorderRadius = ResetItemBorderRadius,
        .setPopupBackgroundBlurStyle = SetPopupBackgroundBlurStyle,
        .resetPopupBackgroundBlurStyle = ResetPopupBackgroundBlurStyle,
        .setPopupTitleBackground = SetPopupTitleBackground,
        .resetPopupTitleBackground = ResetPopupTitleBackground,
        .setAdaptiveWidth = SetAdaptiveWidth,
        .resetAdaptiveWidth = ResetAdaptiveWidth,
        .setArrayValue = SetArrayValue,
        .resetArrayValue = ResetArrayValue,
        .setAutoCollapse = SetAutoCollapse,
        .resetAutoCollapse = ResetAutoCollapse,
        .setEnableHapticFeedback = SetEnableHapticFeedback,
        .resetEnableHapticFeedback = ResetEnableHapticFeedback,
        .setOnIndexerSelect = SetOnIndexerSelect,
        .resetOnIndexerSelect = ResetOnIndexerSelect,
        .setOnRequestPopupData = SetOnRequestPopupData,
        .resetOnRequestPopupData = ResetOnRequestPopupData,
        .setOnPopupSelected = SetOnPopupSelected,
        .resetOnPopupSelected = ResetOnPopupSelected,
        .createWithResourceObj = CreateWithResourceObj,
        .createFrameNode = CreateFrameNode,
        .setIndexerChangeEvent = SetIndexerChangeEvent,
        .setIndexerCreateChangeEvent = SetIndexerCreateChangeEvent,
        .create = Create,
        .getAsyncEventHandlers = GetAsyncEventHandlers,
        .setSelectedFontJs = SetSelectedFontJs,
        .setPopupFontJs = SetPopupFontJs,
        .setFontJs = SetFontJs,
        .setPopupItemBackgroundColorJs = SetPopupItemBackgroundColorJs,
        .setPopupItemBackgroundColorByUser = SetPopupItemBackgroundColorByUser,
        .setAlphabetIndexerColorJs = SetAlphabetIndexerColorJs,
        .setAlphabetIndexerColorByUser = SetAlphabetIndexerColorByUser,
        .setPopupColorJs = SetPopupColorJs,
        .setPopupColorByUser = SetPopupColorByUser,
        .setSelectedColorJs = SetSelectedColorJs,
        .setSelectedColorByUser = SetSelectedColorByUser,
        .setPopupBackgroundJs = SetPopupBackgroundJs,
        .setPopupBackgroundByUser = SetPopupBackgroundByUser,
        .setSelectedBackgroundColorJs = SetSelectedBackgroundColorJs,
        .setSelectedBackgroundColorByUser = SetSelectedBackgroundColorByUser,
        .setPopupUnselectedColorJs = SetPopupUnselectedColorJs,
        .setPopupUnselectedColorByUser = SetPopupUnselectedColorByUser,
        .setPopupSelectedColorJs = SetPopupSelectedColorJs,
        .setPopupSelectedColorByUser = SetPopupSelectedColorByUser,
        .setPopupTitleBackgroundJs = SetPopupTitleBackgroundJs,
        .setPopupTitleBackgroundByUser = SetPopupTitleBackgroundByUser,
        .setPopupPositionJs = SetPopupPositionJs,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIAlphabetIndexerModifier* GetCJUIAlphabetIndexerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIAlphabetIndexerModifier modifier = {
        .setPopupItemFont = SetPopupItemFont,
        .resetPopupItemFont = ResetPopupItemFont,
        .setSelectedFont = SetSelectedFont,
        .resetSelectedFont = ResetSelectedFont,
        .setPopupFont = SetPopupFont,
        .resetPopupFont = ResetPopupFont,
        .setAlphabetIndexerFont = SetAlphabetIndexerFont,
        .resetAlphabetIndexerFont = ResetAlphabetIndexerFont,
        .setPopupItemBackgroundColor = SetPopupItemBackgroundColor,
        .resetPopupItemBackgroundColor = ResetPopupItemBackgroundColor,
        .setAlphabetIndexerColor = SetAlphabetIndexerColor,
        .resetAlphabetIndexerColor = ResetAlphabetIndexerColor,
        .setPopupColor = SetPopupColor,
        .resetPopupColor = ResetPopupColor,
        .setAlphabetIndexerSelectedColor = SetAlphabetIndexerSelectedColor,
        .resetAlphabetIndexerSelectedColor = ResetAlphabetIndexerSelectedColor,
        .setPopupBackground = SetPopupBackground,
        .resetPopupBackground = ResetPopupBackground,
        .setSelectedBackgroundColor = SetSelectedBackgroundColor,
        .resetSelectedBackgroundColor = ResetSelectedBackgroundColor,
        .setPopupUnselectedColor = SetPopupUnselectedColor,
        .resetPopupUnselectedColor = ResetPopupUnselectedColor,
        .setAlignStyle = SetAlignStyle,
        .resetAlignStyle = ResetAlignStyle,
        .setUsingPopup = SetUsingPopup,
        .resetUsingPopup = ResetUsingPopup,
        .setAlphabetIndexerSelected = SetAlphabetIndexerSelected,
        .resetAlphabetIndexerSelected = ResetAlphabetIndexerSelected,
        .setPopupHorizontalSpace = SetPopupHorizontalSpace,
        .resetPopupHorizontalSpace = ResetPopupHorizontalSpace,
        .setPopupSelectedColor = SetPopupSelectedColor,
        .resetPopupSelectedColor = ResetPopupSelectedColor,
        .setItemSize = SetItemSize,
        .resetItemSize = ResetItemSize,
        .setPopupPosition = SetPopupPosition,
        .resetPopupPosition = ResetPopupPosition,
        .setPopupItemBorderRadius = SetPopupItemBorderRadius,
        .resetPopupItemBorderRadius = ResetPopupItemBorderRadius,
        .setItemBorderRadius = SetItemBorderRadius,
        .resetItemBorderRadius = ResetItemBorderRadius,
        .setPopupBackgroundBlurStyle = SetPopupBackgroundBlurStyle,
        .resetPopupBackgroundBlurStyle = ResetPopupBackgroundBlurStyle,
        .setPopupTitleBackground = SetPopupTitleBackground,
        .resetPopupTitleBackground = ResetPopupTitleBackground,
        .setAdaptiveWidth = SetAdaptiveWidth,
        .resetAdaptiveWidth = ResetAdaptiveWidth,
        .setAutoCollapse = SetAutoCollapse,
        .resetAutoCollapse = ResetAutoCollapse,
        .setEnableHapticFeedback = SetEnableHapticFeedback,
        .resetEnableHapticFeedback = ResetEnableHapticFeedback,
        .setArrayValue = SetArrayValue,
        .resetArrayValue = ResetArrayValue,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

} // namespace OHOS::Ace::NG
