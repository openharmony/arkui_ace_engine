/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_text_modifier.h"

#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/font/constants_converter.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "frameworks/core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int DEFAULT_SELECTION = -1;
constexpr Dimension DEFAULT_LINE_HEIGHT = Dimension(0.0, DimensionUnit::PX);
constexpr Dimension DEFAULT_LINE_SPACING = Dimension(0.0, DimensionUnit::PX);
constexpr bool DEFAULT_TRIM_SPACE = false;
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr TextCase DEFAULT_TEXT_CASE = TextCase::NORMAL;
constexpr uint32_t DEFAULT_MAX_LINE = Infinity<uint32_t>();
constexpr bool DEFAULT_TEXT_DRAGGABLE = false;
constexpr bool DEFAULT_TEXT_SENSITIVE = false;
constexpr Dimension DEFAULT_MAX_FONT_SIZE;
constexpr Dimension DEFAULT_MIN_FONT_SIZE;
constexpr float DEFAULT_MIN_FONT_SCALE = 0.0f;
constexpr float DEFAULT_MAX_FONT_SCALE = static_cast<float>(INT32_MAX);
constexpr CopyOptions DEFAULT_COPY_OPTION = CopyOptions::None;
constexpr Dimension DEFAULT_BASELINE_OFFSET = 0.0_fp;
constexpr Dimension DEFAULT_FONT_SIZE = 16.0_fp;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr int32_t DEFAULT_VARIABLE_FONT_WEIGHT = 400;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";
const std::string EMPTY_STRING = "";
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
const std::vector<OHOS::Ace::TextAlign> TEXT_ALIGNS = { OHOS::Ace::TextAlign::START, OHOS::Ace::TextAlign::CENTER,
    OHOS::Ace::TextAlign::END, OHOS::Ace::TextAlign::JUSTIFY, OHOS::Ace::TextAlign::LEFT, OHOS::Ace::TextAlign::RIGHT };
const std::vector<TextContentAlign> TEXT_CONTENT_ALIGNS = { TextContentAlign::TOP, TextContentAlign::CENTER,
    TextContentAlign::BOTTOM };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<EllipsisMode> ELLIPSIS_MODALS = { EllipsisMode::HEAD, EllipsisMode::MIDDLE, EllipsisMode::TAIL };
const std::vector<TextSelectableMode> TEXT_SELECTABLE_MODE = { TextSelectableMode::SELECTABLE_UNFOCUSABLE,
    TextSelectableMode::SELECTABLE_FOCUSABLE, TextSelectableMode::UNSELECTABLE };
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE = true;
constexpr bool DEFAULT_ENABLE_TEXT_DETECTOR = false;
const std::vector<std::string> TEXT_DETECT_TYPES = { "phoneNum", "url", "email", "location", "datetime" };
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int NUM_9 = 9;
constexpr int NUM_10 = 10;
constexpr float DEFAULT_ANGLE = 180.0f;
constexpr double PERCENT_100 = 100.0;

std::map<TextHeightAdaptivePolicy, int> TEXT_HEIGHT_ADAPTIVE_POLICY_MAP = {
    { TextHeightAdaptivePolicy::MAX_LINES_FIRST, 0 },
    { TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, 1 },
    { TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST, 2 } };

const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;

FontWeight ConvertStrToFontWeight(ArkUI_CharPtr weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}
namespace {

thread_local std::string g_strValue;
void SetTextContent(ArkUINodeHandle node, ArkUI_CharPtr value, void* contentRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::u16string content = UtfUtils::Str8DebugToStr16(std::string(value));
    TextModelNG::InitText(frameNode, content);
    NodeModifier::ProcessResourceObj<std::u16string>(frameNode, "Content", content, contentRawPtr);
}

const char* GetTextContent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = UtfUtils::Str16DebugToStr8(TextModelNG::GetContent(frameNode));
    return g_strValue.c_str();
}

void SetFontWeightStr(ArkUINodeHandle node, ArkUI_CharPtr weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, ConvertStrToFontWeight(weight));
}

void SetFontWeightWithOption(ArkUINodeHandle node, const struct ArkUIFontWeightWithOptionsStruct* weightInfo)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, ConvertStrToFontWeight(weightInfo->weight));
    TextModelNG::SetVariableFontWeight(frameNode, weightInfo->variableFontWeight);
    TextModelNG::SetEnableVariableFontWeight(frameNode, weightInfo->enableVariableFontWeight);
}

void SetFontWeight(ArkUINodeHandle node, ArkUI_Int32 weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(weight));
    TextModelNG::SetVariableFontWeight(frameNode, DEFAULT_VARIABLE_FONT_WEIGHT);
    TextModelNG::SetEnableVariableFontWeight(frameNode, false);
}

void SetImmutableFontWeight(ArkUINodeHandle node, ArkUI_Int32 weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(weight));
    TextModelNG::SetVariableFontWeight(frameNode, Constants::GetVariableFontWeight(static_cast<FontWeight>(weight)));
    TextModelNG::SetEnableVariableFontWeight(frameNode, true);
}

void SetOnClick(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GestureEventFunc* click = nullptr;
    if (callback) {
        click = reinterpret_cast<GestureEventFunc*>(callback);
        TextModelNG::SetOnClick(frameNode, std::move(*click));
    } else {
        TextModelNG::SetOnClick(frameNode, nullptr);
    }
}

void ResetOnClick(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ClearOnClick(frameNode);
}

void SetResponseRegion(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (int32_t i = 0; i < length / NUM_4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * NUM_4 + NUM_0], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_0]));
        CalcDimension yDimen =
            CalcDimension(values[i * NUM_4 + NUM_1], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_1]));
        CalcDimension widthDimen =
            CalcDimension(values[i * NUM_4 + NUM_2], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i * NUM_4 + NUM_3], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    TextModelNG::SetResponseRegion(frameNode, region);
}

void ResetResponseRegion(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ClearResponseRegion(frameNode);
}
void ResetFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, Ace::FontWeight::NORMAL);
    TextModelNG::SetVariableFontWeight(frameNode, DEFAULT_VARIABLE_FONT_WEIGHT);
    TextModelNG::SetEnableVariableFontWeight(frameNode, false);
}

void SetFontStyle(ArkUINodeHandle node, ArkUI_Uint32 fontStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (fontStyle < 0 || fontStyle >= FONT_STYLES.size()) {
        return;
    }
    TextModelNG::SetItalicFontStyle(frameNode, FONT_STYLES[fontStyle]);
}

void ResetFontStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetItalicFontStyle(frameNode, OHOS::Ace::FontStyle::NORMAL);
}

void SetTextAlign(ArkUINodeHandle node, ArkUI_Uint32 testAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (testAlign < 0 || testAlign >= TEXT_ALIGNS.size()) {
        return;
    }
    TextModelNG::SetTextAlign(frameNode, TEXT_ALIGNS[testAlign]);
}

int32_t GetTextAlign(ArkUINodeHandle node)
{
    auto defaultTextAlign = static_cast<int32_t>(OHOS::Ace::TextAlign::START);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultTextAlign);
    return static_cast<int32_t>(TextModelNG::GetTextAlign(frameNode));
}

void ResetTextAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextAlign(frameNode, OHOS::Ace::TextAlign::START);
}

void SetTextContentAlign(ArkUINodeHandle node, ArkUI_Uint32 testContentAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (testContentAlign < 0 || testContentAlign >= TEXT_CONTENT_ALIGNS.size()) {
        return;
    }
    TextModelNG::SetTextContentAlign(frameNode, TEXT_CONTENT_ALIGNS[testContentAlign]);
}

int32_t GetTextContentAlign(ArkUINodeHandle node)
{
    auto defaultTextContentAlign = static_cast<int32_t>(OHOS::Ace::TextContentAlign::TOP);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultTextContentAlign);
    return static_cast<int32_t>(TextModelNG::GetTextContentAlign(frameNode));
}

void ResetTextContentAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ReSetTextContentAlign(frameNode);
}

void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* fontColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextColor(frameNode, Color(color));
    NodeModifier::ProcessResourceObj<Color>(frameNode, "TextColor", Color(color), fontColorRawPtr);
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ResetTextColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("TextColor");
    }
}

