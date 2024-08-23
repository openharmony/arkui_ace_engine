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

#include <regex>

#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t FONT_FEATURE_MAX_SIZE = 2;
constexpr int32_t FONT_FEATURE_KEY_LENGTH = 6;
constexpr int32_t FONT_FEATURE_PARENTHESES_LENGTH = 2; // length of ()
const char FONT_FEATURE_NONE[] = "none";
const char FONT_FEATURE_NORMAL[] = "normal";
const char FONT_FEATURE_ON[] = "on";

} // namespace
using FONT_FEATURES_LIST = std::list<std::pair<std::string, int32_t>>;

bool ParseFontVariantCaps(const std::string& fontVariant, FONT_FEATURES_LIST& fontFeatures)
{
    if (fontVariant == FONT_FEATURE_NORMAL || fontVariant.empty()) {
        return true;
    }

    const std::unordered_map<std::string, void (*)(FONT_FEATURES_LIST&)> operators = {
        { "small-caps",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("smcp", 1)); } },
        { "all-small-caps",
            [](FONT_FEATURES_LIST& fontFeatures) {
                fontFeatures.emplace_back(std::make_pair("c2sc", 1));
                fontFeatures.emplace_back(std::make_pair("smcp", 1));
            } },
        { "petite-caps",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("pcap", 1)); } },
        { "all-petite-caps",
            [](FONT_FEATURES_LIST& fontFeatures) {
                fontFeatures.emplace_back(std::make_pair("c2pc", 1));
                fontFeatures.emplace_back(std::make_pair("pcap", 1));
            } },
        { "unicase",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("unic", 1)); } },
        { "titling-caps",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("titl", 1)); } },
    };
    auto iter = operators.find(fontVariant);
    if (iter != operators.end()) {
        iter->second(fontFeatures);
        return true;
    }
    return false;
}

bool ParseFontVariantNumeric(const std::string& fontVariant, FONT_FEATURES_LIST& fontFeatures)
{
    if (fontVariant == FONT_FEATURE_NORMAL || fontVariant.empty()) {
        return true;
    }

    const std::unordered_map<std::string, void (*)(FONT_FEATURES_LIST&)> operators = {
        { "ordinal",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("ordn", 1)); } },
        { "slashed-zero",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("zero", 1)); } },
        { "lining-nums",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("lnum", 1)); } },
        { "oldstyle-nums",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("onum", 1)); } },
        { "proportional-nums",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("pnum", 1)); } },
        { "tabular-nums",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("tnum", 1)); } },
        { "diagonal-fractions",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("frac", 1)); } },
        { "stacked-fractions",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("afrc", 1)); } },
    };
    auto iter = operators.find(fontVariant);
    if (iter != operators.end()) {
        iter->second(fontFeatures);
        return true;
    }
    return false;
}

int32_t ParseFontFeatureParameters(std::string& value)
{
    if ((value == FONT_FEATURE_ON) || (StringUtils::StringToInt(value) == 1)) {
        return 1;
    }
    return 0;
}

