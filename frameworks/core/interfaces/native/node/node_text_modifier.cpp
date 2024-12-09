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

#include "base/utils/utils.h"
#include "base/utils/utf_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "frameworks/core/components_ng/pattern/text/text_model_ng.h"
#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG {
constexpr int DEFAULT_SELECTION = -1;
constexpr Dimension DEFAULT_LINE_HEIGHT = Dimension(0.0, DimensionUnit::PX);
constexpr Dimension DEFAULT_LINE_SPACING = Dimension(0.0, DimensionUnit::PX);
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
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<EllipsisMode> ELLIPSIS_MODALS = { EllipsisMode::HEAD, EllipsisMode::MIDDLE, EllipsisMode::TAIL };
const std::vector<TextSelectableMode> TEXT_SELECTABLE_MODE = { TextSelectableMode::SELECTABLE_UNFOCUSABLE,
    TextSelectableMode::SELECTABLE_FOCUSABLE, TextSelectableMode::UNSELECTABLE };
constexpr bool DEFAULT_ENABLE_TEXT_DETECTOR = false;
const std::vector<std::string> TEXT_DETECT_TYPES = { "phoneNum", "url", "email", "location", "datetime" };
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;

std::map<TextHeightAdaptivePolicy, int> TEXT_HEIGHT_ADAPTIVE_POLICY_MAP = {
    { TextHeightAdaptivePolicy::MAX_LINES_FIRST, 0 },
    { TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, 1 },
    { TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST, 2 } };

const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;

FontWeight ConvertStrToFontWeight(const char* weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}
namespace {

std::string g_strValue;
void SetTextContent(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::u16string content = UtfUtils::Str8ToStr16(std::string(value));
    TextModelNG::InitText(frameNode, content);
}

const char* GetTextContent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = UtfUtils::Str16ToStr8(TextModelNG::GetContent(frameNode));
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
}

void SetOnClick(ArkUINodeHandle node, void* callback)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
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
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
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
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
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

void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextColor(frameNode, Color(color));
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color textColor;
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    textColor = theme->GetTextStyle().GetTextColor();
    TextModelNG::SetTextColor(frameNode, textColor);
}

uint32_t GetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, Color::BLACK.GetValue());
    return TextModelNG::GetFontColor(frameNode).GetValue();
}

void SetTextForegroundColor(ArkUINodeHandle node, ArkUI_Bool isColor, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (isColor) {
        TextModelNG::SetTextColor(frameNode, Color(color));
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

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, ArkUI_Int32 unit)
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
        TextModelNG::SetFontSize(frameNode, Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit)));
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
}

void SetTextLineHeight(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineHeight(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
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

void SetTextDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    TextModelNG::SetTextDecorationColor(frameNode, Color(color));
    TextModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
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

void SetTextMinFontSize(ArkUINodeHandle node, ArkUI_Float32 number, const ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMinFontSize(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMinFontSize(frameNode, DEFAULT_MIN_FONT_SIZE);
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

void SetTextMaxFontSize(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMaxFontSize(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMaxFontSize(frameNode, DEFAULT_MAX_FONT_SIZE);
}

void SetTextMinFontScale(ArkUINodeHandle node, ArkUI_Float32 number)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMinFontScale(frameNode, number);
}

void ResetTextMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMinFontScale(frameNode, DEFAULT_MIN_FONT_SCALE);
}

void SetTextMaxFontScale(ArkUINodeHandle node, ArkUI_Float32 number)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxFontScale(frameNode, number);
}

void ResetTextMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxFontScale(frameNode, DEFAULT_MAX_FONT_SCALE);
}

void SetTextFontFamily(ArkUINodeHandle node, const char** fontFamilies, ArkUI_Uint32 length)
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
}

void ResetTextFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FAMILY);
    TextModelNG::SetFontFamily(frameNode, families);
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

void SetTextTextShadow(ArkUINodeHandle node, struct ArkUITextShadowStruct* shadows, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(shadows);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        ArkUITextShadowStruct* shadowStruct = shadows + i;
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
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
            *(shadow + i) = { 0.0f, static_cast<int32_t>(ShadowType::COLOR),
                Color::TRANSPARENT.GetValue(), 0.0f, 0.0f, 0 };
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
    TextModelNG::SetHeightAdaptivePolicy(frameNode, HEIGHT_ADAPTIVE_POLICY[value]);
}

void ResetTextHeightAdaptivePolicy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHeightAdaptivePolicy(frameNode, TextHeightAdaptivePolicy::MAX_LINES_FIRST);
}