uint32_t GetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, Color::BLACK.GetValue());
    return TextModelNG::GetFontColor(frameNode).GetValue();
}

void SetTextForegroundColor(ArkUINodeHandle node, ArkUI_Bool isColor, uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (isColor) {
        TextModelNG::SetTextColor(frameNode, Color(color));
        NodeModifier::ProcessResourceObj<Color>(frameNode, "TextColor", Color(color), colorRawPtr);
    } else {
        TextModelNG::SetTextColor(frameNode, Color::FOREGROUND);
        auto strategy = static_cast<ForegroundColorStrategy>(color);
        ViewAbstract::SetForegroundColorStrategy(frameNode, strategy);
    }
}

void ResetTextForegroundColor(ArkUINodeHandle node)
{
    ResetFontColor(node);
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, ArkUI_Int32 unit, void* fontSizeRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (fontSize < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        TextModelNG::SetFontSize(frameNode, fontSize);
    } else {
        auto fontSizeValue = Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit));
        TextModelNG::SetFontSize(frameNode, fontSizeValue);
        NodeModifier::ProcessResourceObj<CalcDimension>(frameNode, "FontSize", fontSizeValue, fontSizeRawPtr);
    }
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    TextModelNG::SetFontSize(frameNode, fontSize);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("FontSize");
    }
}

void SetTextLineHeight(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* lineHeightRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto value = Dimension(number, static_cast<DimensionUnit>(unit));
    value.ResetInvalidValue();
    TextModelNG::SetLineHeight(frameNode, value);
    NodeModifier::ProcessResourceObj<CalcDimension>(
        frameNode, "LineHeight", Dimension(number, static_cast<DimensionUnit>(unit)), lineHeightRawPtr);
}

float GetTextLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return TextModelNG::GetLineHeight(frameNode);
}

void ResetTextLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineHeight(frameNode, DEFAULT_LINE_HEIGHT);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("LineHeight");
    }
}

void SetTextTextOverflow(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextOverflow valueTextOverflow = static_cast<TextOverflow>(value);
    TextModelNG::SetTextOverflow(frameNode, valueTextOverflow);
}

int32_t GetTextTextOverflow(ArkUINodeHandle node)
{
    int defaultTextOverflow = static_cast<int32_t>(TextOverflow::NONE);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultTextOverflow);
    return static_cast<int32_t>(TextModelNG::GetTextOverflow(frameNode));
}

void ResetTextTextOverflow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextOverflow(frameNode, TextOverflow::NONE);
}

void SetTextDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, void* colorRawPtr,
    ArkUI_Int32 style, ArkUI_Float32 lineThicknessScale = 1.0f)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    TextModelNG::SetTextDecorationColor(frameNode, Color(color));
    NodeModifier::ProcessResourceObj<Color>(frameNode, "TextDecorationColor", Color(color), colorRawPtr);
    TextModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
    TextModelNG::SetLineThicknessScale(frameNode, lineThicknessScale);
}

void SetTextDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style)
{
    SetTextDecoration(node, decoration, color, nullptr, style, 1.0f); // make cj happy
}

void GetTextDecoration(ArkUINodeHandle node, ArkUITextDecorationType* decoration)
{
    CHECK_NULL_VOID(decoration);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    decoration->decorationType = static_cast<int32_t>(TextModelNG::GetDecoration(frameNode));
    decoration->color = TextModelNG::GetTextDecorationColor(frameNode).GetValue();
    decoration->style = static_cast<int32_t>(TextModelNG::GetTextDecorationStyle(frameNode));
}

void ResetTextDecoration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    TextModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
    TextModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("TextDecorationColor");
    }
}

void SetTextTextCase(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextCase(frameNode, static_cast<TextCase>(value));
}

int32_t GetTextTextCase(ArkUINodeHandle node)
{
    int32_t defaultTextCase = static_cast<int32_t>(DEFAULT_TEXT_CASE);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultTextCase);
    return static_cast<int32_t>(TextModelNG::GetTextCase(frameNode));
}

void ResetTextTextCase(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextCase(frameNode, DEFAULT_TEXT_CASE);
}

void SetTextMaxLines(ArkUINodeHandle node, ArkUI_Uint32 maxLine)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxLines(frameNode, maxLine);
}

int32_t GetTextMaxLines(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_MAX_LINE);
    return TextModelNG::GetMaxLines(frameNode);
}

void ResetTextMaxLines(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxLines(frameNode, DEFAULT_MAX_LINE);
}

void SetTextMinFontSize(ArkUINodeHandle node, ArkUI_Float32 number, const ArkUI_Int32 unit, void* minFontSizeRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMinFontSize(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    NodeModifier::ProcessResourceObj<CalcDimension>(
        frameNode, "AdaptMinFontSize", Dimension(number, static_cast<DimensionUnit>(unit)), minFontSizeRawPtr);
}

void ResetTextMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMinFontSize(frameNode, DEFAULT_MIN_FONT_SIZE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("AdaptMinFontSize");
    }
}

void SetTextDraggable(ArkUINodeHandle node, ArkUI_Uint32 draggable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDraggable(frameNode, static_cast<bool>(draggable));
}

void ResetTextDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDraggable(frameNode, DEFAULT_TEXT_DRAGGABLE);
}

void SetTextPrivacySensitve(ArkUINodeHandle node, ArkUI_Uint32 sensitive)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(static_cast<bool>(sensitive));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ResetTextPrivacySensitve(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(DEFAULT_TEXT_SENSITIVE);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SetTextMaxFontSize(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* maxFontSizeRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMaxFontSize(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    NodeModifier::ProcessResourceObj<CalcDimension>(
        frameNode, "AdaptMaxFontSize", Dimension(number, static_cast<DimensionUnit>(unit)), maxFontSizeRawPtr);
}

void ResetTextMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMaxFontSize(frameNode, DEFAULT_MAX_FONT_SIZE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("AdaptMaxFontSize");
    }
}

void SetTextMinFontScale(ArkUINodeHandle node, ArkUI_Float32 number, void* minFontScaleRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMinFontScale(frameNode, number);
    NodeModifier::ProcessResourceObj<float>(frameNode, "MinFontScale", number, minFontScaleRawPtr);
}

void ResetTextMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMinFontScale(frameNode, DEFAULT_MIN_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("MinFontScale");
    }
}

void SetTextMaxFontScale(ArkUINodeHandle node, ArkUI_Float32 number, void* maxFontScaleRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxFontScale(frameNode, number);
    NodeModifier::ProcessResourceObj<float>(frameNode, "MaxFontScale", number, maxFontScaleRawPtr);
}

void ResetTextMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxFontScale(frameNode, DEFAULT_MAX_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("MaxFontScale");
    }
}

void SetTextFontFamily(ArkUINodeHandle node, const char** fontFamilies, ArkUI_Uint32 length, void* fontFamilyRawPtr)
{
    CHECK_NULL_VOID(fontFamilies);
    if (length <= 0) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families;
    for (uint32_t i = 0; i < length; i++) {
        const char* family = *(fontFamilies + i);
        if (family != nullptr) {
            families.emplace_back(std::string(family));
        }
    }
    TextModelNG::SetFontFamily(frameNode, families);
    NodeModifier::ProcessResourceObj<std::vector<std::string>>(frameNode, "FontFamily", families, fontFamilyRawPtr);
}

void ResetTextFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FAMILY);
    TextModelNG::SetFontFamily(frameNode, families);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("FontFamily");
    }
}

void SetTextCopyOption(ArkUINodeHandle node, ArkUI_Int32 copyOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetCopyOption(frameNode, static_cast<CopyOptions>(copyOption));
}

void ResetTextCopyOption(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetCopyOption(frameNode, DEFAULT_COPY_OPTION);
}

