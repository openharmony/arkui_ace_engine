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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_FIXTURES_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_FIXTURES_H

#include <string>
#include <tuple>
#include <vector>

#include "arkoala_api.h"
#include "test_fixtures_enums.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Fixtures {
enum ResID {
    STRING_RES_0_ID,
    STRING_RES_1_ID,
    STRING_RES_2_ID,
    FONT_FAMILY_RESOURCE_0_ID,
    FONT_FAMILY_RESOURCE_1_ID,
    FONT_FAMILY_RESOURCE_2_ID,
    COLORS_RES_0_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_0_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_1_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_2_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_3_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_4_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_5_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_6_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_7_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_8_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_9_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_10_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_11_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_12_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_13_ID,
    OPACITY_RESOURCE_0_ID,
    OPACITY_RESOURCE_1_ID,
    OPACITY_RESOURCE_2_ID,
    OPACITY_RESOURCE_3_ID,
    OPACITY_RESOURCE_4_ID,
    OPACITY_RESOURCE_5_ID,
    OPACITY_RESOURCE_6_ID,
    OPACITY_RESOURCE_7_ID,
};

inline constexpr auto STRING_RES_0_STR = "STRING_RES_0_STR";
inline constexpr auto STRING_RES_1_STR = "STRING_RES_1_STR";
inline constexpr auto STRING_RES_2_STR = "STRING_RES_2_STR";
inline constexpr auto FONT_FAMILY_RESOURCE_0_STR = "FONT_FAMILY_RESOURCE_0_STR";
inline constexpr auto FONT_FAMILY_RESOURCE_1_STR = "FONT_FAMILY_RESOURCE_1_STR";
inline constexpr auto FONT_FAMILY_RESOURCE_2_STR = "FONT_FAMILY_RESOURCE_2_STR";
inline constexpr auto COLORS_RES_0_STR = "COLORS_RES_0_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR";
inline constexpr auto OPACITY_RESOURCE_0_STR = "OPACITY_RESOURCE_0_STR";
inline constexpr auto OPACITY_RESOURCE_1_STR = "OPACITY_RESOURCE_1_STR";
inline constexpr auto OPACITY_RESOURCE_2_STR = "OPACITY_RESOURCE_2_STR";
inline constexpr auto OPACITY_RESOURCE_3_STR = "OPACITY_RESOURCE_3_STR";
inline constexpr auto OPACITY_RESOURCE_4_STR = "OPACITY_RESOURCE_4_STR";
inline constexpr auto OPACITY_RESOURCE_5_STR = "OPACITY_RESOURCE_5_STR";
inline constexpr auto OPACITY_RESOURCE_6_STR = "OPACITY_RESOURCE_6_STR";
inline constexpr auto OPACITY_RESOURCE_7_STR = "OPACITY_RESOURCE_7_STR";

extern std::vector<std::tuple<ResID, std::string, ResRawValue>> resourceInitTable;

// Fixture 'Boolean' for type 'Ark_Boolean'
extern std::vector<std::tuple<std::string, Ark_Boolean, std::string>> testFixtureBooleanValidValues;

// Fixture 'String' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues;

// Fixture 'StringRes' for type 'Ark_Resource'
extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureStringResValidValues;

// Fixture 'FontFamilyResource' for type 'Ark_Resource'
extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureFontFamilyResourceValidValues;
extern std::vector<std::tuple<std::string, Ark_Resource>> testFixtureFontFamilyResourceInvalidValues;

// Fixture 'FontFamilyString' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontFamilyStringValidValues;
extern std::vector<std::tuple<std::string, Ark_String>> testFixtureFontFamilyStringInvalidValues;

// Fixture 'ColorsStr' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsStrValidValues;
extern std::vector<std::tuple<std::string, Ark_String>> testFixtureColorsStrInvalidValues;

// Fixture 'ColorsNum' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureColorsNumValidValues;

// Fixture 'ColorsRes' for type 'Ark_Resource'
extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsResValidValues;

// Fixture 'ColorsEnum' for type 'Ark_Color'
extern std::vector<std::tuple<std::string, Ark_Color, std::string>> testFixtureColorsEnumValidValues;
extern std::vector<std::tuple<std::string, Ark_Color>> testFixtureColorsEnumInvalidValues;

// Fixture 'LengthNonNegNonPct' for type 'Ark_Length'
extern std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNonNegNonPctValidValues;
extern std::vector<std::tuple<std::string, Ark_Length>> testFixtureLengthNonNegNonPctInvalidValues;

// Fixture 'LengthNonPct' for type 'Ark_Length'
extern std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNonPctValidValues;
extern std::vector<std::tuple<std::string, Ark_Length>> testFixtureLengthNonPctInvalidValues;

// Fixture 'LengthNonNeg' for type 'Ark_Length'
extern std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNonNegValidValues;
extern std::vector<std::tuple<std::string, Ark_Length>> testFixtureLengthNonNegInvalidValues;

// Fixture 'LengthAny' for type 'Ark_Length'
extern std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthAnyValidValues;

// Fixture 'DimensionsNumNonNeg' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureDimensionsNumNonNegValidValues;
extern std::vector<std::tuple<std::string, Ark_Number>> testFixtureDimensionsNumNonNegInvalidValues;

// Fixture 'DimensionsStrNonPerc' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonPercValidValues;
extern std::vector<std::tuple<std::string, Ark_String>> testFixtureDimensionsStrNonPercInvalidValues;

// Fixture 'DimensionsNumAny' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureDimensionsNumAnyValidValues;

// Fixture 'DimensionsStrNonNegNonPct' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonNegNonPctValidValues;
extern std::vector<std::tuple<std::string, Ark_String>> testFixtureDimensionsStrNonNegNonPctInvalidValues;

// Fixture 'DimensionsResNonNegNonPct' for type 'Ark_Resource'
extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureDimensionsResNonNegNonPctValidValues;
extern std::vector<std::tuple<std::string, Ark_Resource>> testFixtureDimensionsResNonNegNonPctInvalidValues;

// Fixture 'NumberAnything' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberAnythingValidValues;

// Fixture 'NumberNonNeg' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberNonNegValidValues;
extern std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberNonNegInvalidValues;

// Fixture 'NumberPosIntFloor' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberPosIntFloorValidValues;
extern std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberPosIntFloorInvalidValues;

// Fixture 'NumberNonNegIntFloor' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberNonNegIntFloorValidValues;
extern std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberNonNegIntFloorInvalidValues;

// Fixture 'NumberNonNegIntCeil' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberNonNegIntCeilValidValues;
extern std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberNonNegIntCeilInvalidValues;

// Fixture 'FontWeightNumbers' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureFontWeightNumbersValidValues;
extern std::vector<std::tuple<std::string, Ark_Number>> testFixtureFontWeightNumbersInvalidValues;

// Fixture 'FontWeightStrings' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontWeightStringsValidValues;
extern std::vector<std::tuple<std::string, Ark_String>> testFixtureFontWeightStringsInvalidValues;

// Fixture 'Opacity' for type 'Ark_Number'
extern std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureOpacityValidValues;

// Fixture 'OpacityResource' for type 'Ark_Resource'
extern std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureOpacityResourceValidValues;
} // namespace OHOS::Ace::NG::Fixtures
#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_FIXTURES_H