void SetTextTextIndent(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextIndent(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
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
}

void SetTextBaselineOffset(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetBaselineOffset(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextBaselineOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetBaselineOffset(frameNode, DEFAULT_BASELINE_OFFSET);
}

ArkUI_Float32 GetTextBaselineOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return TextModelNG::GetTextBaselineOffset(frameNode).ConvertToVp();
}

void SetTextLetterSpacing(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLetterSpacing(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
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
}

void SetTextFont(ArkUINodeHandle node, const struct ArkUIFontWithOptionsStruct* fontInfo)
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
        families.resize(fontInfo->familyLength);
        for (uint32_t i = 0; i < fontInfo->familyLength; i++) {
            families.at(i) = std::string(*(fontInfo->fontFamilies + i));
        }
    }
    font.fontFamilies = families;
    TextModelNG::SetFont(frameNode, font);
    TextModelNG::SetVariableFontWeight(frameNode, fontInfo->variableFontWeight);
    TextModelNG::SetEnableVariableFontWeight(frameNode, fontInfo->enableVariableFontWeight);
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

void SetTextLineSpacing(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineSpacing(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
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
    TextModelNG::SetLineSpacing(frameNode, DEFAULT_LINE_SPACING);
}

void SetTextCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetCaretColor(frameNode, Color(color));
}

ArkUI_Uint32 GetTextCaretColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, Color::BLACK.GetValue());
    return TextModelNG::GetCaretColor(frameNode).GetValue();
}

void ResetTextCaretColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto caretColor = static_cast<int32_t>(theme->GetCaretColor().GetValue());
    TextModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void SetTextSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
}

ArkUI_Uint32 GetTextSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, Color::BLACK.GetValue());
    return TextModelNG::GetSelectedBackgroundColor(frameNode).GetValue();
}

void ResetTextSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::ResetSelectedBackgroundColor(frameNode);
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
    ArkUINodeHandle node, const struct ArkUITextDetectConfigStruct* arkUITextDetectConfig)
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
    TextModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void ResetTextDataDetectorConfigWithEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    TextModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void SetTextOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        TextModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        TextModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetTextOnCopy(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
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
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetOnTextSelectionChange(frameNode, nullptr);
}

void SetTextSelectionMenuOptions(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback)
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
}

void ResetTextSelectionMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    TextModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenuCallback));
    TextModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
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
} // namespace