void SetTextTextShadow(ArkUINodeHandle node, struct ArkUITextShadowStruct* shadows, ArkUI_Uint32 length,
    const void* radiusResArrs, const void* colorResArrs,
    const void* offsetXResArrs, const void* offsetYResArrs)
{
    CHECK_NULL_VOID(shadows);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    std::vector<RefPtr<ResourceObject>> radiusResArr;
    std::vector<RefPtr<ResourceObject>> colorResArr;
    std::vector<RefPtr<ResourceObject>> offsetXResArr;
    std::vector<RefPtr<ResourceObject>> offsetYResArr;
    if (SystemProperties::ConfigChangePerform()) {
            if (radiusResArrs != nullptr) {
            radiusResArr = *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(radiusResArrs));
        }
        if (colorResArrs != nullptr) {
            colorResArr =
                *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(colorResArrs));
        }
        if (offsetXResArrs != nullptr) {
            offsetXResArr =
                *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(offsetXResArrs));
        }
        if (offsetYResArrs != nullptr) {
            offsetYResArr =
            *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(offsetYResArrs));
        }
    }
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        ArkUITextShadowStruct* shadowStruct = shadows + i;
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
        if (SystemProperties::ConfigChangePerform()) {
            RefPtr<ResourceObject> radiusObject = (radiusResArr.size() > i) ? radiusResArr[i] : nullptr;
            RefPtr<ResourceObject> colorObject = (colorResArr.size() > i) ? colorResArr[i] : nullptr;
            RefPtr<ResourceObject> offsetXObject = (offsetXResArr.size() > i) ? offsetXResArr[i] : nullptr;
            RefPtr<ResourceObject> offsetYObject = (offsetYResArr.size() > i) ? offsetYResArr[i] : nullptr;
            Shadow::RegisterShadowResourceObj(shadow, radiusObject, colorObject, offsetXObject, offsetYObject);
        }
        shadowList.at(i) = shadow;
    }
    TextModelNG::SetTextShadow(frameNode, shadowList);
}

ArkUI_Uint32 GetTextShadowCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return TextModelNG::GetTextShadow(frameNode).size();
}

void GetTextShadow(ArkUINodeHandle node, ArkUITextShadowStruct* shadow, uint32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ArkUITextShadowStruct> shadowArray;
    auto textShadowVector = TextModelNG::GetTextShadow(frameNode);
    for (uint32_t i = 0; i < size; i++) {
        if (i < textShadowVector.size()) {
            *(shadow + i) = { static_cast<float>(textShadowVector[i].GetBlurRadius()),
                static_cast<int32_t>(textShadowVector[i].GetShadowType()), textShadowVector[i].GetColor().GetValue(),
                textShadowVector[i].GetOffset().GetX(), textShadowVector[i].GetOffset().GetY(),
                textShadowVector[i].GetIsFilled()};
        } else {
            *(shadow + i) = { 0.0f, static_cast<int32_t>(ShadowType::COLOR), Color::TRANSPARENT.GetValue(), 0.0f, 0.0f,
                0 };
        }
    }
}

void ResetTextTextShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    shadow.SetOffsetX(0.0);
    shadow.SetOffsetY(0.0);
    TextModelNG::SetTextShadow(frameNode, std::vector<Shadow> { shadow });
}

void SetTextHeightAdaptivePolicy(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    value = std::clamp(value, 0, static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size()));
    TextModelNG::SetHeightAdaptivePolicy(frameNode, HEIGHT_ADAPTIVE_POLICY[value]);
}

void ResetTextHeightAdaptivePolicy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHeightAdaptivePolicy(frameNode, TextHeightAdaptivePolicy::MAX_LINES_FIRST);
}

void SetTextTextIndent(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* textIndentRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextIndent(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    NodeModifier::ProcessResourceObj<CalcDimension>(
        frameNode, "TextIndent", Dimension(number, static_cast<DimensionUnit>(unit)), textIndentRawPtr);
}

float GetTextTextIndent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return TextModelNG::GetTextIndent(frameNode).ConvertToVp();
}

void ResetTextTextIndent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextIndent(frameNode, CalcDimension(0, DimensionUnit::FP));
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("TextIndent");
    }
}

void SetTextBaselineOffset(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* baselineOffsetRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetBaselineOffset(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    NodeModifier::ProcessResourceObj<CalcDimension>(
        frameNode, "BaselineOffset", Dimension(number, static_cast<DimensionUnit>(unit)), baselineOffsetRawPtr);
}

void ResetTextBaselineOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetBaselineOffset(frameNode, DEFAULT_BASELINE_OFFSET);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("BaselineOffset");
    }
}

ArkUI_Float32 GetTextBaselineOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return TextModelNG::GetTextBaselineOffset(frameNode).ConvertToVp();
}

void SetTextLetterSpacing(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLetterSpacing(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    NodeModifier::ProcessResourceObj<CalcDimension>(
        frameNode, "LetterSpacing", Dimension(number, static_cast<DimensionUnit>(unit)), resObj);
}

ArkUI_Float32 GetTextLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return TextModelNG::GetLetterSpacing(frameNode).ConvertToVp();
}

void ResetTextLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension letterSpacing(0.0, DimensionUnit::FP);
    TextModelNG::SetLetterSpacing(frameNode, letterSpacing);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("LetterSpacing");
    }
}

void SetTextFont(ArkUINodeHandle node, const struct ArkUIFontWithOptionsStruct* fontInfo,
    void* fontSizeRawPtr, void* fontFamilyRawPtr)
{
    CHECK_NULL_VOID(fontInfo);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = Dimension(fontInfo->fontSizeNumber, static_cast<DimensionUnit>(fontInfo->fontSizeUnit));
    font.fontStyle = static_cast<Ace::FontStyle>(fontInfo->fontStyle);
    font.fontWeight = static_cast<FontWeight>(fontInfo->fontWeight);
    std::vector<std::string> families;
    if (fontInfo->fontFamilies && fontInfo->familyLength > 0) {
        if (fontInfo->familyLength > DEFAULT_MAX_FONT_FAMILY_LENGTH) {
            return;
        }
        families.resize(fontInfo->familyLength);
        for (uint32_t i = 0; i < fontInfo->familyLength; i++) {
            families.at(i) = std::string(*(fontInfo->fontFamilies + i));
        }
    }
    font.fontFamilies = families;
    TextModelNG::SetFont(frameNode, font);
    TextModelNG::SetVariableFontWeight(frameNode, fontInfo->variableFontWeight);
    TextModelNG::SetEnableVariableFontWeight(frameNode, fontInfo->enableVariableFontWeight);
    auto fontSizeValue = Dimension(fontInfo->fontSizeNumber, static_cast<DimensionUnit>(fontInfo->fontSizeUnit));
    NodeModifier::ProcessResourceObj<CalcDimension>(frameNode, "FontSize", fontSizeValue, fontSizeRawPtr);
    NodeModifier::ProcessResourceObj<std::vector<std::string>>(frameNode, "FontFamily", families, fontFamilyRawPtr);
}

void ResetTextFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FAMILY);
    font.fontFamilies = families;
    TextModelNG::SetFont(frameNode, font);
    TextModelNG::SetVariableFontWeight(frameNode, DEFAULT_VARIABLE_FONT_WEIGHT);
    TextModelNG::SetEnableVariableFontWeight(frameNode, false);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("FontSize");
        pattern->UnRegisterResource("FontFamily");
    }
}

void SetWordBreak(ArkUINodeHandle node, ArkUI_Uint32 wordBreak)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (wordBreak < 0 || wordBreak >= WORD_BREAK_TYPES.size()) {
        wordBreak = 2; // 2 is the default value of WordBreak::BREAK_WORD
    }
    TextModelNG::SetWordBreak(frameNode, WORD_BREAK_TYPES[wordBreak]);
}

void ResetWordBreak(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetWordBreak(frameNode, WORD_BREAK_TYPES[2]); // 2 is the default value of WordBreak::BREAK_WORD
}

void SetEllipsisMode(ArkUINodeHandle node, ArkUI_Uint32 ellipsisMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (ellipsisMode < 0 || ellipsisMode >= ELLIPSIS_MODALS.size()) {
        ellipsisMode = 2; // 2 is the default value of EllipsisMode::TAIL
    }
    TextModelNG::SetEllipsisMode(frameNode, ELLIPSIS_MODALS[ellipsisMode]);
}

void ResetEllipsisMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetEllipsisMode(frameNode, ELLIPSIS_MODALS[2]); // 2 is the default value of EllipsisMode::TAIL
}

void SetTextDetectEnable(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDetectEnable(frameNode, static_cast<bool>(value));
}

