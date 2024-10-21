/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "test_fixtures.h"

#include "modifiers_test_utils.h"

#include "core/components/theme/theme_style.h"

namespace OHOS::Ace::NG::Fixtures {
std::vector<std::tuple<ResID, std::string, ResRawValue>> resourceInitTable = {
    { STRING_RES_0_ID, STRING_RES_0_STR, "abc" },
    { STRING_RES_1_ID, STRING_RES_1_STR, "" },
    { STRING_RES_2_ID, STRING_RES_2_STR, "xyz" },
    { COLORS_RES_0_ID, COLORS_RES_0_STR, Color(0xA1FAC0DE) },
};

// Fixture 'Boolean' for type 'Ark_Boolean'
std::vector<std::tuple<std::string, Ark_Boolean, std::string>> testFixtureBooleanValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

// Fixture 'String' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc" },
    { "\"\"", Converter::ArkValue<Ark_String>(""), "" },
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz"), "xyz" },
};

// Fixture 'StringRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureStringResValidValues = {
    { "ResId:STRING_RES_0_ID", CreateResource(STRING_RES_0_ID, NodeModifier::ResourceType::STRING), "abc" },
    { "ResName:STRING_RES_0_STR", CreateResource(STRING_RES_0_STR, NodeModifier::ResourceType::STRING), "abc" },
    { "ResId:STRING_RES_1_ID", CreateResource(STRING_RES_1_ID, NodeModifier::ResourceType::STRING), "" },
    { "ResName:STRING_RES_1_STR", CreateResource(STRING_RES_1_STR, NodeModifier::ResourceType::STRING), "" },
    { "ResId:STRING_RES_2_ID", CreateResource(STRING_RES_2_ID, NodeModifier::ResourceType::STRING), "xyz" },
    { "ResName:STRING_RES_2_STR", CreateResource(STRING_RES_2_STR, NodeModifier::ResourceType::STRING), "xyz" },
};

// Fixture 'ColorsStr' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsStrValidValues = {
    { "\"#123\"", Converter::ArkValue<Ark_String>("#123"), "#FF112233" },
    { "\"#11223344\"", Converter::ArkValue<Ark_String>("#11223344"), "#11223344" },
    { "\"#123456\"", Converter::ArkValue<Ark_String>("#123456"), "#FF123456" },
    { "\"65535\"", Converter::ArkValue<Ark_String>("65535"), "#FF00FFFF" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureColorsStrInvalidValues = {
    { "\"invalid\"", Converter::ArkValue<Ark_String>("invalid") },
    { "\"\"", Converter::ArkValue<Ark_String>("") },
};

// Fixture 'ColorsNum' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureColorsNumValidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0), "#00000000" },
    { "1", Converter::ArkValue<Ark_Number>(1), "#FF000001" },
    { "65535", Converter::ArkValue<Ark_Number>(65535), "#FF00FFFF" },
    { "-1", Converter::ArkValue<Ark_Number>(-1), "#FFFFFFFF" },
    { "0xBE7AC0DE", Converter::ArkValue<Ark_Number>(0xBE7AC0DE), "#BE7AC0DE" },
};

// Fixture 'ColorsRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsResValidValues = {
    { "ResId:COLORS_RES_0_ID", CreateResource(COLORS_RES_0_ID, NodeModifier::ResourceType::COLOR), "#A1FAC0DE" },
    { "ResName:COLORS_RES_0_STR", CreateResource(COLORS_RES_0_STR, NodeModifier::ResourceType::COLOR), "#A1FAC0DE" },
};

