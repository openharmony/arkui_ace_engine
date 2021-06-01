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

#include "core/components/theme/theme_utils.h"

#include <cmath>
#include <regex>
#include <set>

#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t THEME_ID_MIN_SIZE = 5; // Input should contain "@id"
constexpr uint32_t THEME_ID_MATCH_SIZE = 2;
const std::regex THEME_ID_REGEX(R"(^\"@id([0-9]+)\"$)", std::regex::icase); // regex for "@id001"
constexpr uint32_t THEME_ATTR_MIN_SIZE = 7;
const std::regex THEME_ATTR_REGEX(R"(\?theme:([a-zA-Z0-9_]+))"); // regex for "?theme:attr_color_emphasis"
constexpr uint32_t CUSTOM_STYLE_STRING_MAX_SIZE = 128;
constexpr uint32_t OHOS_ID_MIN_SIZE = 7; // Input should contain "@ohos_id"
constexpr uint32_t SYSTEM_RES_ID_START = 0x7000000;
const std::regex OHOS_ID_REGEX(R"(^@ohos_id_([0-9]+)$)", std::regex::icase); // regex for "@ohos_id_001"

const std::set<uint32_t> FONT_WEIGHT_STYLE_ID = {
    THEME_BUTTON_TEXT_FONTWEIGHT,
    THEME_DIALOG_TITLE_TEXT_FONTWEIGHT,
    THEME_TOAST_TEXT_TEXT_FONTWEIGHT,
    THEME_TEXTFIELD_FONT_WEIGHT,
    THEME_SEARCH_FONT_WEIGHT
};

} // namespace

IdParseResult ThemeUtils::ParseThemeIdReference(const std::string& str)
{
    std::smatch matches;
    IdParseResult result { .parseSuccess = false, .isIdRef = false, .id = 0, .refAttr = "" };
    if (str.size() > THEME_ID_MIN_SIZE && std::regex_match(str, matches, THEME_ID_REGEX)) {
        if (matches.size() == THEME_ID_MATCH_SIZE) {
            // Platform style id is no more than 32 bit.
            result.id = static_cast<uint32_t>(std::stoul(matches[1].str()));
            result.parseSuccess = true;
            result.isIdRef = true;
        }
    } else if (str.size() > THEME_ATTR_MIN_SIZE && std::regex_match(str, matches, THEME_ATTR_REGEX)) {
        if (matches.size() == THEME_ID_MATCH_SIZE) {
            result.refAttr = matches[1].str();
            result.parseSuccess = true;
            result.isIdRef = false;
        }
    } else if (str.size() > OHOS_ID_MIN_SIZE && std::regex_match(str, matches, OHOS_ID_REGEX)) {
        if (matches.size() == THEME_ID_MATCH_SIZE) {
            // Platform style id is no more than 32 bit.
            result.id = static_cast<uint32_t>(std::stoul(matches[1].str())) + SYSTEM_RES_ID_START;
            result.parseSuccess = true;
            result.isIdRef = true;
        }
    } else {
        // Not reference format, ignore.
    }
    return result;
}

ResValueWrapper ThemeUtils::ParseStyleValue(
    uint32_t styleId, const ResValueWrapper& model, const std::string& value)
{
    ResValueWrapper resultValue = { .type = model.type, .isPublic = model.isPublic };
    if (FONT_WEIGHT_STYLE_ID.count(styleId) > 0) {
        resultValue.value = static_cast<int32_t>(StringUtils::StringToFontWeight(value));
        return resultValue;
    }
    switch (model.type) {
        case ThemeConstantsType::COLOR:
            resultValue.value = Color::FromString(value, COLOR_ALPHA_MASK);
            break;
        case ThemeConstantsType::DIMENSION:
            resultValue.value = StringUtils::StringToDimension(value);
            break;
        case ThemeConstantsType::INT:
            resultValue.value = StringUtils::StringToInt(value);
            break;
        case ThemeConstantsType::DOUBLE:
            resultValue.value = StringUtils::StringToDouble(value);
            break;
        case ThemeConstantsType::STRING:
            if (value.size() < CUSTOM_STYLE_STRING_MAX_SIZE) {
                resultValue.value = value;
            } else {
                LOGE("Custom style value size over limit!");
                resultValue.type = ThemeConstantsType::ERROR;
            }
            break;
        default:
            resultValue.type = ThemeConstantsType::ERROR;
            break;
    }
    return resultValue;
}

} // namespace OHOS::Ace