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

#include "core/components_ng/pattern/text_field/text_field_type_utils.h"

#include <array>
#include <cstdint>
#include <string_view>

namespace OHOS::Ace::NG::TextFieldTypeUtils {
namespace {

struct InputTypeMapping {
    TextInputType type;
    std::string_view inputType;
    std::string_view textAreaType;
};

constexpr std::string_view DEFAULT_INPUT_TYPE = "InputType.Normal";
constexpr std::string_view DEFAULT_TEXT_AREA_TYPE = "TextAreaType.NORMAL";
constexpr std::array<InputTypeMapping, 11> MAPPINGS = {{
    { TextInputType::NUMBER, "InputType.Number", "TextAreaType.NUMBER" },
    { TextInputType::EMAIL_ADDRESS, "InputType.Email", "TextAreaType.EMAIL" },
    { TextInputType::PHONE, "InputType.PhoneNumber", "TextAreaType.PHONE_NUMBER" },
    { TextInputType::URL, "InputType.URL", "TextAreaType.URL" },
    { TextInputType::VISIBLE_PASSWORD, "InputType.Password", "InputType.Password" },
    { TextInputType::USER_NAME, "InputType.USER_NAME", "InputType.USER_NAME" },
    { TextInputType::NEW_PASSWORD, "InputType.NEW_PASSWORD", "InputType.NEW_PASSWORD" },
    { TextInputType::NUMBER_PASSWORD, "InputType.NUMBER_PASSWORD", "InputType.NUMBER_PASSWORD" },
    { TextInputType::NUMBER_DECIMAL, "InputType.NUMBER_DECIMAL", "TextAreaType.NUMBER_DECIMAL" },
    { TextInputType::ONE_TIME_CODE, "InputType.ONE_TIME_CODE", "TextAreaType.ONE_TIME_CODE" },
    { TextInputType::ONE_TIME_CODE_NUMBER,
        "InputType.ONE_TIME_CODE_NUMBER", "TextAreaType.ONE_TIME_CODE_NUMBER" },
}};

constexpr std::array<std::string_view, 39> CONTENT_TYPE_NAMES = {{
    "TextContentType.UNSPECIFIED",
    "TextContentType.USER_NAME",
    "TextContentType.VISIBLE_PASSWORD",
    "TextContentType.NEW_PASSWORD",
    "TextContentType.FULL_STREET_ADDRESS",
    "TextContentType.HOUSE_NUMBER",
    "TextContentType.DISTRICT_ADDRESS",
    "TextContentType.CITY_ADDRESS",
    "TextContentType.PROVINCE_ADDRESS",
    "TextContentType.COUNTRY_ADDRESS",
    "TextContentType.PERSON_FULL_NAME",
    "TextContentType.PERSON_LAST_NAME",
    "TextContentType.PERSON_FIRST_NAME",
    "TextContentType.PHONE_NUMBER",
    "TextContentType.PHONE_COUNTRY_CODE",
    "TextContentType.FULL_PHONE_NUMBER",
    "TextContentType.EMAIL_ADDRESS",
    "TextContentType.BANK_CARD_NUMBER",
    "TextContentType.ID_CARD_NUMBER",
    "TextContentType.PRECISE_TIME",
    "TextContentType.HOUR_AND_MINUTE",
    "TextContentType.DATE",
    "TextContentType.MONTH",
    "TextContentType.YEAR",
    "TextContentType.NICKNAME",
    "TextContentType.DETAIL_INFO_WITHOUT_STREET",
    "TextContentType.FORMAT_ADDRESS",
    "TextContentType.PASSPORT_NUMBER",
    "TextContentType.VALIDITY",
    "TextContentType.ISSUE_AT",
    "TextContentType.ORGANIZATION",
    "TextContentType.TAX_ID",
    "TextContentType.ADDRESS_CITY_AND_STATE",
    "TextContentType.FLIGHT_NUMBER",
    "TextContentType.LICENSE_NUMBER",
    "TextContentType.LICENSE_FILE_NUMBER",
    "TextContentType.LICENSE_PLATE",
    "TextContentType.ENGINE_NUMBER",
    "TextContentType.LICENSE_CHASSIS_NUMBER",
}};

std::string ToEnumName(std::string_view value)
{
    const auto separator = value.rfind('.');
    if (separator == std::string_view::npos) {
        return std::string(value);
    }
    return std::string(value.substr(separator + 1));
}

} // namespace

std::string ToInputTypeString(TextInputType type, bool isTextArea, bool isTextInput)
{
    for (const auto& mapping : MAPPINGS) {
        if (mapping.type == type) {
            return std::string(isTextArea ? mapping.textAreaType : mapping.inputType);
        }
    }
    return std::string(isTextInput ? DEFAULT_INPUT_TYPE : DEFAULT_TEXT_AREA_TYPE);
}

std::string ToContentTypeString(TextContentType type)
{
    // TextContentType::UNSPECIFIED is -1, so offset the enum value by one.
    auto index = static_cast<int64_t>(type) + 1;
    if (index < 0 || index >= static_cast<int64_t>(CONTENT_TYPE_NAMES.size())) {
        index = 0;
    }
    return std::string(CONTENT_TYPE_NAMES[static_cast<size_t>(index)]);
}

std::string ToInputTypeName(TextInputType type, bool isTextArea, bool isTextInput)
{
    return ToEnumName(ToInputTypeString(type, isTextArea, isTextInput));
}

std::string ToContentTypeName(TextContentType type)
{
    return ToEnumName(ToContentTypeString(type));
}

} // namespace OHOS::Ace::NG::TextFieldTypeUtils