bool ParseFontVariantAlternates(const std::string& fontVariant, FONT_FEATURES_LIST& fontFeatures)
{
    // format of font-variant-alternates is key(value) | normal | historical-forms.
    if (fontVariant == FONT_FEATURE_NORMAL || fontVariant.empty()) {
        return true;
    }
    if (fontVariant != "historical-forms" && !regex_match(fontVariant, std::regex(".+(.+)"))) {
        return false;
    }

    std::string key = fontVariant;
    int32_t value = 1;
    auto valueIndex = fontVariant.find_first_of("(");
    if (valueIndex != std::string::npos && fontVariant.size() > valueIndex) {
        key = fontVariant.substr(0, valueIndex);
        value = StringUtils::StringToInt(
            fontVariant.substr(valueIndex + 1, fontVariant.size() - key.size() - FONT_FEATURE_PARENTHESES_LENGTH));
    }
    const std::unordered_map<std::string,
        void (*)(const std::string&, int32_t, FONT_FEATURES_LIST&)>
        operators = {
            { "historical-forms",
                [](const std::string& key, int32_t value, FONT_FEATURES_LIST& fontFeatures) {
                    fontFeatures.emplace_back(std::make_pair("hist", 1));
                } },
            { "stylistic",
                [](const std::string& key, int32_t value, FONT_FEATURES_LIST& fontFeatures) {
                    fontFeatures.emplace_back(std::make_pair("salt", value));
                } },
            { "styleset",
                [](const std::string& key, int32_t value, FONT_FEATURES_LIST& fontFeatures) {
                    // Convert value to ssxx, like 1 to ss01.
                    std::string temp = "0" + std::to_string(value);
                    fontFeatures.emplace_back(std::make_pair("ss" + temp.substr(temp.size() - 2, 2), 1));
                } },
            { "character-variant",
                [](const std::string& key, int32_t value, FONT_FEATURES_LIST& fontFeatures) {
                    // Convert value to cvxx, like 1 to cv01.
                    std::string temp = "0" + std::to_string(value);
                    fontFeatures.emplace_back(std::make_pair("cv" + temp.substr(temp.size() - 2, 2), 1));
                } },
            { "swash",
                [](const std::string& key, int32_t value, FONT_FEATURES_LIST& fontFeatures) {
                    fontFeatures.emplace_back(std::make_pair("swsh", value));
                    fontFeatures.emplace_back(std::make_pair("cswh", value));
                } },
            { "ornaments",
                [](const std::string& key, int32_t value, FONT_FEATURES_LIST& fontFeatures) {
                    fontFeatures.emplace_back(std::make_pair("ornm", value));
                } },
            { "annotation",
                [](const std::string& key, int32_t value, FONT_FEATURES_LIST& fontFeatures) {
                    fontFeatures.emplace_back(std::make_pair("nalt", value));
                } },
        };
    auto iter = operators.find(key);
    if (iter != operators.end()) {
        iter->second(key, value, fontFeatures);
        return true;
    }
    return false;
}

bool ParseFontVariantLigatures(const std::string& fontVariant, FONT_FEATURES_LIST& fontFeatures)
{
    if (fontVariant == FONT_FEATURE_NORMAL || fontVariant.empty()) {
        return true;
    }

    const std::unordered_map<std::string, void (*)(FONT_FEATURES_LIST&)> operators = {
        { "none",
            [](FONT_FEATURES_LIST& fontFeatures) {
                fontFeatures.emplace_back(std::make_pair("liga ", 0));
                fontFeatures.emplace_back(std::make_pair("clig ", 0));
                fontFeatures.emplace_back(std::make_pair("dlig ", 0));
                fontFeatures.emplace_back(std::make_pair("hlig ", 0));
                fontFeatures.emplace_back(std::make_pair("calt ", 0));
            } },
        { "common-ligatures",
            [](FONT_FEATURES_LIST& fontFeatures) {
                fontFeatures.emplace_back(std::make_pair("liga ", 1));
                fontFeatures.emplace_back(std::make_pair("clig ", 1));
            } },
        { "no-common-ligatures",
            [](FONT_FEATURES_LIST& fontFeatures) {
                fontFeatures.emplace_back(std::make_pair("liga", 0));
                fontFeatures.emplace_back(std::make_pair("clig", 0));
            } },
        { "discretionary-ligatures",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("dlig", 1)); } },
        { "no-discretionary-ligatures",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("dlig", 0)); } },
        { "historical-ligatures",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("hlig", 1)); } },
        { "no-historical-ligatures",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("hlig", 0)); } },
        { "contextual",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("calt", 1)); } },
        { "no-contextual",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("calt", 0)); } },
    };
    auto iter = operators.find(fontVariant);
    if (iter != operators.end()) {
        iter->second(fontFeatures);
        return true;
    }
    return false;
}

bool ParseFontVariantEastAsian(const std::string& fontVariant, FONT_FEATURES_LIST& fontFeatures)
{
    if (fontVariant == FONT_FEATURE_NORMAL || fontVariant.empty()) {
        return true;
    }

    const std::unordered_map<std::string, void (*)(FONT_FEATURES_LIST&)> operators = {
        { "ruby", [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("ruby", 1)); } },
        { "jis78",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("jp78", 1)); } },
        { "jis83",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("jp83", 1)); } },
        { "jis90",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("jp90", 1)); } },
        { "jis04",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("jp04", 1)); } },
        { "simplified",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("smpl", 1)); } },
        { "traditional",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("trad", 1)); } },
        { "proportional-width",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("pwid", 1)); } },
        { "full-width",
            [](FONT_FEATURES_LIST& fontFeatures) { fontFeatures.emplace_back(std::make_pair("fwid", 1)); } },
    };
    auto iter = operators.find(fontVariant);
    if (iter != operators.end()) {
        iter->second(fontFeatures);
        return true;
    }
    return false;
}