ArkUI_Int32 GetTextDetectEnable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetTextDetectEnable(frameNode));
}

void ResetTextDetectEnable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDetectEnable(frameNode, DEFAULT_ENABLE_TEXT_DETECTOR);
}

ArkUI_CharPtr GetFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::vector<std::string> fontFamilies = TextModelNG::GetFontFamily(frameNode);
    std::string families;
    //set index start
    uint32_t index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != fontFamilies.size() - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = families;
    return g_strValue.c_str();
}

ArkUI_Int32 GetCopyOption(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetCopyOption(frameNode));
}

ArkUI_Int32 GetHeightAdaptivePolicy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TEXT_HEIGHT_ADAPTIVE_POLICY_MAP[TextModelNG::GetHeightAdaptivePolicy(frameNode)];
}

ArkUI_Float32 GetTextMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Float32>(TextModelNG::GetAdaptMinFontSize(frameNode).Value());
}

ArkUI_Float32 GetTextMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Float32>(TextModelNG::GetAdaptMaxFontSize(frameNode).Value());
}

void GetFont(ArkUINodeHandle node, ArkUITextFont* font)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font value = TextModelNG::GetFont(frameNode);
    if (value.fontSize.has_value()) {
        font->fontSize = value.fontSize.value().GetNativeValue(static_cast<DimensionUnit>(font->fontSizeUnit));
    }
    if (value.fontWeight.has_value()) {
        font->fontWeight = static_cast<ArkUI_Int32>(value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        std::string families;
        //set index start
        std::size_t index = 0;
        for (auto& family : value.fontFamilies) {
            families += family;
            if (index != value.fontFamilies.size() - 1) {
                families += ",";
            }
            index++;
        }
        g_strValue = families;
        font->fontFamilies = g_strValue.c_str();
    } else {
        font->fontFamilies = "HarmonyOS Sans";
    }
    if (value.fontStyle.has_value()) {
        font->fontStyle = static_cast<ArkUI_Int32>(value.fontStyle.value());
    }
}

ArkUI_Float32 GetFontSize(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Float32>(
        TextModelNG::GetFontSize(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit)));
}

ArkUI_Int32 GetFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetFontWeight(frameNode));
}

ArkUI_Int32 GetLineCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetLineCount(frameNode));
}

ArkUI_Int32 GetItalicFontStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetItalicFontStyle(frameNode));
}

ArkUI_Int32 GetTextWordBreak(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetWordBreak(frameNode));
}

ArkUI_Int32 GetTextEllipsisMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetEllipsisMode(frameNode));
}

void SetTextFontFeature(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = value;
    TextModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void ResetTextFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = "";
    TextModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void SetTextDataDetectorConfig(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size)
{
    std::string textTypes;
    for (int i = 0; i < size; i++) {
        auto index = values[i];
        if (index < 0 || index >= TEXT_DETECT_TYPES.size()) {
            continue;
        }
        if (i != 0) {
            textTypes.append(",");
        }
        textTypes.append(TEXT_DETECT_TYPES[index]);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDetectConfig(frameNode, textTypes);
}

ArkUI_Int32 GetTextDataDetectorConfig(ArkUINodeHandle node, ArkUI_Int32 (*values)[32])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto typeString = TextModelNG::GetTextDetectConfig(frameNode);
    std::vector<std::string> types;
    StringUtils::StringSplitter(typeString, ',', types);
    for (uint32_t i = 0; i < types.size(); i++) {
        auto ret = std::find(TEXT_DETECT_TYPES.begin(), TEXT_DETECT_TYPES.end(), types[i]);
        (*values)[i] = ret != TEXT_DETECT_TYPES.end() ? ret - TEXT_DETECT_TYPES.begin() : -1;
    }
    return types.size();
}

void ResetTextDataDetectorConfig(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDetectConfig(frameNode, "");
}

ArkUI_CharPtr GetTextFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = UnParseFontFeatureSetting(TextModelNG::GetFontFeature(frameNode));
    return g_strValue.c_str();
}

void SetTextLineSpacing(
    ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, ArkUI_Bool isOnlyBetweenLines, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineSpacing(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)), isOnlyBetweenLines);
    NodeModifier::ProcessResourceObj<CalcDimension>(
        frameNode, "LineSpacing", Dimension(number, static_cast<DimensionUnit>(unit)), resObj);
}

float GetTextLineSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return TextModelNG::GetLineSpacing(frameNode);
}

void ResetTextLineSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineSpacing(frameNode, DEFAULT_LINE_SPACING, false);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("LineSpacing");
    }
}

void SetTextCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* caretColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetCaretColor(frameNode, Color(color));
    NodeModifier::ProcessResourceObj<Color>(frameNode, "TextCaretColor", Color(color), caretColorRawPtr);
}

ArkUI_Uint32 GetTextCaretColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, Color::BLACK.GetValue());
    return TextModelNG::GetCaretColor(frameNode).GetValue();
}

void ResetTextCaretColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto caretColor = static_cast<int32_t>(theme->GetCaretColor().GetValue());
    TextModelNG::SetCaretColor(frameNode, Color(caretColor));
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("TextCaretColor");
    }
}

void SetTextSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* selectedBackgroundColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
    NodeModifier::ProcessResourceObj<Color>(
        frameNode, "SelectedBackgroundColor", Color(color), selectedBackgroundColorRawPtr);
}

ArkUI_Uint32 GetTextSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, Color::BLACK.GetValue());
    return TextModelNG::GetSelectedBackgroundColor(frameNode).GetValue();
}

void ResetTextSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ResetSelectedBackgroundColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("SelectedBackgroundColor");
    }
}

void SetLineBreakStrategy(ArkUINodeHandle node, ArkUI_Uint32 lineBreakStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (lineBreakStrategy < 0 || lineBreakStrategy >= LINE_BREAK_STRATEGY_TYPES.size()) {
        lineBreakStrategy = 0; // 0 is the default value of LineBreakStrategy::GREEDY
    }
    TextModelNG::SetLineBreakStrategy(frameNode, LINE_BREAK_STRATEGY_TYPES[lineBreakStrategy]);
}

void ResetLineBreakStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // 0 is the default value of LineBreakStrategy::GREEDY
    TextModelNG::SetLineBreakStrategy(frameNode, LINE_BREAK_STRATEGY_TYPES[0]);
}

ArkUI_Int32 GetTextLineBreakStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextModelNG::GetLineBreakStrategy(frameNode));
}

void SetTextContentWithStyledString(ArkUINodeHandle node, ArkUI_StyledString* styledString)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(styledString);
    TextModelNG::SetTextContentWithStyledString(frameNode, styledString);
}

void ResetTextContentWithStyledString(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextContentWithStyledString(frameNode, nullptr);
}

void SetTextSelection(ArkUINodeHandle node, int32_t startIndex, int32_t endIndex)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextSelection(frameNode, startIndex, endIndex);
}

void ResetTextSelection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextSelection(frameNode, DEFAULT_SELECTION, DEFAULT_SELECTION);
}

void SetTextSelectableMode(ArkUINodeHandle node, ArkUI_Uint32 textSelectableMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (textSelectableMode < 0 || textSelectableMode >= TEXT_SELECTABLE_MODE.size()) {
        textSelectableMode = 0;
    }
    TextModelNG::SetTextSelectableMode(frameNode, TEXT_SELECTABLE_MODE[textSelectableMode]);
}

void ResetTextSelectableMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextSelectableMode(frameNode, TEXT_SELECTABLE_MODE[0]);
}

