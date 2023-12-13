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
#define private public
#define protected public
#include "core/components/test/json/text_style_creator.h"

#include "base/log/log.h"
#include "core/components/common/properties/color.h"
#include "core/components/test/json/color_creator.h"
#include "core/components/test/json/shadow_creator.h"
#include "core/pipeline/base/constants.h"
#include "core/components/declaration/text/text_declaration.h"
#include "frameworks/bridge/common/utils/utils.h"
#undef protected
#undef private
namespace OHOS::Ace {
namespace {

constexpr FontWeight FONT_WEIGHTS[] = { FontWeight::W100, FontWeight::W200, FontWeight::W300, FontWeight::W400,
    FontWeight::W500, FontWeight::W600, FontWeight::W700, FontWeight::W800, FontWeight::W900, FontWeight::BOLD,
    FontWeight::NORMAL, FontWeight::BOLDER, FontWeight::LIGHTER, FontWeight::MEDIUM, FontWeight::REGULAR };
constexpr FontStyle FONT_STYLES[] = { FontStyle::NORMAL, FontStyle::ITALIC };
constexpr TextBaseline BASE_LINES[] = { TextBaseline::ALPHABETIC, TextBaseline::IDEOGRAPHIC };
constexpr TextDecoration TEXT_DECORATIONS[] = { TextDecoration::NONE, TextDecoration::UNDERLINE,
    TextDecoration::OVERLINE, TextDecoration::LINE_THROUGH, TextDecoration::INHERIT };
constexpr TextDecorationStyle TEXT_DECORATION_STYLES[] = { TextDecorationStyle::SOLID, TextDecorationStyle::DOUBLE,
    TextDecorationStyle::DOTTED, TextDecorationStyle::DASHED, TextDecorationStyle::WAVY };
const char TEXT_SHADOW[] = "textShadow";
const char TEXT_ADAPT_HEIGHT[] = "adaptHeight";
const char TEXT_ALLOW_SCALE[] = "allowScale";
const char TEXT_ADAPT_MAX_FONT_SIZE[] = "adaptMaxFontSize";
const char TEXT_ADAPT_MIN_FONT_SIZE[] = "adaptMinFontSize";
const char TEXT_PREFER_FONT_SIZE[] = "preferFontSizes";
const char TEXT_DECORATION_COLOR[] = "textDecorationColor";
const char TEXT_INDENT[] = "textIndent";
const char TEXT_VALIGN[] = "textValign";
const char TEXT_WHITESPACE[] = "whiteSpace";
const char TEXT_WORDBREAK[] = "wordBreak";
const char TEXT_ADAPT_FONT_SIZE_STEP[] = "fontSizeStep";
const char TEXT_CASE[] = "textCase";
const std::vector<Dimension> PREFER_FONT_SIZES { Dimension(5.0), Dimension(10.0), Dimension(20.0) };
const std::unordered_map<std::string, int32_t> FONT_FEATURES {
    {"liga ", 0},
    {"clig ", 0},
    {"dlig ", 0},
    {"hlig ", 0},
    {"dlig ", 0}
};

const std::unordered_map<std::string, DimensionUnit> dimensionUnitMap {
    {"px", DimensionUnit::PX},
    {"vp", DimensionUnit::VP},
    {"fp", DimensionUnit::FP},
    {"%", DimensionUnit::PERCENT},
    {"lpx", DimensionUnit::LPX},
};

const std::unordered_map<int, TextCase> textCaseMap {
    {0, TextCase::NORMAL},
    {1, TextCase::LOWERCASE},
    {2, TextCase::UPPERCASE}
};

} // namespace

TextStyle TextStyleCreator::CreateFromJson(const JsonValue& json)
{
    LOGD("CreateFromJson TextStyle");
    TextStyle textStyle;
    std::string classType = json.GetValue(CLASS_NAME)->GetString();
    if (classType != TEXT_STYLE_NAME) {
        LOGW("Create TextStyle err: not a TextStyle json.");
        // Currently return a default text style has no side effect.
        return textStyle;
    }
    if (json.Contains(TEXT_FONT_SIZE) && json.GetValue(TEXT_FONT_SIZE)->IsNumber()) {
        textStyle.SetFontSize(Dimension(json.GetValue(TEXT_FONT_SIZE)->GetDouble(), DimensionUnit::PX));
    }
    if (json.Contains(TEXT_FONT_WEIGHT) && json.GetValue(TEXT_FONT_WEIGHT)->IsNumber()) {
        textStyle.SetFontWeight(
            ConvertIntToEnum(json.GetValue(TEXT_FONT_WEIGHT)->GetInt(), FONT_WEIGHTS, FontWeight::NORMAL));
    }
    if (json.Contains(TEXT_FONT_STYLE) && json.GetValue(TEXT_FONT_STYLE)->IsNumber()) {
        textStyle.SetFontStyle(
            ConvertIntToEnum(json.GetValue(TEXT_FONT_STYLE)->GetInt(), FONT_STYLES, FontStyle::NORMAL));
    }
    if (json.Contains(TEXT_BASE_LINE) && json.GetValue(TEXT_BASE_LINE)->IsNumber()) {
        textStyle.SetTextBaseline(
            ConvertIntToEnum(json.GetValue(TEXT_BASE_LINE)->GetInt(), BASE_LINES, TextBaseline::ALPHABETIC));
    }
    if (json.Contains(TEXT_COLOR) && json.GetValue(TEXT_COLOR)->IsObject()) {
        auto colorJson = json.GetValue(TEXT_COLOR);
        auto color = ColorCreator::CreateFromJson(*colorJson);
        textStyle.SetTextColor(color);
    } else if (json.Contains(TEXT_COLOR) && json.GetValue(TEXT_COLOR)->IsString()) {
        auto color = ColorCreator::CreateFromString(json.GetValue(TEXT_COLOR)->GetString());
        textStyle.SetTextColor(color);
    }
    if (json.Contains(TEXT_DECORATION) && json.GetValue(TEXT_DECORATION)->IsNumber()) {
        textStyle.SetTextDecoration(
            ConvertIntToEnum(json.GetValue(TEXT_DECORATION)->GetInt(), TEXT_DECORATIONS, TextDecoration::NONE));
    }
    if (json.Contains(TEXT_DECORATION_STYLE) && json.GetValue(TEXT_DECORATION_STYLE)->IsNumber()) {
        textStyle.SetTextDecorationStyle(ConvertIntToEnum(
            json.GetValue(TEXT_DECORATION_STYLE)->GetInt(), TEXT_DECORATION_STYLES, TextDecorationStyle::SOLID));
    }
    if (json.Contains(TEXT_DECORATION_COLOR) && json.GetValue(TEXT_DECORATION_COLOR)->IsString()) {
        TextDeclaration colorDecoration;
        textStyle.SetTextDecorationColor(colorDecoration.ParseColor(json.GetValue(TEXT_DECORATION_COLOR)->GetString()));
    }
    if (json.Contains(SHADOW) && json.GetValue(SHADOW)->IsObject()) {
        auto shadow = ShadowCreator::CreateFromJson(*(json.GetValue(SHADOW)));
        textStyle.SetShadow(shadow);
    }
    if (json.Contains(TEXT_WORD_SPACING) && json.GetValue(TEXT_WORD_SPACING)->IsNumber()) {
        textStyle.SetWordSpacing(Dimension(json.GetValue(TEXT_WORD_SPACING)->GetDouble()));
    }
    auto arrayJsonObject = json.GetValue(TEXT_FONT_FAMILIES);
    if (arrayJsonObject && arrayJsonObject->IsArray()) {
        std::vector<std::string> fontFamilies_;
        for (int32_t i = 0; i < arrayJsonObject->GetArraySize(); i++) {
            fontFamilies_.emplace_back(arrayJsonObject->GetArrayItem(i)->GetString());
        }
        textStyle.SetFontFamilies(fontFamilies_);
    }
    if (json.Contains(TEXT_LINE_HEIGHT) && json.GetValue(TEXT_LINE_HEIGHT)->IsNumber()) {
        textStyle.SetLineHeight(Dimension(json.GetValue(TEXT_LINE_HEIGHT)->GetDouble(), DimensionUnit::PX));
    } else if (json.Contains(TEXT_LINE_HEIGHT) && json.GetValue(TEXT_LINE_HEIGHT)->IsString()) {
        TextDeclaration declaration;
        textStyle.SetLineHeight(declaration.ParseLineHeight(json.GetValue(TEXT_LINE_HEIGHT)->GetString()));
    }
    if (json.Contains(TEXT_LETTER_SPACING) && json.GetValue(TEXT_LETTER_SPACING)->IsNumber()) {
        textStyle.SetLetterSpacing(Dimension(json.GetValue(TEXT_LETTER_SPACING)->GetDouble()));
    } else if (json.Contains(TEXT_LETTER_SPACING) && json.GetValue(TEXT_LETTER_SPACING)->IsString()) {
        std::string letterSpacing = json.GetValue(TEXT_LETTER_SPACING)->GetString();
        char *pUnit = NULL;
        auto val =  std::strtof(letterSpacing.c_str(), &pUnit);
        const std::string unit = pUnit;
        auto iter = dimensionUnitMap.find(unit);
        if (iter != dimensionUnitMap.end()) {
            textStyle.SetLetterSpacing(Dimension(val, iter->second));
        }
    }
    if (json.Contains(TEXT_ADAPT) && json.GetValue(TEXT_ADAPT)->IsBool()) {
        if (json.Contains(TEXT_ADAPT_MIN_FONTSIZE) && json.GetValue(TEXT_ADAPT_MIN_FONTSIZE)->IsNumber()) {
            textStyle.SetAdaptTextSize(textStyle.GetFontSize(),
                Dimension(json.GetValue(TEXT_ADAPT_MIN_FONTSIZE)->GetDouble(), DimensionUnit::FP));
        }
    }

    if (json.Contains(TEXT_ADAPT_HEIGHT) && json.GetValue(TEXT_ADAPT_HEIGHT)->IsBool()) {
        textStyle.SetAdaptHeight(json.GetBool(TEXT_ADAPT_HEIGHT, false));
    }

    if (json.Contains(TEXT_ALLOW_SCALE) && json.GetValue(TEXT_ALLOW_SCALE)->IsBool()) {
        textStyle.SetAllowScale(json.GetBool(TEXT_ALLOW_SCALE, false));
    }

    if (json.Contains(TEXT_FIELD_MAX_LINES) && json.GetValue(TEXT_FIELD_MAX_LINES)->IsNumber()) {
        textStyle.SetMaxLines(json.GetValue(TEXT_FIELD_MAX_LINES)->GetUInt());
    }
    if (json.Contains(TEXT_ADAPT_MAX_FONT_SIZE) && json.GetValue(TEXT_ADAPT_MAX_FONT_SIZE)->IsString()) {
        TextDeclaration declaration;
        auto maxFontSize = declaration.ParseDimension(json.GetValue(TEXT_ADAPT_MAX_FONT_SIZE)->GetString());
        textStyle.SetAdaptMaxFontSize(maxFontSize);
    }
    if (json.Contains(TEXT_ADAPT_MIN_FONT_SIZE) && json.GetValue(TEXT_ADAPT_MIN_FONT_SIZE)->IsString()) {
        TextDeclaration declaration;
        auto minFontSize = declaration.ParseDimension(json.GetValue(TEXT_ADAPT_MIN_FONT_SIZE)->GetString());
        textStyle.SetAdaptMinFontSize(minFontSize);
    }
    if (json.Contains(TEXT_PREFER_FONT_SIZE) && json.GetValue(TEXT_PREFER_FONT_SIZE)->IsString()) {
        TextDeclaration declaration;
        auto preferFontSizes = declaration.ParsePreferFontSizes(json.GetValue(TEXT_PREFER_FONT_SIZE)->GetString());
        textStyle.SetPreferFontSizes(preferFontSizes);
    }
    if (json.Contains(TEXT_ALIGN) && json.GetValue(TEXT_ALIGN)->IsString()) {
        auto textAlign = Framework::ConvertStrToTextAlign(json.GetValue(TEXT_ALIGN)->GetString());
        textStyle.SetTextAlign(textAlign);
    }
    if (json.Contains(TEXT_INDENT) && json.GetValue(TEXT_INDENT)->IsString()) {
        TextDeclaration textIndentDeclaration;
        auto textIndent = json.GetValue(TEXT_INDENT)->GetString();
        textStyle.SetTextIndent(textIndentDeclaration.ParseDimension(textIndent));
    }
    if (json.Contains(TEXT_OVERFLOW) && json.GetValue(TEXT_OVERFLOW)->IsString()) {
        auto textOverflow = json.GetValue(TEXT_OVERFLOW)->GetString();
        textStyle.SetTextOverflow(Framework::ConvertStrToTextOverflow(textOverflow));
    }
    if (json.Contains(TEXT_VALIGN) && json.GetValue(TEXT_VALIGN)->IsString()) {
        auto textAlign = json.GetValue(TEXT_VALIGN)->GetString();
        textStyle.SetTextVerticalAlign(Framework::ConvertStrToTextVerticalAlign(textAlign));
    }
    if (json.Contains(TEXT_WHITESPACE) && json.GetValue(TEXT_WHITESPACE)->IsString()) {
        auto whiteSpace = json.GetValue(TEXT_WHITESPACE)->GetString();
        textStyle.SetWhiteSpace(Framework::ConvertStrToWhiteSpace(whiteSpace));
    }

    if (json.Contains(TEXT_WORDBREAK) && json.GetValue(TEXT_WORDBREAK)->IsString()) {
        textStyle.SetWordBreak(Framework::ConvertStrToWordBreak(json.GetValue(TEXT_WORDBREAK)->GetString()));
    }
    if (json.Contains(TEXT_WORD_SPACING) && json.GetValue(TEXT_WORD_SPACING)->IsString()) {
        TextDeclaration wordspacing;
        textStyle.SetWordSpacing(wordspacing.ParseDimension(json.GetValue(TEXT_WORD_SPACING)->GetString()));
    }
    if (json.Contains(TEXT_ADAPT_FONT_SIZE_STEP) && json.GetValue(TEXT_ADAPT_FONT_SIZE_STEP)->IsString()) {
        TextDeclaration wordspacing;
        auto fontSizeStep = json.GetValue(TEXT_ADAPT_FONT_SIZE_STEP)->GetString();
        textStyle.SetAdaptFontSizeStep(wordspacing.ParseDimension(fontSizeStep));
    }
    if (json.Contains(TEXT_CASE) && json.GetValue(TEXT_CASE)->IsNumber()) {
        auto index = json.GetValue(TEXT_CASE)->GetUInt();
        auto it = textCaseMap.find(index);
        if (it != textCaseMap.end()) {
            textStyle.SetTextCase(it->second);
        } else {
            textStyle.SetTextCase(TextCase::NORMAL);
        }
    }

    if (json.Contains(TEXT_SHADOW) && json.GetValue(TEXT_SHADOW)->IsString()) {
        TextDeclaration declaration;
        auto textShadow = json.GetValue(TEXT_SHADOW)->GetString();
        textStyle.SetTextShadows(TextDeclaration::ParseTextShadow(textShadow, declaration));
    }
    return textStyle;
}

} // namespace OHOS::Ace