void ParseFontVariant(const std::string& fontVariant, FONT_FEATURES_LIST& fontFeatures)
{
    if (fontVariant.empty()) {
        return;
    }
    auto tempFontVariant = fontVariant;
    StringUtils::TrimStrLeadingAndTrailing(tempFontVariant);
    if (ParseFontVariantCaps(tempFontVariant, fontFeatures)) {
        return;
    }
    if (ParseFontVariantNumeric(tempFontVariant, fontFeatures)) {
        return;
    }
    if (ParseFontVariantAlternates(tempFontVariant, fontFeatures)) {
        return;
    }
    if (ParseFontVariantLigatures(tempFontVariant, fontFeatures)) {
        return;
    }
    if (ParseFontVariantEastAsian(tempFontVariant, fontFeatures)) {
        return;
    }
}

/*
 * Format of font-feature-settings:
 * normal | none | <string>
 * number of <string> can be single or multiple, and separated by space ' '
 */
FONT_FEATURES_LIST ParseFontVariants(const std::string& fontVariants)
{
    FONT_FEATURES_LIST fontFeatures;
    if (fontVariants == FONT_FEATURE_NORMAL || fontVariants.empty()) {
        return fontFeatures;
    }

    if (fontVariants == FONT_FEATURE_NONE) {
        fontFeatures.emplace_back(std::make_pair("liga ", 0));
        fontFeatures.emplace_back(std::make_pair("clig ", 0));
        fontFeatures.emplace_back(std::make_pair("dlig ", 0));
        fontFeatures.emplace_back(std::make_pair("hlig ", 0));
        fontFeatures.emplace_back(std::make_pair("calt ", 0));
        return fontFeatures;
    }

    std::stringstream stream(fontVariants);
    std::string fontVariant;
    while (getline(stream, fontVariant, ' ')) {
        ParseFontVariant(fontVariant, fontFeatures);
    }
    return fontFeatures;
}

void ParseFontFeatureSetting(
    const std::string& fontFeatureSetting, FONT_FEATURES_LIST& fontFeatures)
{
    if (fontFeatureSetting.empty()) {
        return;
    }

    auto temp = fontFeatureSetting;
    StringUtils::TrimStrLeadingAndTrailing(temp);
    if (temp.empty()) {
        return;
    }

    std::vector<std::string> value;
    StringUtils::StringSplitter(temp, ' ', value);
    if (value.empty() || value.size() > FONT_FEATURE_MAX_SIZE || value[0].size() != FONT_FEATURE_KEY_LENGTH) {
        return;
    }

    switch (value.size()) {
        case 1:
            fontFeatures.emplace_back(std::make_pair(value[0], 1));
            break;
        case 2:
            fontFeatures.emplace_back(std::make_pair(value[0], ParseFontFeatureParameters(value[1])));
            break;
        default:
            break;
    }
}

/*
 * Format of font-feature-settings:
 * normal | <feature-tag-value>, where <feature-tag-value> = <string> [ <integer> | on | off ], like: "liga" 0
 * number of <feature-tag-value> can be single or multiple, and separated by comma ','
 */
ACE_FORCE_EXPORT FONT_FEATURES_LIST ParseFontFeatureSettings(const std::string& fontFeatureSettings)
{
    FONT_FEATURES_LIST fontFeatures;
    if (fontFeatureSettings == FONT_FEATURE_NORMAL || fontFeatureSettings.empty()) {
        return fontFeatures;
    }

    std::stringstream stream(fontFeatureSettings);
    std::string fontFeatureSetting;
    while (getline(stream, fontFeatureSetting, ',')) {
        ParseFontFeatureSetting(fontFeatureSetting, fontFeatures);
    }
    return fontFeatures;
}

std::string UnParseFontFeatureSetting(const FONT_FEATURES_LIST& fontFeatureSettings)
{
    std::stringstream strTemp;
    for (const auto& kv:fontFeatureSettings) {
        strTemp << kv.first << " " << kv.second << ",";
    }
    std::string fontFeatures = strTemp.str();
    if (!fontFeatures.empty()) {
        fontFeatures.pop_back();
    }
    return fontFeatures;
}
} // namespace OHOS::Ace