namespace NodeModifier {
const ArkUITextModifier* GetTextModifier()
{
    static const ArkUITextModifier modifier = { SetTextContent, SetFontWeight, ResetFontWeight, SetFontStyle,
        ResetFontStyle, SetTextAlign, ResetTextAlign, SetFontColor, ResetFontColor, SetTextForegroundColor,
        ResetTextForegroundColor, SetFontSize, ResetFontSize, SetTextLineHeight, ResetTextLineHeight,
        SetTextTextOverflow, ResetTextTextOverflow, SetTextDecoration, ResetTextDecoration, SetTextTextCase,
        ResetTextTextCase, SetTextMaxLines, ResetTextMaxLines, SetTextMinFontSize, ResetTextMinFontSize,
        SetTextDraggable, ResetTextDraggable, SetTextPrivacySensitve, ResetTextPrivacySensitve, SetTextMaxFontSize,
        ResetTextMaxFontSize, SetTextFontFamily, ResetTextFontFamily, SetTextCopyOption, ResetTextCopyOption,
        SetTextTextShadow, ResetTextTextShadow, SetTextHeightAdaptivePolicy, ResetTextHeightAdaptivePolicy,
        SetTextTextIndent, ResetTextTextIndent, SetTextBaselineOffset, ResetTextBaselineOffset, SetTextLetterSpacing,
        ResetTextLetterSpacing, SetTextFont, ResetTextFont, SetFontWeightStr, SetFontWeightWithOption, SetWordBreak,
        ResetWordBreak, GetFontFamily, GetCopyOption, GetHeightAdaptivePolicy, GetTextMinFontSize, GetTextMaxFontSize,
        GetFont, GetFontSize, GetFontWeight, GetItalicFontStyle, SetEllipsisMode, ResetEllipsisMode,
        SetTextDetectEnable, ResetTextDetectEnable, GetTextContent, GetTextLineHeight, GetTextDecoration,
        GetTextTextCase, GetTextLetterSpacing, GetTextMaxLines, GetTextAlign, GetTextTextOverflow, GetTextTextIndent,
        GetFontColor, GetTextBaselineOffset, GetTextShadowCount, GetTextShadow, GetTextWordBreak, GetTextEllipsisMode,
        SetTextFontFeature, ResetTextFontFeature, SetTextLineSpacing, GetTextLineSpacing, ResetTextLineSpacing,
        GetTextFontFeature, GetTextDetectEnable, SetTextDataDetectorConfig, GetTextDataDetectorConfig,
        ResetTextDataDetectorConfig, SetLineBreakStrategy, ResetLineBreakStrategy, GetTextLineBreakStrategy,
        SetTextCaretColor, GetTextCaretColor, ResetTextCaretColor,
        SetTextSelectedBackgroundColor, GetTextSelectedBackgroundColor, ResetTextSelectedBackgroundColor,
        SetTextContentWithStyledString, ResetTextContentWithStyledString, SetTextSelection, ResetTextSelection,
        SetTextSelectableMode, ResetTextSelectableMode, SetTextDataDetectorConfigWithEvent,
        ResetTextDataDetectorConfigWithEvent, SetTextOnCopy, ResetTextOnCopy, SetTextOnTextSelectionChange,
        ResetTextOnTextSelectionChange, SetTextMinFontScale, ResetTextMinFontScale, SetTextMaxFontScale,
        ResetTextMaxFontScale, SetTextSelectionMenuOptions, ResetTextSelectionMenuOptions, SetTextHalfLeading,
        ResetTextHalfLeading, GetTextHalfLeading, SetOnClick, ResetOnClick, SetResponseRegion, ResetResponseRegion };

    return &modifier;
}

const CJUITextModifier* GetCJUITextModifier()
{
    static const CJUITextModifier modifier = { SetTextContent, SetFontWeight, ResetFontWeight, SetFontStyle,
        ResetFontStyle, SetTextAlign, ResetTextAlign, SetFontColor, ResetFontColor, SetTextForegroundColor,
        ResetTextForegroundColor, SetFontSize, ResetFontSize, SetTextLineHeight, ResetTextLineHeight,
        SetTextTextOverflow, ResetTextTextOverflow, SetTextDecoration, ResetTextDecoration, SetTextTextCase,
        ResetTextTextCase, SetTextMaxLines, ResetTextMaxLines, SetTextMinFontSize, ResetTextMinFontSize,
        SetTextDraggable, ResetTextDraggable, SetTextPrivacySensitve, ResetTextPrivacySensitve, SetTextMaxFontSize,
        ResetTextMaxFontSize, SetTextFontFamily, ResetTextFontFamily, SetTextCopyOption, ResetTextCopyOption,
        SetTextTextShadow, ResetTextTextShadow, SetTextHeightAdaptivePolicy, ResetTextHeightAdaptivePolicy,
        SetTextTextIndent, ResetTextTextIndent, SetTextBaselineOffset, ResetTextBaselineOffset, SetTextLetterSpacing,
        ResetTextLetterSpacing, SetTextFont, ResetTextFont, SetFontWeightStr, SetWordBreak, ResetWordBreak,
        GetFontFamily, GetCopyOption, GetHeightAdaptivePolicy, GetTextMinFontSize, GetTextMaxFontSize, GetFont,
        GetFontSize, GetFontWeight, GetItalicFontStyle, SetEllipsisMode, ResetEllipsisMode, SetTextDetectEnable,
        ResetTextDetectEnable, GetTextContent, GetTextLineHeight, GetTextDecoration, GetTextTextCase,
        GetTextLetterSpacing, GetTextMaxLines, GetTextAlign, GetTextTextOverflow, GetTextTextIndent, GetFontColor,
        GetTextBaselineOffset, GetTextShadowCount, GetTextShadow, GetTextWordBreak, GetTextEllipsisMode,
        SetTextFontFeature, ResetTextFontFeature, GetTextFontFeature, GetTextDetectEnable, SetTextDataDetectorConfig,
        GetTextDataDetectorConfig, ResetTextDataDetectorConfig, SetTextLineSpacing, GetTextLineSpacing,
        ResetTextLineSpacing, SetTextSelectedBackgroundColor, GetTextSelectedBackgroundColor,
        ResetTextSelectedBackgroundColor, SetLineBreakStrategy, ResetLineBreakStrategy, GetTextLineBreakStrategy,
        SetTextContentWithStyledString, ResetTextContentWithStyledString, SetTextSelection, ResetTextSelection,
        SetTextSelectableMode, ResetTextSelectableMode, SetTextDataDetectorConfigWithEvent,
        ResetTextDataDetectorConfigWithEvent, SetTextOnCopy, ResetTextOnCopy, SetTextOnTextSelectionChange,
        ResetTextOnTextSelectionChange, SetFontWeightWithOption, SetTextMinFontScale, ResetTextMinFontScale,
        SetTextMaxFontScale, ResetTextMaxFontScale, SetTextSelectionMenuOptions, ResetTextSelectionMenuOptions,
        SetTextHalfLeading, ResetTextHalfLeading, GetTextHalfLeading, SetOnClick, ResetOnClick, SetResponseRegion,
        ResetResponseRegion };

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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