void SetTextDataDetectorConfigWithEvent(
    ArkUINodeHandle node, const struct ArkUITextDetectConfigStruct* arkUITextDetectConfig, void* entityColorRawPtr,
    void* entityDecorationColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = arkUITextDetectConfig->types;
    if (arkUITextDetectConfig->onResult) {
        textDetectConfig.onResult =
            std::move(*(reinterpret_cast<std::function<void(const std::string&)>*>(arkUITextDetectConfig->onResult)));
    }
    textDetectConfig.entityColor = Color(arkUITextDetectConfig->entityColor);
    textDetectConfig.entityDecorationType = TextDecoration(arkUITextDetectConfig->entityDecorationType);
    textDetectConfig.entityDecorationColor = Color(arkUITextDetectConfig->entityDecorationColor);
    textDetectConfig.entityDecorationStyle = TextDecorationStyle(arkUITextDetectConfig->entityDecorationStyle);
    textDetectConfig.enablePreviewMenu = arkUITextDetectConfig->entityEnablePreviewMenu;
    if (SystemProperties::ConfigChangePerform()) {
        if (entityColorRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(entityColorRawPtr));
            TextDetectConfig::RegisterColorResource(textDetectConfig, resObj);
        }
        if (entityDecorationColorRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(entityDecorationColorRawPtr));
            TextDetectConfig::RegisterDecoColorResource(textDetectConfig, resObj);
        }
    }
    TextModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void ResetTextDataDetectorConfigWithEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    TextModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("dataDetectorConfig");
    }
}

void SetTextOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        TextModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        TextModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetTextOnCopy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetOnCopy(frameNode, nullptr);
}

void SetTextOnTextSelectionChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
        TextModelNG::SetOnTextSelectionChange(frameNode, std::move(*onChange));
    } else {
        TextModelNG::SetOnTextSelectionChange(frameNode, nullptr);
    }
}

void ResetTextOnTextSelectionChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetOnTextSelectionChange(frameNode, nullptr);
}

void SetTextSelectionMenuOptions(
    ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback, void* onPrepareMenuCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (onCreateMenuCallback) {
        NG::OnCreateMenuCallback onCreateMenu = *(reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback));
        TextModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenu));
    } else {
        TextModelNG::OnCreateMenuCallbackUpdate(frameNode, nullptr);
    }
    if (onMenuItemClickCallback) {
        NG::OnMenuItemClickCallback onMenuItemClick =
            *(reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback));
        TextModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
    } else {
        TextModelNG::OnMenuItemClickCallbackUpdate(frameNode, nullptr);
    }
    if (onPrepareMenuCallback) {
        NG::OnPrepareMenuCallback onPrepareMenu =
            *(reinterpret_cast<NG::OnPrepareMenuCallback*>(onPrepareMenuCallback));
        TextModelNG::OnPrepareMenuCallbackUpdate(frameNode, std::move(onPrepareMenu));
    } else {
        TextModelNG::OnPrepareMenuCallbackUpdate(frameNode, nullptr);
    }
}

void SetTextSelectionMenuOptionsForCJ(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback)
{
    SetTextSelectionMenuOptions(node, onCreateMenuCallback, onMenuItemClickCallback, nullptr);
}

void ResetTextSelectionMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    TextModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenuCallback));
    TextModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
    TextModelNG::OnPrepareMenuCallbackUpdate(frameNode, std::move(onPrepareMenuCallback));
}

void SetTextHalfLeading(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHalfLeading(frameNode, value);
}

void ResetTextHalfLeading(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHalfLeading(frameNode, false);
}

ArkUI_Int32 GetTextHalfLeading(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Int32>(TextModelNG::GetHalfLeading(frameNode));
}

void SetTextEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetEnableHapticFeedback(frameNode, static_cast<bool>(value));
}

void ResetTextEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetEnableHapticFeedback(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE);
}

void SetMarqueeOptions(ArkUINodeHandle node, struct ArkUITextMarqueeOptions* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    TextMarqueeOptions marqueeOptions;
    marqueeOptions.UpdateTextMarqueeStart(value->start);
    marqueeOptions.UpdateTextMarqueeStep(value->step);
    marqueeOptions.UpdateTextMarqueeLoop(value->loop);
    marqueeOptions.UpdateTextMarqueeDirection(value->fromStart ? MarqueeDirection::LEFT : MarqueeDirection::RIGHT);
    marqueeOptions.UpdateTextMarqueeDelay(value->delay);
    marqueeOptions.UpdateTextMarqueeFadeout(value->fadeout);
    marqueeOptions.UpdateTextMarqueeStartPolicy(static_cast<MarqueeStartPolicy>(value->marqueeStartPolicy));

    TextModelNG::SetMarqueeOptions(frameNode, marqueeOptions);
}

void ResetMarqueeOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextMarqueeOptions marqueeOptions;
    TextModelNG::SetMarqueeOptions(frameNode, marqueeOptions);
}

void SetOnMarqueeStateChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int32_t)>*>(callback);
        TextModelNG::SetOnMarqueeStateChange(frameNode, std::move(*onChange));
    } else {
        TextModelNG::SetOnMarqueeStateChange(frameNode, nullptr);
    }
}

void ResetOnMarqueeStateChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetOnMarqueeStateChange(frameNode, nullptr);
}

void SetTextOptimizeTrailingSpace(ArkUINodeHandle node, ArkUI_Bool trim)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetOptimizeTrailingSpace(frameNode, trim);
}

ArkUI_Int32 GetTextOptimizeTrailingSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Int32>(TextModelNG::GetOptimizeTrailingSpace(frameNode));
}

void ResetTextOptimizeTrailingSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetOptimizeTrailingSpace(frameNode, DEFAULT_TRIM_SPACE);
}

void SetEnableAutoSpacing(ArkUINodeHandle node, ArkUI_Bool enableAutoSpacing)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetEnableAutoSpacing(frameNode, static_cast<bool>(enableAutoSpacing));
}

void ResetEnableAutoSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetEnableAutoSpacing(frameNode, false);
}

void SetLinearGradientDirectionTo(std::shared_ptr<LinearGradient>& linearGradient, const GradientDirection direction)
{
    switch (direction) {
        case GradientDirection::LEFT:
            linearGradient->linearX = NG::GradientDirection::LEFT;
            break;
        case GradientDirection::RIGHT:
            linearGradient->linearX = NG::GradientDirection::RIGHT;
            break;
        case GradientDirection::TOP:
            linearGradient->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::BOTTOM:
            linearGradient->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::LEFT_TOP:
            linearGradient->linearX = NG::GradientDirection::LEFT;
            linearGradient->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::LEFT_BOTTOM:
            linearGradient->linearX = NG::GradientDirection::LEFT;
            linearGradient->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::RIGHT_TOP:
            linearGradient->linearX = NG::GradientDirection::RIGHT;
            linearGradient->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::RIGHT_BOTTOM:
            linearGradient->linearX = NG::GradientDirection::RIGHT;
            linearGradient->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::NONE:
        case GradientDirection::START_TO_END:
        case GradientDirection::END_TO_START:
        default:
            break;
    }
}

GradientDirection ConvertToLinearGradientDirection(std::shared_ptr<LinearGradient> linearGradient)
{
    auto linearX = linearGradient->linearX;
    auto linearY = linearGradient->linearY;
    if (!linearX.has_value() && !linearY.has_value()) {
        return GradientDirection::BOTTOM;
    }
    if (linearX.has_value() && !linearY.has_value()) {
        return linearX.value();
    }
    if (!linearX.has_value() && linearY.has_value()) {
        return linearY.value();
    }

    if (linearX.value() == NG::GradientDirection::LEFT && linearY.value() == NG::GradientDirection::TOP) {
        return GradientDirection::LEFT_TOP;
    }
    if (linearX.value() == NG::GradientDirection::LEFT && linearY.value() == NG::GradientDirection::BOTTOM) {
        return GradientDirection::LEFT_BOTTOM;
    }
    if (linearX.value() == NG::GradientDirection::RIGHT && linearY.value() == NG::GradientDirection::TOP) {
        return GradientDirection::RIGHT_TOP;
    }
    if (linearX.value() == NG::GradientDirection::RIGHT && linearY.value() == NG::GradientDirection::BOTTOM) {
        return GradientDirection::RIGHT_BOTTOM;
    }
    return GradientDirection::BOTTOM;
}

/**
 * @param values value value
 * values[0], values[1] : angle: hasValue, angle value
 * values[2] : direction
 * values[3] : repeating
 * @param valuesLength values length
 */