// Fixture 'ColorsEnum' for type 'Ark_Color'
std::vector<std::tuple<std::string, Ark_Color, std::string>> testFixtureColorsEnumValidValues = {
    { "ARK_COLOR_WHITE", Converter::ArkValue<Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
    { "ARK_COLOR_BLACK", Converter::ArkValue<Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
    { "ARK_COLOR_BLUE", Converter::ArkValue<Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "ARK_COLOR_BROWN", Converter::ArkValue<Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
    { "ARK_COLOR_GRAY", Converter::ArkValue<Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
    { "ARK_COLOR_GREEN", Converter::ArkValue<Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
    { "ARK_COLOR_GREY", Converter::ArkValue<Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
    { "ARK_COLOR_ORANGE", Converter::ArkValue<Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
    { "ARK_COLOR_PINK", Converter::ArkValue<Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
    { "ARK_COLOR_RED", Converter::ArkValue<Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
    { "ARK_COLOR_YELLOW", Converter::ArkValue<Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
    { "ARK_COLOR_TRANSPARENT", Converter::ArkValue<Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
};

std::vector<std::tuple<std::string, Ark_Color>> testFixtureColorsEnumInvalidValues = {
    { "static_cast<Ark_Color>(-1)", Converter::ArkValue<Ark_Color>(static_cast<Ark_Color>(-1)) },
    { "static_cast<Ark_Color>(INT_MAX)", Converter::ArkValue<Ark_Color>(static_cast<Ark_Color>(INT_MAX)) },
};

// Fixture 'DimensionsNumNonNeg' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureDimensionsNumNonNegValidValues = {
    { "123", Converter::ArkValue<Ark_Number>(123), "123.00vp" },
    { "0", Converter::ArkValue<Ark_Number>(0), "0.00vp" },
    { "1.23", Converter::ArkValue<Ark_Number>(1.23), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureDimensionsNumNonNegInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Number>(-1) },
};

// Fixture 'LengthNumNonNeg' for type 'Ark_Length'
std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNumNonNegValidValues = {
    { "123", Converter::ArkValue<Ark_Length>(123), "123.00vp" },
    { "0", Converter::ArkValue<Ark_Length>(0), "0.00vp" },
    { "1.23f", Converter::ArkValue<Ark_Length>(1.23f), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_Length>> testFixtureLengthNumNonNegInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Length>(-1) },
};

// Fixture 'DimensionsStrNonNegNonPct' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonNegNonPctValidValues = {
    { "\"123vp\"", Converter::ArkValue<Ark_String>("123vp"), "123.00vp" },
    { "\"0vp\"", Converter::ArkValue<Ark_String>("0vp"), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp"), "1.23vp" },
    { "\"123fp\"", Converter::ArkValue<Ark_String>("123fp"), "123.00fp" },
    { "\"0fp\"", Converter::ArkValue<Ark_String>("0fp"), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp"), "1.23fp" },
    { "\"123px\"", Converter::ArkValue<Ark_String>("123px"), "123.00px" },
    { "\"0px\"", Converter::ArkValue<Ark_String>("0px"), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px"), "1.23px" },
    { "\"123lpx\"", Converter::ArkValue<Ark_String>("123lpx"), "123.00lpx" },
    { "\"0lpx\"", Converter::ArkValue<Ark_String>("0lpx"), "0.00lpx" },
    { "\"1.23lpx\"", Converter::ArkValue<Ark_String>("1.23lpx"), "1.23lpx" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureDimensionsStrNonNegNonPctInvalidValues = {
    { "\"-123vp\"", Converter::ArkValue<Ark_String>("-123vp") },
    { "\"-123vp\"", Converter::ArkValue<Ark_String>("-123vp") },
    { "\"-123px\"", Converter::ArkValue<Ark_String>("-123px") },
    { "\"-123lpx\"", Converter::ArkValue<Ark_String>("-123lpx") },
    { "\"20%\"", Converter::ArkValue<Ark_String>("20%") },
    { "\"-20%\"", Converter::ArkValue<Ark_String>("-20%") },
};

// Fixture 'NumberAnything' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberAnythingValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100), "100" },
    { "0", Converter::ArkValue<Ark_Number>(0), "0" },
    { "-100", Converter::ArkValue<Ark_Number>(-100), "-100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34), "12.34" },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78), "-56.78" },
};

} // namespace OHOS::Ace::NG::Fixtures