void SetLinearGradientValues(NG::Gradient& gradient, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_4)) {
        return;
    }
    auto angleHasValue = values[NUM_0].i32;
    auto angleValue = values[NUM_1].f32;
    auto directionValue = values[NUM_2].i32;
    auto repeating = values[NUM_3].i32;
    auto linearGradient = gradient.GetLinearGradient();
    if (linearGradient == nullptr) {
        return;
    }
    if (static_cast<bool>(angleHasValue)) {
        linearGradient->angle = CalcDimension(angleValue, DimensionUnit::PX);
    }
    SetLinearGradientDirectionTo(linearGradient, static_cast<GradientDirection>(directionValue));
    gradient.SetRepeat(static_cast<bool>(repeating));
}

/**
 * @param values value value
 * values[0], values[1], values[2] : centerX Dimension: hasValue, value, unit
 * values[3], values[4], values[5] : centerY Dimension: hasValue, value, unit
 * values[6], values[7], values[8] : radius: Dimension: hasValue, value, unit
 * values[9] : repeating
 * @param valuesLength values length
 */
void SetRadialGradientValues(NG::Gradient& gradient, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_10)) {
        return;
    }

    auto centerXHasValue = values[NUM_0].i32;
    auto centerXValue = values[NUM_1].f32;
    auto centerXUnit = values[NUM_2].i32;
    auto centerYHasValue = values[NUM_3].i32;
    auto centerYValue = values[NUM_4].f32;
    auto centerYUnit = values[NUM_5].i32;
    auto radiusHasValue = values[NUM_6].i32;
    auto radiusValue = values[NUM_7].f32;
    auto radiusUnit = values[NUM_8].i32;
    auto repeating = values[NUM_9].i32;

    if (static_cast<bool>(centerXHasValue)) {
        auto unit = static_cast<DimensionUnit>(centerXUnit);
        auto value = (unit == DimensionUnit::PERCENT) ? (centerXValue * PERCENT_100) : centerXValue;
        gradient.GetRadialGradient()->radialCenterX = CalcDimension(value, unit);
    }
    if (static_cast<bool>(centerYHasValue)) {
        auto unit = static_cast<DimensionUnit>(centerYUnit);
        auto value = (unit == DimensionUnit::PERCENT) ? (centerYValue * PERCENT_100) : centerYValue;
        gradient.GetRadialGradient()->radialCenterY = CalcDimension(value, unit);
    }
    if (static_cast<bool>(radiusHasValue)) {
        auto unit = static_cast<DimensionUnit>(radiusUnit);
        auto value = static_cast<float>(radiusValue);
        gradient.GetRadialGradient()->radialVerticalSize = CalcDimension(value, unit);
        gradient.GetRadialGradient()->radialHorizontalSize = CalcDimension(value, unit);
    }
    gradient.SetRepeat(static_cast<bool>(repeating));
}

/**
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetGradientColors(NG::Gradient& gradient, const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
{
    if ((colors == nullptr) || (colorsLength % NUM_3) != 0) {
        return;
    }
    for (int32_t index = 0; index < colorsLength; index += NUM_3) {
        auto colorValue = colors[index].u32;
        auto colorHasDimension = colors[index + NUM_1].i32;
        auto colorDimension = colors[index + NUM_2].f32;
        auto color = static_cast<uint32_t>(colorValue);
        auto hasDimension = static_cast<bool>(colorHasDimension);
        auto dimension = colorDimension;
        NG::GradientColor gradientColor;
        gradientColor.SetColor(Color(color));
        gradientColor.SetHasValue(hasDimension);
        if (hasDimension) {
            gradientColor.SetDimension(CalcDimension(dimension * PERCENT_100, DimensionUnit::PERCENT));
        }
        gradient.AddColor(gradientColor);
    }
}

/**
 * @param values value value
 * values[0], values[1] : angle: hasValue, angle value
 * values[2] : direction
 * values[3] : repeating
 * @param valuesLength values length
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetTextLinearGradient(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
    const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesLength != NUM_4) || ((colorsLength % NUM_3) != 0)) {
        return;
    }
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    SetLinearGradientValues(gradient, values, valuesLength);
    SetGradientColors(gradient, colors, colorsLength);
    TextModelNG::SetGradientStyle(frameNode, gradient);
}

ArkUI_Int32 GetTextLinearGradient(
    ArkUINodeHandle node, ArkUI_Float32 (*values)[3], ArkUI_Uint32 (*colors)[10], ArkUI_Float32 (*stop)[10])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto gradient = TextModelNG::GetGradientStyle(frameNode);
    auto angle = gradient.GetLinearGradient()->angle;
    //0 angle
    (*values)[0] = angle.has_value() ? angle.value().Value() : DEFAULT_ANGLE;
    //1 Direction
    (*values)[1] = static_cast<int32_t>(ConvertToLinearGradientDirection(gradient.GetLinearGradient()));
    //2 Repeat
    (*values)[2] = gradient.GetRepeat();

    std::vector<GradientColor> gradientColors = gradient.GetColors();
    //0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        if (index >= NUM_10) {
            break;
        }
        (*colors)[index] = gradientColor.GetColor().GetValue();
        (*stop)[index] = gradientColor.GetDimension().Value();
        index++;
    }
    return index;
}

/**
 * @param values value value
 * values[0], values[1], values[2] : centerX Dimension: hasValue, value, unit
 * values[3], values[4], values[5] : centerY Dimension: hasValue, value, unit
 * values[6], values[7], values[8] : radius: Dimension: hasValue, value, unit
 * values[9] : repeating
 * @param valuesLength values length
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetTextRadialGradient(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
    const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesLength != NUM_10) || ((colorsLength % NUM_3) != 0)) {
        return;
    }
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    SetRadialGradientValues(gradient, values, valuesLength);
    SetGradientColors(gradient, colors, colorsLength);
    TextModelNG::SetGradientStyle(frameNode, gradient);
}

void ResetTextGradient(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ResetTextGradient(frameNode);
}

ArkUI_Int32 GetTextRadialGradient(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Uint32 (*colors)[10],
    ArkUI_Float32 (*stops)[10], ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto gradient = TextModelNG::GetGradientStyle(frameNode);
    auto radialGradient = gradient.GetRadialGradient();

    CHECK_NULL_RETURN(radialGradient, ERROR_INT_CODE);
    (*values)[NUM_0] = radialGradient->radialCenterX->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = radialGradient->radialCenterY->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = radialGradient->radialHorizontalSize->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = gradient.GetRepeat();

    std::vector<GradientColor> gradientColors = gradient.GetColors();
    //0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        if (index >= NUM_10) {
            break;
        }
        (*colors)[index] = gradientColor.GetColor().GetValue();
        (*stops)[index] = gradientColor.GetDimension().Value();
        index++;
    }
    return index;
}

void SetColorShaderColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetColorShaderStyle(frameNode, Color(color));
}

void SetTextVerticalAlign(ArkUINodeHandle node, ArkUI_Uint32 textVerticalAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextVerticalAlign(frameNode, static_cast<TextVerticalAlign>(textVerticalAlign));
}

void ResetTextVerticalAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextVerticalAlign(frameNode, TextVerticalAlign::BASELINE);
}

ArkUI_Uint32 GetTextVerticalAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<uint32_t>(TextVerticalAlign::BASELINE));
    return static_cast<ArkUI_Uint32>(TextModelNG::GetTextVerticalAlign(frameNode));
}

void SetTextContentTransition(ArkUINodeHandle node, ArkUI_Int32 flipDirection, ArkUI_Bool enableBlur)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetContentTransition(frameNode, TextEffectStrategy::FLIP,
        static_cast<TextFlipDirection>(flipDirection), static_cast<bool>(enableBlur));
}

void ResetTextContentTransition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ResetContentTransition(frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUITextModifier* GetTextModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITextModifier modifier = {
        .setContent = SetTextContent,
        .setFontWeight = SetFontWeight,
        .resetFontWeight = ResetFontWeight,
        .setFontStyle = SetFontStyle,
        .resetFontStyle = ResetFontStyle,
        .setTextAlign = SetTextAlign,
        .resetTextAlign = ResetTextAlign,
        .setTextContentAlign = SetTextContentAlign,
        .resetTextContentAlign = ResetTextContentAlign,
        .setFontColor = SetFontColor,
        .resetFontColor = ResetFontColor,
        .setTextForegroundColor = SetTextForegroundColor,
        .resetTextForegroundColor = ResetTextForegroundColor,
        .setFontSize = SetFontSize,
        .resetFontSize = ResetFontSize,
        .setTextLineHeight = SetTextLineHeight,
        .resetTextLineHeight = ResetTextLineHeight,
        .setTextOverflow = SetTextTextOverflow,
        .resetTextOverflow = ResetTextTextOverflow,
        .setTextDecoration = SetTextDecoration,
        .resetTextDecoration = ResetTextDecoration,
        .setTextCase = SetTextTextCase,
        .resetTextCase = ResetTextTextCase,
        .setTextMaxLines = SetTextMaxLines,
        .resetTextMaxLines = ResetTextMaxLines,
        .setTextMinFontSize = SetTextMinFontSize,
        .resetTextMinFontSize = ResetTextMinFontSize,
        .setTextDraggable = SetTextDraggable,
        .resetTextDraggable = ResetTextDraggable,
        .setTextPrivacySensitive = SetTextPrivacySensitve,
        .resetTextPrivacySensitive = ResetTextPrivacySensitve,
        .setTextMaxFontSize = SetTextMaxFontSize,
        .resetTextMaxFontSize = ResetTextMaxFontSize,
        .setTextFontFamily = SetTextFontFamily,
        .resetTextFontFamily = ResetTextFontFamily,
        .setTextCopyOption = SetTextCopyOption,
        .resetTextCopyOption = ResetTextCopyOption,
        .setTextShadow = SetTextTextShadow,
        .resetTextShadow = ResetTextTextShadow,
        .setTextHeightAdaptivePolicy = SetTextHeightAdaptivePolicy,
        .resetTextHeightAdaptivePolicy = ResetTextHeightAdaptivePolicy,
        .setTextIndent = SetTextTextIndent,
        .resetTextIndent = ResetTextTextIndent,
        .setTextBaselineOffset = SetTextBaselineOffset,
        .resetTextBaselineOffset = ResetTextBaselineOffset,
        .setTextLetterSpacing = SetTextLetterSpacing,
        .resetTextLetterSpacing = ResetTextLetterSpacing,
        .setTextFont = SetTextFont,
        .resetTextFont = ResetTextFont,
        .setFontWeightStr = SetFontWeightStr,
        .setFontWeightWithOption = SetFontWeightWithOption,
        .setWordBreak = SetWordBreak,
        .resetWordBreak = ResetWordBreak,
        .getFontFamily = GetFontFamily,
        .getCopyOption = GetCopyOption,
        .getHeightAdaptivePolicy = GetHeightAdaptivePolicy,
        .getTextMinFontSize = GetTextMinFontSize,
        .getTextMaxFontSize = GetTextMaxFontSize,
        .getFont = GetFont,
        .getFontSize = GetFontSize,
        .getFontWeight = GetFontWeight,
        .getItalicFontStyle = GetItalicFontStyle,
        .setEllipsisMode = SetEllipsisMode,
        .resetEllipsisMode = ResetEllipsisMode,
        .setEnableDataDetector = SetTextDetectEnable,
        .resetEnableDataDetector = ResetTextDetectEnable,
        .getTextContent = GetTextContent,
        .getTextLineHeight = GetTextLineHeight,
        .getTextDecoration = GetTextDecoration,
        .getTextTextCase = GetTextTextCase,
        .getTextLetterSpacing = GetTextLetterSpacing,
        .getTextMaxLines = GetTextMaxLines,
        .getTextAlign = GetTextAlign,
        .getTextContentAlign = GetTextContentAlign,
        .getTextTextOverflow = GetTextTextOverflow,
        .getTextTextIndent = GetTextTextIndent,
        .getFontColor = GetFontColor,
        .getTextBaselineOffset = GetTextBaselineOffset,
        .getTextShadowsCount = GetTextShadowCount,
        .getTextShadows = GetTextShadow,
        .getTextWordBreak = GetTextWordBreak,
        .getTextEllipsisMode = GetTextEllipsisMode,
        .setTextFontFeature = SetTextFontFeature,
        .resetTextFontFeature = ResetTextFontFeature,
        .getTextFontFeature = GetTextFontFeature,
        .getEnableDataDetector = GetTextDetectEnable,
        .setTextDataDetectorConfig = SetTextDataDetectorConfig,
        .getTextDataDetectorConfig = GetTextDataDetectorConfig,
        .resetTextDataDetectorConfig = ResetTextDataDetectorConfig,
        .setTextLineSpacing = SetTextLineSpacing,
        .getTextLineSpacing = GetTextLineSpacing,
        .resetTextLineSpacing = ResetTextLineSpacing,
        .setTextCaretColor = SetTextCaretColor,
        .getTextCaretColor = GetTextCaretColor,
        .resetTextCaretColor = ResetTextCaretColor,
        .setTextSelectedBackgroundColor = SetTextSelectedBackgroundColor,
        .getTextSelectedBackgroundColor = GetTextSelectedBackgroundColor,
        .resetTextSelectedBackgroundColor = ResetTextSelectedBackgroundColor,
        .setLineBreakStrategy = SetLineBreakStrategy,
        .resetLineBreakStrategy = ResetLineBreakStrategy,
        .getTextLineBreakStrategy = GetTextLineBreakStrategy,
        .setTextContentWithStyledString = SetTextContentWithStyledString,
        .resetTextContentWithStyledString = ResetTextContentWithStyledString,
        .setTextSelection = SetTextSelection,
        .resetTextSelection = ResetTextSelection,
        .setTextSelectableMode = SetTextSelectableMode,
        .resetTextSelectableMode = ResetTextSelectableMode,
        .setTextDataDetectorConfigWithEvent = SetTextDataDetectorConfigWithEvent,
        .resetTextDataDetectorConfigWithEvent = ResetTextDataDetectorConfigWithEvent,
        .setTextOnCopy = SetTextOnCopy,
        .resetTextOnCopy = ResetTextOnCopy,
        .setTextOnTextSelectionChange = SetTextOnTextSelectionChange,
        .resetTextOnTextSelectionChange = ResetTextOnTextSelectionChange,
        .setTextSelectionMenuOptions = SetTextSelectionMenuOptions,
        .resetTextSelectionMenuOptions = ResetTextSelectionMenuOptions,
        .setTextMinFontScale = SetTextMinFontScale,
        .resetTextMinFontScale = ResetTextMinFontScale,
        .setTextMaxFontScale = SetTextMaxFontScale,
        .resetTextMaxFontScale = ResetTextMaxFontScale,
        .setTextHalfLeading = SetTextHalfLeading,
        .resetTextHalfLeading = ResetTextHalfLeading,
        .getTextHalfLeading = GetTextHalfLeading,
        .setTextOnClick = SetOnClick,
        .resetTextOnClick = ResetOnClick,
        .setTextResponseRegion = SetResponseRegion,
        .resetTextResponseRegion = ResetResponseRegion,
        .setTextEnableHapticFeedback = SetTextEnableHapticFeedback,
        .resetTextEnableHapticFeedback = ResetTextEnableHapticFeedback,
        .setImmutableFontWeight = SetImmutableFontWeight,
        .setTextMarqueeOptions = SetMarqueeOptions,
        .resetTextMarqueeOptions = ResetMarqueeOptions,
        .setOnMarqueeStateChange = SetOnMarqueeStateChange,
        .resetOnMarqueeStateChange = ResetOnMarqueeStateChange,
        .getLineCount = GetLineCount,
        .setTextOptimizeTrailingSpace = SetTextOptimizeTrailingSpace,
        .resetTextOptimizeTrailingSpace = ResetTextOptimizeTrailingSpace,
        .getTextOptimizeTrailingSpace = GetTextOptimizeTrailingSpace,
        .setEnableAutoSpacing = SetEnableAutoSpacing,
        .resetEnableAutoSpacing = ResetEnableAutoSpacing,
        .setLinearGradient = SetTextLinearGradient,
        .getLinearGradient = GetTextLinearGradient,
        .setRadialGradient = SetTextRadialGradient,
        .getRadialGradient = GetTextRadialGradient,
        .resetTextGradient = ResetTextGradient,
        .setTextVerticalAlign = SetTextVerticalAlign,
        .resetTextVerticalAlign = ResetTextVerticalAlign,
        .getTextVerticalAlign = GetTextVerticalAlign,
        .setColorShaderColor = SetColorShaderColor,
        .setTextContentTransition = SetTextContentTransition,
        .resetTextContentTransition = ResetTextContentTransition,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITextModifier* GetCJUITextModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITextModifier modifier = {
        .setContent = SetTextContent,
        .setFontWeight = SetFontWeight,
        .resetFontWeight = ResetFontWeight,
        .setFontStyle = SetFontStyle,
        .resetFontStyle = ResetFontStyle,
        .setTextAlign = SetTextAlign,
        .resetTextAlign = ResetTextAlign,
        .setFontColor = SetFontColor,
        .resetFontColor = ResetFontColor,
        .setTextForegroundColor = SetTextForegroundColor,
        .resetTextForegroundColor = ResetTextForegroundColor,
        .setFontSize = SetFontSize,
        .resetFontSize = ResetFontSize,
        .setTextLineHeight = SetTextLineHeight,
        .resetTextLineHeight = ResetTextLineHeight,
        .setTextOverflow = SetTextTextOverflow,
        .resetTextOverflow = ResetTextTextOverflow,
        .setTextDecoration = SetTextDecoration,
        .resetTextDecoration = ResetTextDecoration,
        .setTextCase = SetTextTextCase,
        .resetTextCase = ResetTextTextCase,
        .setTextMaxLines = SetTextMaxLines,
        .resetTextMaxLines = ResetTextMaxLines,
        .setTextMinFontSize = SetTextMinFontSize,
        .resetTextMinFontSize = ResetTextMinFontSize,
        .setTextDraggable = SetTextDraggable,
        .resetTextDraggable = ResetTextDraggable,
        .setTextPrivacySensitive = SetTextPrivacySensitve,
        .resetTextPrivacySensitive = ResetTextPrivacySensitve,
        .setTextMaxFontSize = SetTextMaxFontSize,
        .resetTextMaxFontSize = ResetTextMaxFontSize,
        .setTextFontFamily = SetTextFontFamily,
        .resetTextFontFamily = ResetTextFontFamily,
        .setTextCopyOption = SetTextCopyOption,
        .resetTextCopyOption = ResetTextCopyOption,
        .setTextShadow = SetTextTextShadow,
        .resetTextShadow = ResetTextTextShadow,
        .setTextHeightAdaptivePolicy = SetTextHeightAdaptivePolicy,
        .resetTextHeightAdaptivePolicy = ResetTextHeightAdaptivePolicy,
        .setTextIndent = SetTextTextIndent,
        .resetTextIndent = ResetTextTextIndent,
        .setTextBaselineOffset = SetTextBaselineOffset,
        .resetTextBaselineOffset = ResetTextBaselineOffset,
        .setTextLetterSpacing = SetTextLetterSpacing,
        .resetTextLetterSpacing = ResetTextLetterSpacing,
        .setTextFont = SetTextFont,
        .resetTextFont = ResetTextFont,
        .setFontWeightStr = SetFontWeightStr,
        .setWordBreak = SetWordBreak,
        .resetWordBreak = ResetWordBreak,
        .getFontFamily = GetFontFamily,
        .getCopyOption = GetCopyOption,
        .getHeightAdaptivePolicy = GetHeightAdaptivePolicy,
        .getTextMinFontSize = GetTextMinFontSize,
        .getTextMaxFontSize = GetTextMaxFontSize,
        .getFont = GetFont,
        .getFontSize = GetFontSize,
        .getFontWeight = GetFontWeight,
        .getItalicFontStyle = GetItalicFontStyle,
        .setEllipsisMode = SetEllipsisMode,
        .resetEllipsisMode = ResetEllipsisMode,
        .setEnableDataDetector = SetTextDetectEnable,
        .resetEnableDataDetector = ResetTextDetectEnable,
        .getTextContent = GetTextContent,
        .getTextLineHeight = GetTextLineHeight,
        .getTextDecoration = GetTextDecoration,
        .getTextTextCase = GetTextTextCase,
        .getTextLetterSpacing = GetTextLetterSpacing,
        .getTextMaxLines = GetTextMaxLines,
        .getTextAlign = GetTextAlign,
        .getTextTextOverflow = GetTextTextOverflow,
        .getTextTextIndent = GetTextTextIndent,
        .getFontColor = GetFontColor,
        .getTextBaselineOffset = GetTextBaselineOffset,
        .getTextShadowsCount = GetTextShadowCount,
        .getTextShadows = GetTextShadow,
        .getTextWordBreak = GetTextWordBreak,
        .getTextEllipsisMode = GetTextEllipsisMode,
        .setTextFontFeature = SetTextFontFeature,
        .resetTextFontFeature = ResetTextFontFeature,
        .getTextFontFeature = GetTextFontFeature,
        .getEnableDataDetector = GetTextDetectEnable,
        .setTextDataDetectorConfig = SetTextDataDetectorConfig,
        .getTextDataDetectorConfig = GetTextDataDetectorConfig,
        .resetTextDataDetectorConfig = ResetTextDataDetectorConfig,
        .setTextLineSpacing = SetTextLineSpacing,
        .getTextLineSpacing = GetTextLineSpacing,
        .resetTextLineSpacing = ResetTextLineSpacing,
        .setTextSelectedBackgroundColor = SetTextSelectedBackgroundColor,
        .getTextSelectedBackgroundColor = GetTextSelectedBackgroundColor,
        .resetTextSelectedBackgroundColor = ResetTextSelectedBackgroundColor,
        .setLineBreakStrategy = SetLineBreakStrategy,
        .resetLineBreakStrategy = ResetLineBreakStrategy,
        .getTextLineBreakStrategy = GetTextLineBreakStrategy,
        .setTextContentWithStyledString = SetTextContentWithStyledString,
        .resetTextContentWithStyledString = ResetTextContentWithStyledString,
        .setTextSelection = SetTextSelection,
        .resetTextSelection = ResetTextSelection,
        .setTextSelectableMode = SetTextSelectableMode,
        .resetTextSelectableMode = ResetTextSelectableMode,
        .setTextDataDetectorConfigWithEvent = SetTextDataDetectorConfigWithEvent,
        .resetTextDataDetectorConfigWithEvent = ResetTextDataDetectorConfigWithEvent,
        .setTextOnCopy = SetTextOnCopy,
        .resetTextOnCopy = ResetTextOnCopy,
        .setTextOnTextSelectionChange = SetTextOnTextSelectionChange,
        .resetTextOnTextSelectionChange = ResetTextOnTextSelectionChange,
        .setFontWeightWithOption = SetFontWeightWithOption,
        .setTextMinFontScale = SetTextMinFontScale,
        .resetTextMinFontScale = ResetTextMinFontScale,
        .setTextMaxFontScale = SetTextMaxFontScale,
        .resetTextMaxFontScale = ResetTextMaxFontScale,
        .setTextSelectionMenuOptions = SetTextSelectionMenuOptionsForCJ,
        .resetTextSelectionMenuOptions = ResetTextSelectionMenuOptions,
        .setTextHalfLeading = SetTextHalfLeading,
        .resetTextHalfLeading = ResetTextHalfLeading,
        .getTextHalfLeading = GetTextHalfLeading,
        .setTextOnClick = SetOnClick,
        .resetTextOnClick = ResetOnClick,
        .setTextResponseRegion = SetResponseRegion,
        .resetTextResponseRegion = ResetResponseRegion,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

void SetOnDetectResultUpdate(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDetectResultUpdate = [node, extraParam](const std::string& str) {
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_DETECT_RESULT_UPDATE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(str.c_str());
        SendArkUISyncEvent(&event);
    };
    TextModelNG::SetOnDetectResultUpdate(frameNode, std::move(onDetectResultUpdate));
}

void ResetOnDetectResultUpdate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetOnDetectResultUpdate(frameNode, nullptr);
}

template<typename T>
void ProcessResourceObj(FrameNode* frameNode, std::string key, T value, void* objRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (objRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(objRawPtr));
        pattern->RegisterResource<T>(key, resObj, value);
    } else {
        pattern->UnRegisterResource(key);
    }
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
