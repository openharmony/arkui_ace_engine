/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
Converter::ConvContext fixCtx;
std::vector<std::tuple<ResID, std::string, ResRawValue>> resourceInitTable = {
    { STRING_RES_0_ID, STRING_RES_0_STR, "abc" },
    { STRING_RES_1_ID, STRING_RES_1_STR, "" },
    { STRING_RES_2_ID, STRING_RES_2_STR, "xyz" },
    { STRING_RES_NO_EMPTY_0_ID, STRING_RES_NO_EMPTY_0_STR, "abc" },
    { STRING_RES_NO_EMPTY_1_ID, STRING_RES_NO_EMPTY_1_STR, "xyz" },
    { STRING_EMPTY_RES_UNDEFINED_0_ID, STRING_EMPTY_RES_UNDEFINED_0_STR, "" },
    { URI_STRING_RES_NO_EMPTY_0_ID, URI_STRING_RES_NO_EMPTY_0_STR, "abc" },
    { URI_STRING_RES_NO_EMPTY_1_ID, URI_STRING_RES_NO_EMPTY_1_STR, "xyz" },
    { IMAGE_URI_STRING_RES_NO_EMPTY_0_ID, IMAGE_URI_STRING_RES_NO_EMPTY_0_STR, "abc" },
    { FONT_FAMILY_RESOURCE_0_ID, FONT_FAMILY_RESOURCE_0_STR, "Arial" },
    { FONT_FAMILY_RESOURCE_1_ID, FONT_FAMILY_RESOURCE_1_STR, "Arial, Sans Serif" },
    { FONT_FAMILY_RESOURCE_2_ID, FONT_FAMILY_RESOURCE_2_STR, "" },
    { COLORS_RES_0_ID, COLORS_RES_0_STR, Color(0xA1FAC0DE) },
    { COLORS_ALPHA_20RES_0_ID, COLORS_ALPHA_20RES_0_STR, Color(0xA1FAC0DE) },
    { COLORS_ALPHA_20RES_1_ID, COLORS_ALPHA_20RES_1_STR, Color(0xFFFAC0DE) },
    { RES_DATA_FOR_LENGTH_0_ID, RES_DATA_FOR_LENGTH_0_STR, 432.0_vp },
    { RES_DATA_FOR_LENGTH_1_ID, RES_DATA_FOR_LENGTH_1_STR, 123.0_fp },
    { RES_DATA_FOR_LENGTH_2_ID, RES_DATA_FOR_LENGTH_2_STR, 22.55_px },
    { RES_DATA_FOR_LENGTH_3_ID, RES_DATA_FOR_LENGTH_3_STR, 0.5_pct },
    { RES_DATA_FOR_LENGTH_4_ID, RES_DATA_FOR_LENGTH_4_STR, 0.0_vp },
    { RES_DATA_FOR_LENGTH_5_ID, RES_DATA_FOR_LENGTH_5_STR, 0.0_fp },
    { RES_DATA_FOR_LENGTH_6_ID, RES_DATA_FOR_LENGTH_6_STR, 0.0_px },
    { RES_DATA_FOR_LENGTH_7_ID, RES_DATA_FOR_LENGTH_7_STR, 0.0_pct },
    { RES_DATA_FOR_LENGTH_8_ID, RES_DATA_FOR_LENGTH_8_STR, -2.3_vp },
    { RES_DATA_FOR_LENGTH_9_ID, RES_DATA_FOR_LENGTH_9_STR, -4.5_fp },
    { RES_DATA_FOR_LENGTH_10_ID, RES_DATA_FOR_LENGTH_10_STR, -5.6_px },
    { RES_DATA_FOR_LENGTH_11_ID, RES_DATA_FOR_LENGTH_11_STR, -0.8_pct },
    { DIMENSIONS_RES_ANY_0_ID, DIMENSIONS_RES_ANY_0_STR, 123.0_vp },
    { DIMENSIONS_RES_ANY_1_ID, DIMENSIONS_RES_ANY_1_STR, 0.0_vp },
    { DIMENSIONS_RES_ANY_2_ID, DIMENSIONS_RES_ANY_2_STR, 1.23_vp },
    { DIMENSIONS_RES_ANY_3_ID, DIMENSIONS_RES_ANY_3_STR, 123.0_fp },
    { DIMENSIONS_RES_ANY_4_ID, DIMENSIONS_RES_ANY_4_STR, 0.0_fp },
    { DIMENSIONS_RES_ANY_5_ID, DIMENSIONS_RES_ANY_5_STR, 1.23_fp },
    { DIMENSIONS_RES_ANY_6_ID, DIMENSIONS_RES_ANY_6_STR, 123.0_px },
    { DIMENSIONS_RES_ANY_7_ID, DIMENSIONS_RES_ANY_7_STR, 0.0_px },
    { DIMENSIONS_RES_ANY_8_ID, DIMENSIONS_RES_ANY_8_STR, 1.23_px },
    { DIMENSIONS_RES_ANY_9_ID, DIMENSIONS_RES_ANY_9_STR, -2.3_vp },
    { DIMENSIONS_RES_ANY_10_ID, DIMENSIONS_RES_ANY_10_STR, -4.5_fp },
    { DIMENSIONS_RES_ANY_11_ID, DIMENSIONS_RES_ANY_11_STR, -5.6_px },
    { DIMENSIONS_RES_ANY_12_ID, DIMENSIONS_RES_ANY_12_STR, 0.5_pct },
    { DIMENSIONS_RES_ANY_13_ID, DIMENSIONS_RES_ANY_13_STR, 0.0_pct },
    { DIMENSIONS_RES_ANY_14_ID, DIMENSIONS_RES_ANY_14_STR, -0.8_pct },
    { DIMENSIONS_RES_NON_NEG_0_ID, DIMENSIONS_RES_NON_NEG_0_STR, 123._vp },
    { DIMENSIONS_RES_NON_NEG_1_ID, DIMENSIONS_RES_NON_NEG_1_STR, 0._vp },
    { DIMENSIONS_RES_NON_NEG_2_ID, DIMENSIONS_RES_NON_NEG_2_STR, 1.23_vp },
    { DIMENSIONS_RES_NON_NEG_3_ID, DIMENSIONS_RES_NON_NEG_3_STR, 123._fp },
    { DIMENSIONS_RES_NON_NEG_4_ID, DIMENSIONS_RES_NON_NEG_4_STR, 0._fp },
    { DIMENSIONS_RES_NON_NEG_5_ID, DIMENSIONS_RES_NON_NEG_5_STR, 1.23_fp },
    { DIMENSIONS_RES_NON_NEG_6_ID, DIMENSIONS_RES_NON_NEG_6_STR, 123._px },
    { DIMENSIONS_RES_NON_NEG_7_ID, DIMENSIONS_RES_NON_NEG_7_STR, 0._px },
    { DIMENSIONS_RES_NON_NEG_8_ID, DIMENSIONS_RES_NON_NEG_8_STR, 1.23_px },
    { DIMENSIONS_RES_NON_NEG_9_ID, DIMENSIONS_RES_NON_NEG_9_STR, 0.2_pct },
    { DIMENSIONS_RES_NON_NEG_10_ID, DIMENSIONS_RES_NON_NEG_10_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_11_ID, DIMENSIONS_RES_NON_NEG_11_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_12_ID, DIMENSIONS_RES_NON_NEG_12_STR, -123._px },
    { DIMENSIONS_RES_NON_NEG_13_ID, DIMENSIONS_RES_NON_NEG_13_STR, -0.2_pct },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_0_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR, 123._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_1_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR, 0._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_2_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR, 1.23_vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_3_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR, 123._fp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_4_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR, 0._fp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_5_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR, 1.23_fp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_6_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR, 123._px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_7_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR, 0._px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_8_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR, 1.23_px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_9_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_10_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_11_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR, -123._px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_12_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR, 0.2_pct },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_13_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR, -0.2_pct },
    { DIMENSIONS_RES_NON_PCT_0_ID, DIMENSIONS_RES_NON_PCT_0_STR, 123._vp },
    { DIMENSIONS_RES_NON_PCT_1_ID, DIMENSIONS_RES_NON_PCT_1_STR, 0._vp },
    { DIMENSIONS_RES_NON_PCT_2_ID, DIMENSIONS_RES_NON_PCT_2_STR, 1.23_vp },
    { DIMENSIONS_RES_NON_PCT_3_ID, DIMENSIONS_RES_NON_PCT_3_STR, 123._fp },
    { DIMENSIONS_RES_NON_PCT_4_ID, DIMENSIONS_RES_NON_PCT_4_STR, 0._fp },
    { DIMENSIONS_RES_NON_PCT_5_ID, DIMENSIONS_RES_NON_PCT_5_STR, 1.23_fp },
    { DIMENSIONS_RES_NON_PCT_6_ID, DIMENSIONS_RES_NON_PCT_6_STR, 123._px },
    { DIMENSIONS_RES_NON_PCT_7_ID, DIMENSIONS_RES_NON_PCT_7_STR, 0._px },
    { DIMENSIONS_RES_NON_PCT_8_ID, DIMENSIONS_RES_NON_PCT_8_STR, 1.23_px },
    { DIMENSIONS_RES_NON_PCT_9_ID, DIMENSIONS_RES_NON_PCT_9_STR, -123._vp },
    { DIMENSIONS_RES_NON_PCT_10_ID, DIMENSIONS_RES_NON_PCT_10_STR, -123._fp },
    { DIMENSIONS_RES_NON_PCT_11_ID, DIMENSIONS_RES_NON_PCT_11_STR, -123._px },
    { DIMENSIONS_RES_NON_PCT_12_ID, DIMENSIONS_RES_NON_PCT_12_STR, 0.2_pct },
    { DIMENSIONS_RES_NON_PCT_13_ID, DIMENSIONS_RES_NON_PCT_13_STR, -0.2_pct },
    { MAX_FONT_SCALE_RES_0_ID, MAX_FONT_SCALE_RES_0_STR, 1.0f },
    { MAX_FONT_SCALE_RES_1_ID, MAX_FONT_SCALE_RES_1_STR, 3.41f },
    { MAX_FONT_SCALE_RES_2_ID, MAX_FONT_SCALE_RES_2_STR, 50.f },
    { MIN_FONT_SCALE_RES_0_ID, MIN_FONT_SCALE_RES_0_STR, 0.125f },
    { MIN_FONT_SCALE_RES_1_ID, MIN_FONT_SCALE_RES_1_STR, 0.5f },
    { MIN_FONT_SCALE_RES_2_ID, MIN_FONT_SCALE_RES_2_STR, 1.0f },
    { FONT_WEIGHT_RES_STRINGS_0_ID, FONT_WEIGHT_RES_STRINGS_0_STR, "100" },
    { FONT_WEIGHT_RES_STRINGS_1_ID, FONT_WEIGHT_RES_STRINGS_1_STR, "200" },
    { FONT_WEIGHT_RES_STRINGS_2_ID, FONT_WEIGHT_RES_STRINGS_2_STR, "300" },
    { FONT_WEIGHT_RES_STRINGS_3_ID, FONT_WEIGHT_RES_STRINGS_3_STR, "400" },
    { FONT_WEIGHT_RES_STRINGS_4_ID, FONT_WEIGHT_RES_STRINGS_4_STR, "500" },
    { FONT_WEIGHT_RES_STRINGS_5_ID, FONT_WEIGHT_RES_STRINGS_5_STR, "600" },
    { FONT_WEIGHT_RES_STRINGS_6_ID, FONT_WEIGHT_RES_STRINGS_6_STR, "700" },
    { FONT_WEIGHT_RES_STRINGS_7_ID, FONT_WEIGHT_RES_STRINGS_7_STR, "800" },
    { FONT_WEIGHT_RES_STRINGS_8_ID, FONT_WEIGHT_RES_STRINGS_8_STR, "900" },
    { FONT_WEIGHT_RES_STRINGS_9_ID, FONT_WEIGHT_RES_STRINGS_9_STR, "0" },
    { FONT_WEIGHT_RES_STRINGS_10_ID, FONT_WEIGHT_RES_STRINGS_10_STR, "1000" },
    { FONT_WEIGHT_RES_STRINGS_11_ID, FONT_WEIGHT_RES_STRINGS_11_STR, "-100" },
    { SCROLLABLE_FRICTION_RES_0_ID, SCROLLABLE_FRICTION_RES_0_STR, 0.125f },
    { SCROLLABLE_FRICTION_RES_1_ID, SCROLLABLE_FRICTION_RES_1_STR, 0.875f },
    { SCROLLABLE_FRICTION_RES_2_ID, SCROLLABLE_FRICTION_RES_2_STR, 2.0f },
    { SCROLLABLE_FRICTION_RES_3_ID, SCROLLABLE_FRICTION_RES_3_STR, 0.f },
    { SCROLLABLE_FRICTION_RES_4_ID, SCROLLABLE_FRICTION_RES_4_STR, -100.f },
    { OPACITY_RESOURCE_0_ID, OPACITY_RESOURCE_0_STR, 0.1f },
    { OPACITY_RESOURCE_1_ID, OPACITY_RESOURCE_1_STR, 0.0f },
    { OPACITY_RESOURCE_2_ID, OPACITY_RESOURCE_2_STR, 0.9f },
    { OPACITY_RESOURCE_3_ID, OPACITY_RESOURCE_3_STR, 1.0f },
    { OPACITY_RESOURCE_4_ID, OPACITY_RESOURCE_4_STR, -0.1f },
    { OPACITY_RESOURCE_5_ID, OPACITY_RESOURCE_5_STR, 100.0f },
    { OPACITY_RESOURCE_6_ID, OPACITY_RESOURCE_6_STR, -100.0f },
    { OPACITY_RESOURCE_7_ID, OPACITY_RESOURCE_7_STR, 1.1f },
    { FRICTION_RESOURCE_0_ID, FRICTION_RESOURCE_0_STR, 0.1f },
    { FRICTION_RESOURCE_1_ID, FRICTION_RESOURCE_1_STR, 0.0f },
    { FRICTION_RESOURCE_2_ID, FRICTION_RESOURCE_2_STR, 0.9f },
    { FRICTION_RESOURCE_3_ID, FRICTION_RESOURCE_3_STR, 1.0f },
    { FRICTION_RESOURCE_4_ID, FRICTION_RESOURCE_4_STR, -0.1f },
    { FRICTION_RESOURCE_5_ID, FRICTION_RESOURCE_5_STR, 100.0f },
    { FRICTION_RESOURCE_6_ID, FRICTION_RESOURCE_6_STR, -100.0f },
    { FRICTION_RESOURCE_7_ID, FRICTION_RESOURCE_7_STR, 1.1f },
    { TIME_FORMAT_RES_0_ID, TIME_FORMAT_RES_0_STR, "aa hh:mm:ss" },
    { TIME_FORMAT_RES_1_ID, TIME_FORMAT_RES_1_STR, "EEEE, M, d, yyyy" },
    { TIME_FORMAT_RES_2_ID, TIME_FORMAT_RES_2_STR, "MMM d, yyyy" },
    { TIME_FORMAT_RES_3_ID, TIME_FORMAT_RES_3_STR, "EEEE, M, d" },
    { TIME_FORMAT_RES_4_ID, TIME_FORMAT_RES_4_STR, "MMM dd" },
    { TIME_FORMAT_RES_5_ID, TIME_FORMAT_RES_5_STR, "MM/dd/yyyy" },
    { TIME_FORMAT_RES_6_ID, TIME_FORMAT_RES_6_STR, "EEEE MM dd" },
    { TIME_FORMAT_RES_7_ID, TIME_FORMAT_RES_7_STR, "yyyy" },
    { TIME_FORMAT_RES_8_ID, TIME_FORMAT_RES_8_STR, "yy" },
    { TIME_FORMAT_RES_9_ID, TIME_FORMAT_RES_9_STR, "MM" },
    { TIME_FORMAT_RES_10_ID, TIME_FORMAT_RES_10_STR, "M" },
    { TIME_FORMAT_RES_11_ID, TIME_FORMAT_RES_11_STR, "dd" },
    { TIME_FORMAT_RES_12_ID, TIME_FORMAT_RES_12_STR, "d" },
    { TIME_FORMAT_RES_13_ID, TIME_FORMAT_RES_13_STR, "EEEE" },
    { TIME_FORMAT_RES_14_ID, TIME_FORMAT_RES_14_STR, "E, EE, EEE" },
    { TIME_FORMAT_RES_15_ID, TIME_FORMAT_RES_15_STR, "MMM d, yyyy" },
    { TIME_FORMAT_RES_16_ID, TIME_FORMAT_RES_16_STR, "yyyy/M/d" },
    { TIME_FORMAT_RES_17_ID, TIME_FORMAT_RES_17_STR, "yyyy-M-d" },
    { TIME_FORMAT_RES_18_ID, TIME_FORMAT_RES_18_STR, "yyyy.M.d" },
    { TIME_FORMAT_RES_19_ID, TIME_FORMAT_RES_19_STR, "HH:mm:ss" },
    { TIME_FORMAT_RES_20_ID, TIME_FORMAT_RES_20_STR, "aa hh:mm:ss" },
    { TIME_FORMAT_RES_21_ID, TIME_FORMAT_RES_21_STR, "hh:mm:ss" },
    { TIME_FORMAT_RES_22_ID, TIME_FORMAT_RES_22_STR, "HH:mm" },
    { TIME_FORMAT_RES_23_ID, TIME_FORMAT_RES_23_STR, "aa hh:mm" },
    { TIME_FORMAT_RES_24_ID, TIME_FORMAT_RES_24_STR, "hh:mm" },
    { TIME_FORMAT_RES_25_ID, TIME_FORMAT_RES_25_STR, "mm:ss" },
    { TIME_FORMAT_RES_26_ID, TIME_FORMAT_RES_26_STR, "mm:ss.SS" },
    { TIME_FORMAT_RES_27_ID, TIME_FORMAT_RES_27_STR, "mm:ss.SSS" },
    { TIME_FORMAT_RES_28_ID, TIME_FORMAT_RES_28_STR, "hh:mm:ss aa" },
    { TIME_FORMAT_RES_29_ID, TIME_FORMAT_RES_29_STR, "HH" },
    { TIME_FORMAT_RES_30_ID, TIME_FORMAT_RES_30_STR, "" },
    { SHADOW_RADIUS_RES_0_ID, SHADOW_RADIUS_RES_0_STR, 0.1f },
    { SHADOW_RADIUS_RES_1_ID, SHADOW_RADIUS_RES_1_STR, 3.0f },
    { SHADOW_RADIUS_RES_2_ID, SHADOW_RADIUS_RES_2_STR, 0.9f },
    { SHADOW_RADIUS_RES_3_ID, SHADOW_RADIUS_RES_3_STR, 100.0f },
    { SHADOW_RADIUS_RES_4_ID, SHADOW_RADIUS_RES_4_STR, 1.1f },
    { SHADOW_RADIUS_RES_5_ID, SHADOW_RADIUS_RES_5_STR, -1 },
    { SHADOW_OFFSET_RES_0_ID, SHADOW_OFFSET_RES_0_STR, 0.1f },
    { SHADOW_OFFSET_RES_1_ID, SHADOW_OFFSET_RES_1_STR, 3.0f },
    { SHADOW_OFFSET_RES_2_ID, SHADOW_OFFSET_RES_2_STR, 0.9f },
    { SHADOW_OFFSET_RES_3_ID, SHADOW_OFFSET_RES_3_STR, -100.0f },
    { SHADOW_OFFSET_RES_4_ID, SHADOW_OFFSET_RES_4_STR, 99.0f },
    { SHADOW_OFFSET_RES_5_ID, SHADOW_OFFSET_RES_5_STR, -1.134f },
    { SHADOW_OFFSET_RES_6_ID, SHADOW_OFFSET_RES_6_STR, 1.1f },
};

// Fixture 'Boolean' for type 'Ark_Boolean'
std::vector<std::tuple<std::string, Ark_Boolean, std::string>> testFixtureBooleanValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true, &fixCtx), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false, &fixCtx), "false" },
};

// Fixture 'String' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc", &fixCtx), "abc" },
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx), "" },
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz", &fixCtx), "xyz" },
};

// Fixture 'StringNoEmpty' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringNoEmptyValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc", &fixCtx), "abc" },
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz", &fixCtx), "xyz" },
};

// Fixture 'StringRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureStringResValidValues = {
    { "ResId:STRING_RES_0_ID", CreateResource(STRING_RES_0_ID, ResourceType::STRING), "abc" },
    { "ResName:STRING_RES_0_STR", CreateResource(STRING_RES_0_STR, ResourceType::STRING), "abc" },
    { "ResId:STRING_RES_1_ID", CreateResource(STRING_RES_1_ID, ResourceType::STRING), "" },
    { "ResName:STRING_RES_1_STR", CreateResource(STRING_RES_1_STR, ResourceType::STRING), "" },
    { "ResId:STRING_RES_2_ID", CreateResource(STRING_RES_2_ID, ResourceType::STRING), "xyz" },
    { "ResName:STRING_RES_2_STR", CreateResource(STRING_RES_2_STR, ResourceType::STRING), "xyz" },
};

// Fixture 'StringResNoEmpty' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureStringResNoEmptyValidValues = {
    { "ResId:STRING_RES_NO_EMPTY_0_ID", CreateResource(STRING_RES_NO_EMPTY_0_ID, ResourceType::STRING), "abc" },
    { "ResName:STRING_RES_NO_EMPTY_0_STR", CreateResource(STRING_RES_NO_EMPTY_0_STR, ResourceType::STRING), "abc" },
    { "ResId:STRING_RES_NO_EMPTY_1_ID", CreateResource(STRING_RES_NO_EMPTY_1_ID, ResourceType::STRING), "xyz" },
    { "ResName:STRING_RES_NO_EMPTY_1_STR", CreateResource(STRING_RES_NO_EMPTY_1_STR, ResourceType::STRING), "xyz" },
};

// Fixture 'StringEmptyUndefined' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringEmptyUndefinedValidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx), "undefined" },
};

// Fixture 'StringEmptyResUndefined' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureStringEmptyResUndefinedValidValues = {
    { "ResId:STRING_EMPTY_RES_UNDEFINED_0_ID", CreateResource(STRING_EMPTY_RES_UNDEFINED_0_ID, ResourceType::STRING),
        "undefined" },
    { "ResName:STRING_EMPTY_RES_UNDEFINED_0_STR",
        CreateResource(STRING_EMPTY_RES_UNDEFINED_0_STR, ResourceType::STRING), "undefined" },
};

// Fixture 'UriString' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureUriStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc", &fixCtx), "file://abc" },
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz", &fixCtx), "file://xyz" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureUriStringInvalidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
};

// Fixture 'UriStringResNoEmpty' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureUriStringResNoEmptyValidValues = {
    { "ResId:URI_STRING_RES_NO_EMPTY_0_ID", CreateResource(URI_STRING_RES_NO_EMPTY_0_ID, ResourceType::STRING),
        "file://abc" },
    { "ResName:URI_STRING_RES_NO_EMPTY_0_STR", CreateResource(URI_STRING_RES_NO_EMPTY_0_STR, ResourceType::STRING),
        "file://abc" },
    { "ResId:URI_STRING_RES_NO_EMPTY_1_ID", CreateResource(URI_STRING_RES_NO_EMPTY_1_ID, ResourceType::STRING),
        "file://xyz" },
    { "ResName:URI_STRING_RES_NO_EMPTY_1_STR", CreateResource(URI_STRING_RES_NO_EMPTY_1_STR, ResourceType::STRING),
        "file://xyz" },
};

// Fixture 'ImageUriString' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureImageUriStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc", &fixCtx), "file://abc " },
};

// Fixture 'ImageUriStringResNoEmpty' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureImageUriStringResNoEmptyValidValues = {
    { "ResId:IMAGE_URI_STRING_RES_NO_EMPTY_0_ID",
        CreateResource(IMAGE_URI_STRING_RES_NO_EMPTY_0_ID, ResourceType::STRING), "file://abc " },
    { "ResName:IMAGE_URI_STRING_RES_NO_EMPTY_0_STR",
        CreateResource(IMAGE_URI_STRING_RES_NO_EMPTY_0_STR, ResourceType::STRING), "file://abc " },
};

// Fixture 'FontFamilyResource' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureFontFamilyResourceValidValues = {
    { "ResId:FONT_FAMILY_RESOURCE_0_ID", CreateResource(FONT_FAMILY_RESOURCE_0_ID, ResourceType::STRING), "Arial" },
    { "ResName:FONT_FAMILY_RESOURCE_0_STR", CreateResource(FONT_FAMILY_RESOURCE_0_STR, ResourceType::STRING), "Arial" },
    { "ResId:FONT_FAMILY_RESOURCE_1_ID", CreateResource(FONT_FAMILY_RESOURCE_1_ID, ResourceType::STRING),
        "Arial, Sans Serif" },
    { "ResName:FONT_FAMILY_RESOURCE_1_STR", CreateResource(FONT_FAMILY_RESOURCE_1_STR, ResourceType::STRING),
        "Arial, Sans Serif" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureFontFamilyResourceInvalidValues = {
    { "ResId:FONT_FAMILY_RESOURCE_2_ID", CreateResource(FONT_FAMILY_RESOURCE_2_ID, ResourceType::STRING) },
    { "ResName:FONT_FAMILY_RESOURCE_2_STR", CreateResource(FONT_FAMILY_RESOURCE_2_STR, ResourceType::STRING) },
};

// Fixture 'FontFamilyString' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontFamilyStringValidValues = {
    { "\"Arial\"", Converter::ArkValue<Ark_String>("Arial", &fixCtx), "Arial" },
    { "\"Arial, Sans Serif\"", Converter::ArkValue<Ark_String>("Arial, Sans Serif", &fixCtx), "Arial, Sans Serif" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureFontFamilyStringInvalidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
};

// Fixture 'ColorsStr' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsStrValidValues = {
    { "\"#123\"", Converter::ArkValue<Ark_String>("#123", &fixCtx), "#FF112233" },
    { "\"#11223344\"", Converter::ArkValue<Ark_String>("#11223344", &fixCtx), "#11223344" },
    { "\"#123456\"", Converter::ArkValue<Ark_String>("#123456", &fixCtx), "#FF123456" },
    { "\"65535\"", Converter::ArkValue<Ark_String>("65535", &fixCtx), "#FF00FFFF" },
    { "\"#abcdef\"", Converter::ArkValue<Ark_String>("#abcdef", &fixCtx), "#FFABCDEF" },
    { "\"#aBcdeF\"", Converter::ArkValue<Ark_String>("#aBcdeF", &fixCtx), "#FFABCDEF" },
    { "\"rgb(255, 100, 55)\"", Converter::ArkValue<Ark_String>("rgb(255, 100, 55)", &fixCtx), "#FFFF6437" },
    { "\"rgba(255, 100, 255, 0.5)\"", Converter::ArkValue<Ark_String>("rgba(255, 100, 255, 0.5)", &fixCtx),
        "#80FF64FF" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureColorsStrInvalidValues = {
    { "\"invalid\"", Converter::ArkValue<Ark_String>("invalid", &fixCtx) },
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
    { "\"rgb(270, 0xf1, 755.5f)\"", Converter::ArkValue<Ark_String>("rgb(270, 0xf1, 755.5f)", &fixCtx) },
    { "\"RgbA(255, 100, 255, 0.5)\"", Converter::ArkValue<Ark_String>("RgbA(255, 100, 255, 0.5)", &fixCtx) },
};

// Fixture 'ColorsAlpha20Str' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsAlpha20StrValidValues = {
    { "\"#123\"", Converter::ArkValue<Ark_String>("#123", &fixCtx), "#33112233" },
    { "\"#11223344\"", Converter::ArkValue<Ark_String>("#11223344", &fixCtx), "#11223344" },
    { "\"#123456\"", Converter::ArkValue<Ark_String>("#123456", &fixCtx), "#33123456" },
    { "\"65535\"", Converter::ArkValue<Ark_String>("65535", &fixCtx), "#3300FFFF" },
    { "\"#abcdef\"", Converter::ArkValue<Ark_String>("#abcdef", &fixCtx), "#33ABCDEF" },
    { "\"#aBcdeF\"", Converter::ArkValue<Ark_String>("#aBcdeF", &fixCtx), "#33ABCDEF" },
    { "\"rgb(255, 100, 55)\"", Converter::ArkValue<Ark_String>("rgb(255, 100, 55)", &fixCtx), "#33FF6437" },
    { "\"rgba(255, 100, 255, 0.5)\"", Converter::ArkValue<Ark_String>("rgba(255, 100, 255, 0.5)", &fixCtx),
        "#80FF64FF" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureColorsAlpha20StrInvalidValues = {
    { "\"invalid\"", Converter::ArkValue<Ark_String>("invalid", &fixCtx) },
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
    { "\"rgb(270, 0xf1, 755.5f)\"", Converter::ArkValue<Ark_String>("rgb(270, 0xf1, 755.5f)", &fixCtx) },
    { "\"RgbA(255, 100, 255, 0.5)\"", Converter::ArkValue<Ark_String>("RgbA(255, 100, 255, 0.5)", &fixCtx) },
};

// Fixture 'ColorsNum' for type 'Ark_Int32'
std::vector<std::tuple<std::string, Ark_Int32, std::string>> testFixtureColorsNumValidValues = {
    { "0", Converter::ArkValue<Ark_Int32>(0, &fixCtx), "#00000000" },
    { "1", Converter::ArkValue<Ark_Int32>(1, &fixCtx), "#FF000001" },
    { "65535", Converter::ArkValue<Ark_Int32>(65535, &fixCtx), "#FF00FFFF" },
    { "-1", Converter::ArkValue<Ark_Int32>(-1, &fixCtx), "#FFFFFFFF" },
    { "0xBE7AC0DE", Converter::ArkValue<Ark_Int32>(0xBE7AC0DE, &fixCtx), "#BE7AC0DE" },
    { "std::numeric_limits<float>::quiet_NaN()",
        Converter::ArkValue<Ark_Int32>(std::numeric_limits<float>::quiet_NaN(), &fixCtx), "#80000000" },
    { "std::numeric_limits<float>::infinity()",
        Converter::ArkValue<Ark_Int32>(std::numeric_limits<float>::infinity(), &fixCtx), "#80000000" },
};

// Fixture 'ColorsAlpha20Num' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureColorsAlpha20NumValidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "#00000000" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "#33000001" },
    { "65535", Converter::ArkValue<Ark_Number>(65535, &fixCtx), "#3300FFFF" },
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx), "#33FFFFFF" },
    { "0xBE7AC0DE", Converter::ArkValue<Ark_Number>(0xBE7AC0DE, &fixCtx), "#BE7AC0DE" },
    { "std::numeric_limits<float>::quiet_NaN()",
        Converter::ArkValue<Ark_Number>(std::numeric_limits<float>::quiet_NaN(), &fixCtx), "#80000000" },
    { "std::numeric_limits<float>::infinity()",
        Converter::ArkValue<Ark_Number>(std::numeric_limits<float>::infinity(), &fixCtx), "#80000000" },
};

// Fixture 'TextMaxLength' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureTextMaxLengthValidValues = {
    { "20", Converter::ArkValue<Ark_Number>(20, &fixCtx), "20" },
    { "22.5f", Converter::ArkValue<Ark_Number>(22.5f, &fixCtx), "22" },
    { "22.1f", Converter::ArkValue<Ark_Number>(22.1f, &fixCtx), "22" },
    { "22.4f", Converter::ArkValue<Ark_Number>(22.4f, &fixCtx), "22" },
    { "22.6f", Converter::ArkValue<Ark_Number>(22.6f, &fixCtx), "22" },
    { "22.9f", Converter::ArkValue<Ark_Number>(22.9f, &fixCtx), "22" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "-20", Converter::ArkValue<Ark_Number>(-20, &fixCtx), "INF" },
    { "0.0f", Converter::ArkValue<Ark_Number>(0.0f, &fixCtx), "0" },
    { "-22.5f", Converter::ArkValue<Ark_Number>(-22.5f, &fixCtx), "INF" },
};

// Fixture 'ColorsRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsResValidValues = {
    { "ResId:COLORS_RES_0_ID", CreateResource(COLORS_RES_0_ID, ResourceType::COLOR), "#A1FAC0DE" },
    { "ResName:COLORS_RES_0_STR", CreateResource(COLORS_RES_0_STR, ResourceType::COLOR), "#A1FAC0DE" },
};

// Fixture 'ColorsAlpha20Res' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsAlpha20ResValidValues = {
    { "ResId:COLORS_ALPHA_20RES_0_ID", CreateResource(COLORS_ALPHA_20RES_0_ID, ResourceType::COLOR), "#A1FAC0DE" },
    { "ResName:COLORS_ALPHA_20RES_0_STR", CreateResource(COLORS_ALPHA_20RES_0_STR, ResourceType::COLOR), "#A1FAC0DE" },
    { "ResId:COLORS_ALPHA_20RES_1_ID", CreateResource(COLORS_ALPHA_20RES_1_ID, ResourceType::COLOR), "#33FAC0DE" },
    { "ResName:COLORS_ALPHA_20RES_1_STR", CreateResource(COLORS_ALPHA_20RES_1_STR, ResourceType::COLOR), "#33FAC0DE" },
};

// Fixture 'TextAlignType' for type 'Ark_TextAlign'
std::vector<std::tuple<std::string, Ark_TextAlign, std::string>> testFixtureTextAlignTypeValidValues = {
    { "ARK_TEXT_ALIGN_CENTER", Converter::ArkValue<Ark_TextAlign>(ARK_TEXT_ALIGN_CENTER, &fixCtx), "TextAlign.Center" },
    { "ARK_TEXT_ALIGN_START", Converter::ArkValue<Ark_TextAlign>(ARK_TEXT_ALIGN_START, &fixCtx), "TextAlign.Start" },
    { "ARK_TEXT_ALIGN_END", Converter::ArkValue<Ark_TextAlign>(ARK_TEXT_ALIGN_END, &fixCtx), "TextAlign.End" },
    { "ARK_TEXT_ALIGN_JUSTIFY", Converter::ArkValue<Ark_TextAlign>(ARK_TEXT_ALIGN_JUSTIFY, &fixCtx),
        "TextAlign.Justify" },
};

std::vector<std::tuple<std::string, Ark_TextAlign>> testFixtureTextAlignTypeInvalidValues = {
    { "static_cast<Ark_TextAlign>(-1)", Converter::ArkValue<Ark_TextAlign>(static_cast<Ark_TextAlign>(-1), &fixCtx) },
    { "static_cast<Ark_TextAlign>(INT_MAX)",
        Converter::ArkValue<Ark_TextAlign>(static_cast<Ark_TextAlign>(INT_MAX), &fixCtx) },
};

// Fixture 'TextInputContentType' for type 'Ark_ContentType'
std::vector<std::tuple<std::string, Ark_ContentType, std::string>> testFixtureTextInputContentTypeValidValues = {
    { "ARK_CONTENT_TYPE_USER_NAME", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_USER_NAME, &fixCtx),
        "TextContentType.USER_NAME" },
    { "ARK_CONTENT_TYPE_PASSWORD", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_PASSWORD, &fixCtx),
        "TextContentType.VISIBLE_PASSWORD" },
    { "ARK_CONTENT_TYPE_NEW_PASSWORD", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_NEW_PASSWORD, &fixCtx),
        "TextContentType.NEW_PASSWORD" },
    { "ARK_CONTENT_TYPE_FULL_STREET_ADDRESS",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_FULL_STREET_ADDRESS, &fixCtx),
        "TextContentType.FULL_STREET_ADDRESS" },
    { "ARK_CONTENT_TYPE_HOUSE_NUMBER", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_HOUSE_NUMBER, &fixCtx),
        "TextContentType.HOUSE_NUMBER" },
    { "ARK_CONTENT_TYPE_DISTRICT_ADDRESS",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_DISTRICT_ADDRESS, &fixCtx),
        "TextContentType.DISTRICT_ADDRESS" },
    { "ARK_CONTENT_TYPE_CITY_ADDRESS", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_CITY_ADDRESS, &fixCtx),
        "TextContentType.CITY_ADDRESS" },
    { "ARK_CONTENT_TYPE_PROVINCE_ADDRESS",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_PROVINCE_ADDRESS, &fixCtx),
        "TextContentType.PROVINCE_ADDRESS" },
    { "ARK_CONTENT_TYPE_COUNTRY_ADDRESS",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_COUNTRY_ADDRESS, &fixCtx),
        "TextContentType.COUNTRY_ADDRESS" },
    { "ARK_CONTENT_TYPE_PERSON_FULL_NAME",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_PERSON_FULL_NAME, &fixCtx),
        "TextContentType.PERSON_FULL_NAME" },
    { "ARK_CONTENT_TYPE_PERSON_LAST_NAME",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_PERSON_LAST_NAME, &fixCtx),
        "TextContentType.PERSON_LAST_NAME" },
    { "ARK_CONTENT_TYPE_PERSON_FIRST_NAME",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_PERSON_FIRST_NAME, &fixCtx),
        "TextContentType.PERSON_FIRST_NAME" },
    { "ARK_CONTENT_TYPE_PHONE_NUMBER", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_PHONE_NUMBER, &fixCtx),
        "TextContentType.PHONE_NUMBER" },
    { "ARK_CONTENT_TYPE_PHONE_COUNTRY_CODE",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_PHONE_COUNTRY_CODE, &fixCtx),
        "TextContentType.PHONE_COUNTRY_CODE" },
    { "ARK_CONTENT_TYPE_FULL_PHONE_NUMBER",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_FULL_PHONE_NUMBER, &fixCtx),
        "TextContentType.FULL_PHONE_NUMBER" },
    { "ARK_CONTENT_TYPE_EMAIL_ADDRESS", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_EMAIL_ADDRESS, &fixCtx),
        "TextContentType.EMAIL_ADDRESS" },
    { "ARK_CONTENT_TYPE_BANK_CARD_NUMBER",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_BANK_CARD_NUMBER, &fixCtx),
        "TextContentType.BANK_CARD_NUMBER" },
    { "ARK_CONTENT_TYPE_ID_CARD_NUMBER", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_ID_CARD_NUMBER, &fixCtx),
        "TextContentType.ID_CARD_NUMBER" },
    { "ARK_CONTENT_TYPE_NICKNAME", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_NICKNAME, &fixCtx),
        "TextContentType.NICKNAME" },
    { "ARK_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET",
        Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET, &fixCtx),
        "TextContentType.DETAIL_INFO_WITHOUT_STREET" },
    { "ARK_CONTENT_TYPE_FORMAT_ADDRESS", Converter::ArkValue<Ark_ContentType>(ARK_CONTENT_TYPE_FORMAT_ADDRESS, &fixCtx),
        "TextContentType.FORMAT_ADDRESS" },
};

std::vector<std::tuple<std::string, Ark_ContentType>> testFixtureTextInputContentTypeInvalidValues = {
    { "static_cast<Ark_ContentType>(-1)",
        Converter::ArkValue<Ark_ContentType>(static_cast<Ark_ContentType>(-1), &fixCtx) },
    { "static_cast<Ark_ContentType>(INT_MAX)",
        Converter::ArkValue<Ark_ContentType>(static_cast<Ark_ContentType>(INT_MAX), &fixCtx) },
};

// Fixture 'TextInputCancelButtonStyle' for type 'Ark_CancelButtonStyle'
std::vector<std::tuple<std::string, Ark_CancelButtonStyle, std::string>>
    testFixtureTextInputCancelButtonStyleValidValues = {
        { "ARK_CANCEL_BUTTON_STYLE_CONSTANT",
            Converter::ArkValue<Ark_CancelButtonStyle>(ARK_CANCEL_BUTTON_STYLE_CONSTANT, &fixCtx), "0" },
        { "ARK_CANCEL_BUTTON_STYLE_INVISIBLE",
            Converter::ArkValue<Ark_CancelButtonStyle>(ARK_CANCEL_BUTTON_STYLE_INVISIBLE, &fixCtx), "1" },
        { "ARK_CANCEL_BUTTON_STYLE_INPUT",
            Converter::ArkValue<Ark_CancelButtonStyle>(ARK_CANCEL_BUTTON_STYLE_INPUT, &fixCtx), "2" },
    };

std::vector<std::tuple<std::string, Ark_CancelButtonStyle>> testFixtureTextInputCancelButtonStyleInvalidValues = {
    { "static_cast<Ark_CancelButtonStyle>(-1)",
        Converter::ArkValue<Ark_CancelButtonStyle>(static_cast<Ark_CancelButtonStyle>(-1), &fixCtx) },
    { "static_cast<Ark_CancelButtonStyle>(INT_MAX)",
        Converter::ArkValue<Ark_CancelButtonStyle>(static_cast<Ark_CancelButtonStyle>(INT_MAX), &fixCtx) },
};

// Fixture 'TextInputLineBreakStrategy' for type 'Ark_LineBreakStrategy'
std::vector<std::tuple<std::string, Ark_LineBreakStrategy, std::string>>
    testFixtureTextInputLineBreakStrategyValidValues = {
        { "ARK_LINE_BREAK_STRATEGY_GREEDY",
            Converter::ArkValue<Ark_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_GREEDY, &fixCtx), "greedy" },
        { "ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY",
            Converter::ArkValue<Ark_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY, &fixCtx), "high-quality" },
        { "ARK_LINE_BREAK_STRATEGY_BALANCED",
            Converter::ArkValue<Ark_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_BALANCED, &fixCtx), "balanced" },
    };

std::vector<std::tuple<std::string, Ark_LineBreakStrategy>> testFixtureTextInputLineBreakStrategyInvalidValues = {
    { "static_cast<Ark_LineBreakStrategy>(-1)",
        Converter::ArkValue<Ark_LineBreakStrategy>(static_cast<Ark_LineBreakStrategy>(-1), &fixCtx) },
    { "static_cast<Ark_LineBreakStrategy>(INT_MAX)",
        Converter::ArkValue<Ark_LineBreakStrategy>(static_cast<Ark_LineBreakStrategy>(INT_MAX), &fixCtx) },
};

// Fixture 'TextInputTextContentStyle' for type 'Ark_TextContentStyle'
std::vector<std::tuple<std::string, Ark_TextContentStyle, std::string>>
    testFixtureTextInputTextContentStyleValidValues = {
        { "ARK_TEXT_CONTENT_STYLE_DEFAULT",
            Converter::ArkValue<Ark_TextContentStyle>(ARK_TEXT_CONTENT_STYLE_DEFAULT, &fixCtx),
            "TextInputStyle.Default" },
        { "ARK_TEXT_CONTENT_STYLE_INLINE",
            Converter::ArkValue<Ark_TextContentStyle>(ARK_TEXT_CONTENT_STYLE_INLINE, &fixCtx),
            "TextInputStyle.Inline" },
    };

std::vector<std::tuple<std::string, Ark_TextContentStyle>> testFixtureTextInputTextContentStyleInvalidValues = {
    { "static_cast<Ark_TextContentStyle>(-1)",
        Converter::ArkValue<Ark_TextContentStyle>(static_cast<Ark_TextContentStyle>(-1), &fixCtx) },
    { "static_cast<Ark_TextContentStyle>(INT_MAX)",
        Converter::ArkValue<Ark_TextContentStyle>(static_cast<Ark_TextContentStyle>(INT_MAX), &fixCtx) },
};

// Fixture 'ImageSpanVerticalAlign' for type 'Ark_ImageSpanAlignment'
std::vector<std::tuple<std::string, Ark_ImageSpanAlignment, std::string>>
    testFixtureImageSpanVerticalAlignValidValues = {
        { "ARK_IMAGE_SPAN_ALIGNMENT_TOP",
            Converter::ArkValue<Ark_ImageSpanAlignment>(ARK_IMAGE_SPAN_ALIGNMENT_TOP, &fixCtx), "VerticalAlign.TOP" },
        { "ARK_IMAGE_SPAN_ALIGNMENT_CENTER",
            Converter::ArkValue<Ark_ImageSpanAlignment>(ARK_IMAGE_SPAN_ALIGNMENT_CENTER, &fixCtx),
            "VerticalAlign.CENTER" },
        { "ARK_IMAGE_SPAN_ALIGNMENT_BOTTOM",
            Converter::ArkValue<Ark_ImageSpanAlignment>(ARK_IMAGE_SPAN_ALIGNMENT_BOTTOM, &fixCtx),
            "VerticalAlign.BOTTOM" },
        { "ARK_IMAGE_SPAN_ALIGNMENT_BASELINE",
            Converter::ArkValue<Ark_ImageSpanAlignment>(ARK_IMAGE_SPAN_ALIGNMENT_BASELINE, &fixCtx),
            "VerticalAlign.BASELINE" },
    };

std::vector<std::tuple<std::string, Ark_ImageSpanAlignment>> testFixtureImageSpanVerticalAlignInvalidValues = {
    { "static_cast<Ark_ImageSpanAlignment>(-1)",
        Converter::ArkValue<Ark_ImageSpanAlignment>(static_cast<Ark_ImageSpanAlignment>(-1), &fixCtx) },
    { "static_cast<Ark_ImageSpanAlignment>(INT_MAX)",
        Converter::ArkValue<Ark_ImageSpanAlignment>(static_cast<Ark_ImageSpanAlignment>(INT_MAX), &fixCtx) },
};

// Fixture 'ProgressType' for type 'Ark_ProgressType'
std::vector<std::tuple<std::string, Ark_ProgressType, std::string>> testFixtureProgressTypeValidValues = {
    { "ARK_PROGRESS_TYPE_LINEAR", Converter::ArkValue<Ark_ProgressType>(ARK_PROGRESS_TYPE_LINEAR, &fixCtx),
        "ProgressStyle.Linear" },
    { "ARK_PROGRESS_TYPE_RING", Converter::ArkValue<Ark_ProgressType>(ARK_PROGRESS_TYPE_RING, &fixCtx),
        "ProgressStyle.Ring" },
    { "ARK_PROGRESS_TYPE_ECLIPSE", Converter::ArkValue<Ark_ProgressType>(ARK_PROGRESS_TYPE_ECLIPSE, &fixCtx),
        "ProgressStyle.Eclipse" },
    { "ARK_PROGRESS_TYPE_SCALE_RING", Converter::ArkValue<Ark_ProgressType>(ARK_PROGRESS_TYPE_SCALE_RING, &fixCtx),
        "ProgressStyle.ScaleRing" },
    { "ARK_PROGRESS_TYPE_CAPSULE", Converter::ArkValue<Ark_ProgressType>(ARK_PROGRESS_TYPE_CAPSULE, &fixCtx),
        "ProgressStyle.Capsule" },
};

std::vector<std::tuple<std::string, Ark_ProgressType>> testFixtureProgressTypeInvalidValues = {
    { "static_cast<Ark_ProgressType>(-1)",
        Converter::ArkValue<Ark_ProgressType>(static_cast<Ark_ProgressType>(-1), &fixCtx) },
    { "static_cast<Ark_ProgressType>(INT_MAX)",
        Converter::ArkValue<Ark_ProgressType>(static_cast<Ark_ProgressType>(INT_MAX), &fixCtx) },
};

// Fixture 'ColorsEnum' for type 'Ark_arkui_component_enums_Color'
std::vector<std::tuple<std::string, Ark_arkui_component_enums_Color, std::string>>
    testFixtureColorsEnumValidValues = {
    { "ARK_COLOR_WHITE", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE, &fixCtx),
        "#FFFFFFFF" },
    { "ARK_COLOR_BLACK", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK, &fixCtx),
        "#FF000000" },
    { "ARK_COLOR_BLUE", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE, &fixCtx),
        "#FF0000FF" },
    { "ARK_COLOR_BROWN", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BROWN, &fixCtx),
        "#FFA52A2A" },
    { "ARK_COLOR_GRAY", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_GRAY, &fixCtx),
        "#FF808080" },
    { "ARK_COLOR_GREEN", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN, &fixCtx),
        "#FF008000" },
    { "ARK_COLOR_GREY", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREY, &fixCtx),
        "#FF808080" },
    { "ARK_COLOR_ORANGE", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_ORANGE, &fixCtx),
        "#FFFFA500" },
    { "ARK_COLOR_PINK", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_PINK, &fixCtx),
        "#FFFFC0CB" },
    { "ARK_COLOR_RED", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED, &fixCtx),
        "#FFFF0000" },
    { "ARK_COLOR_YELLOW", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_YELLOW, &fixCtx),
        "#FFFFFF00" },
    { "ARK_COLOR_TRANSPARENT", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_TRANSPARENT, &fixCtx),
        "#00000000" },
};

std::vector<std::tuple<std::string, Ark_arkui_component_enums_Color>> testFixtureColorsEnumInvalidValues = {
    { "static_cast<Ark_arkui_component_enums_Color>(-1)", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        static_cast<Ark_arkui_component_enums_Color>(-1), &fixCtx) },
    { "static_cast<Ark_arkui_component_enums_Color>(INT_MAX)", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        static_cast<Ark_arkui_component_enums_Color>(INT_MAX), &fixCtx) },
};

// Fixture 'ColorsAlpha20Enum' for type 'Ark_arkui_component_enums_Color'
std::vector<std::tuple<std::string, Ark_arkui_component_enums_Color, std::string>>
    testFixtureColorsAlpha20EnumValidValues = {
    { "ARK_COLOR_WHITE", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE, &fixCtx),
        "#33FFFFFF" },
    { "ARK_COLOR_BLACK", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK, &fixCtx),
        "#33000000" },
    { "ARK_COLOR_BLUE", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE, &fixCtx),
        "#330000FF" },
    { "ARK_COLOR_BROWN", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BROWN, &fixCtx),
        "#33A52A2A" },
    { "ARK_COLOR_GRAY", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_GRAY, &fixCtx),
        "#33808080" },
    { "ARK_COLOR_GREEN", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN, &fixCtx),
        "#33008000" },
    { "ARK_COLOR_GREY", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREY, &fixCtx),
        "#33808080" },
    { "ARK_COLOR_ORANGE", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_ORANGE, &fixCtx),
        "#33FFA500" },
    { "ARK_COLOR_PINK", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_PINK, &fixCtx),
        "#33FFC0CB" },
    { "ARK_COLOR_RED", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED, &fixCtx),
        "#33FF0000" },
    { "ARK_COLOR_YELLOW", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_YELLOW, &fixCtx),
        "#33FFFF00" },
    { "ARK_COLOR_TRANSPARENT", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_TRANSPARENT, &fixCtx),
        "#00000000" },
};

std::vector<std::tuple<std::string, Ark_arkui_component_enums_Color>> testFixtureColorsAlpha20EnumInvalidValues = {
    { "static_cast<Ark_arkui_component_enums_Color>(-1)", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        static_cast<Ark_arkui_component_enums_Color>(-1), &fixCtx) },
    { "static_cast<Ark_arkui_component_enums_Color>(INT_MAX)", Converter::ArkValue<Ark_arkui_component_enums_Color>(
        static_cast<Ark_arkui_component_enums_Color>(INT_MAX), &fixCtx) },
};

// Fixture 'VariableFontWeightEnum' for type 'Ark_FontWeight'
std::vector<std::tuple<std::string, Ark_FontWeight, std::string>> testFixtureVariableFontWeightEnumValidValues = {
    { "ARK_FONT_WEIGHT_LIGHTER", Converter::ArkValue<Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER, &fixCtx), "100" },
    { "ARK_FONT_WEIGHT_NORMAL", Converter::ArkValue<Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL, &fixCtx), "400" },
    { "ARK_FONT_WEIGHT_REGULAR", Converter::ArkValue<Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR, &fixCtx), "400" },
    { "ARK_FONT_WEIGHT_MEDIUM", Converter::ArkValue<Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM, &fixCtx), "500" },
    { "ARK_FONT_WEIGHT_BOLD", Converter::ArkValue<Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD, &fixCtx), "700" },
    { "ARK_FONT_WEIGHT_BOLDER", Converter::ArkValue<Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER, &fixCtx), "900" },
};

std::vector<std::tuple<std::string, Ark_FontWeight>> testFixtureVariableFontWeightEnumInvalidValues = {
    { "static_cast<Ark_FontWeight>(-1)",
        Converter::ArkValue<Ark_FontWeight>(static_cast<Ark_FontWeight>(-1), &fixCtx) },
    { "static_cast<Ark_FontWeight>(INT_MAX)",
        Converter::ArkValue<Ark_FontWeight>(static_cast<Ark_FontWeight>(INT_MAX), &fixCtx) },
};

// Fixture 'ImageRotateOrientation' for type 'Ark_ImageRotateOrientation'
std::vector<std::tuple<std::string, Ark_ImageRotateOrientation, std::string>>
    testFixtureImageRotateOrientationValidValues = {
        { "ARK_IMAGE_ROTATE_ORIENTATION_AUTO",
            Converter::ArkValue<Ark_ImageRotateOrientation>(ARK_IMAGE_ROTATE_ORIENTATION_AUTO, &fixCtx), "0" },
        { "ARK_IMAGE_ROTATE_ORIENTATION_UP",
            Converter::ArkValue<Ark_ImageRotateOrientation>(ARK_IMAGE_ROTATE_ORIENTATION_UP, &fixCtx), "1" },
        { "ARK_IMAGE_ROTATE_ORIENTATION_RIGHT",
            Converter::ArkValue<Ark_ImageRotateOrientation>(ARK_IMAGE_ROTATE_ORIENTATION_RIGHT, &fixCtx), "2" },
        { "ARK_IMAGE_ROTATE_ORIENTATION_DOWN",
            Converter::ArkValue<Ark_ImageRotateOrientation>(ARK_IMAGE_ROTATE_ORIENTATION_DOWN, &fixCtx), "3" },
        { "ARK_IMAGE_ROTATE_ORIENTATION_LEFT",
            Converter::ArkValue<Ark_ImageRotateOrientation>(ARK_IMAGE_ROTATE_ORIENTATION_LEFT, &fixCtx), "4" },
    };

std::vector<std::tuple<std::string, Ark_ImageRotateOrientation>> testFixtureImageRotateOrientationInvalidValues = {
    { "static_cast<Ark_ImageRotateOrientation>(-1)",
        Converter::ArkValue<Ark_ImageRotateOrientation>(static_cast<Ark_ImageRotateOrientation>(-1), &fixCtx) },
    { "static_cast<Ark_ImageRotateOrientation>(INT_MAX)",
        Converter::ArkValue<Ark_ImageRotateOrientation>(static_cast<Ark_ImageRotateOrientation>(INT_MAX), &fixCtx) },
};

// Fixture 'LengthNonNegNonPct' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureLengthNonNegNonPctValidValues = {
    { "\"123.0vp\"", Converter::ArkValue<Ark_String>("123.0vp", &fixCtx), "123.00vp" },
    { "\"0.0vp\"", Converter::ArkValue<Ark_String>("0.0vp", &fixCtx), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123.0fp\"", Converter::ArkValue<Ark_String>("123.0fp", &fixCtx), "123.00fp" },
    { "\"0.0fp\"", Converter::ArkValue<Ark_String>("0.0fp", &fixCtx), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123.0px\"", Converter::ArkValue<Ark_String>("123.0px", &fixCtx), "123.00px" },
    { "\"0.0px\"", Converter::ArkValue<Ark_String>("0.0px", &fixCtx), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureLengthNonNegNonPctInvalidValues = {
    { "\"-2.3vp\"", Converter::ArkValue<Ark_String>("-2.3vp", &fixCtx) },
    { "\"-4.5fp\"", Converter::ArkValue<Ark_String>("-4.5fp", &fixCtx) },
    { "\"-5.6px\"", Converter::ArkValue<Ark_String>("-5.6px", &fixCtx) },
    { "\"50%\"", Converter::ArkValue<Ark_String>("50%", &fixCtx) },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx) },
    { "\"-80%\"", Converter::ArkValue<Ark_String>("-80%", &fixCtx) },
};

// Fixture 'LengthPositivel' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureLengthPositivelValidValues = {
    { "\"123.0vp\"", Converter::ArkValue<Ark_String>("123.0vp", &fixCtx), "123.000000" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.230000" },
    { "\"123.0fp\"", Converter::ArkValue<Ark_String>("123.0fp", &fixCtx), "123.000000" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.230000" },
    { "\"123.0px\"", Converter::ArkValue<Ark_String>("123.0px", &fixCtx), "123.000000" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.230000" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureLengthPositivelInvalidValues = {
    { "\"-2.3vp\"", Converter::ArkValue<Ark_String>("-2.3vp", &fixCtx) },
    { "\"-4.5fp\"", Converter::ArkValue<Ark_String>("-4.5fp", &fixCtx) },
    { "\"-5.6px\"", Converter::ArkValue<Ark_String>("-5.6px", &fixCtx) },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx) },
    { "\"-80%\"", Converter::ArkValue<Ark_String>("-80%", &fixCtx) },
};

// Fixture 'LengthPosNonPct' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureLengthPosNonPctValidValues = {
    { "\"123.0vp\"", Converter::ArkValue<Ark_String>("123.0vp", &fixCtx), "123.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123.0fp\"", Converter::ArkValue<Ark_String>("123.0fp", &fixCtx), "123.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123.0px\"", Converter::ArkValue<Ark_String>("123.0px", &fixCtx), "123.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureLengthPosNonPctInvalidValues = {
    { "\"-2.3vp\"", Converter::ArkValue<Ark_String>("-2.3vp", &fixCtx) },
    { "\"-4.5fp\"", Converter::ArkValue<Ark_String>("-4.5fp", &fixCtx) },
    { "\"-5.6px\"", Converter::ArkValue<Ark_String>("-5.6px", &fixCtx) },
    { "\"50%\"", Converter::ArkValue<Ark_String>("50%", &fixCtx) },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx) },
    { "\"-80%\"", Converter::ArkValue<Ark_String>("-80%", &fixCtx) },
    { "\"0.0vp\"", Converter::ArkValue<Ark_String>("0.0vp", &fixCtx) },
    { "\"0.0fp\"", Converter::ArkValue<Ark_String>("0.0fp", &fixCtx) },
    { "\"0.0px\"", Converter::ArkValue<Ark_String>("0.0px", &fixCtx) },
};

// Fixture 'LengthNonPct' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureLengthNonPctValidValues = {
    { "\"123.0vp\"", Converter::ArkValue<Ark_String>("123.0vp", &fixCtx), "123.00vp" },
    { "\"0.0vp\"", Converter::ArkValue<Ark_String>("0.0vp", &fixCtx), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123.0fp\"", Converter::ArkValue<Ark_String>("123.0fp", &fixCtx), "123.00fp" },
    { "\"0.0fp\"", Converter::ArkValue<Ark_String>("0.0fp", &fixCtx), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123.0px\"", Converter::ArkValue<Ark_String>("123.0px", &fixCtx), "123.00px" },
    { "\"0.0px\"", Converter::ArkValue<Ark_String>("0.0px", &fixCtx), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
    { "\"-2.3vp\"", Converter::ArkValue<Ark_String>("-2.3vp", &fixCtx), "-2.30vp" },
    { "\"-4.5fp\"", Converter::ArkValue<Ark_String>("-4.5fp", &fixCtx), "-4.50fp" },
    { "\"-5.6px\"", Converter::ArkValue<Ark_String>("-5.6px", &fixCtx), "-5.60px" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureLengthNonPctInvalidValues = {
    { "\"50%\"", Converter::ArkValue<Ark_String>("50%", &fixCtx) },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx) },
    { "\"-80%\"", Converter::ArkValue<Ark_String>("-80%", &fixCtx) },
};

// Fixture 'LengthNonNeg' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureLengthNonNegValidValues = {
    { "\"123.0vp\"", Converter::ArkValue<Ark_String>("123.0vp", &fixCtx), "123.00vp" },
    { "\"0.0vp\"", Converter::ArkValue<Ark_String>("0.0vp", &fixCtx), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123.0fp\"", Converter::ArkValue<Ark_String>("123.0fp", &fixCtx), "123.00fp" },
    { "\"0.0fp\"", Converter::ArkValue<Ark_String>("0.0fp", &fixCtx), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123.0px\"", Converter::ArkValue<Ark_String>("123.0px", &fixCtx), "123.00px" },
    { "\"0.0px\"", Converter::ArkValue<Ark_String>("0.0px", &fixCtx), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
    { "\"50%\"", Converter::ArkValue<Ark_String>("50%", &fixCtx), "50.00%" },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx), "0.00%" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureLengthNonNegInvalidValues = {
    { "\"-2.3vp\"", Converter::ArkValue<Ark_String>("-2.3vp", &fixCtx) },
    { "\"-4.5fp\"", Converter::ArkValue<Ark_String>("-4.5fp", &fixCtx) },
    { "\"-5.6px\"", Converter::ArkValue<Ark_String>("-5.6px", &fixCtx) },
    { "\"-80%\"", Converter::ArkValue<Ark_String>("-80%", &fixCtx) },
};

// Fixture 'LengthPositive' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureLengthPositiveValidValues = {
    { "\"123.0vp\"", Converter::ArkValue<Ark_String>("123.0vp", &fixCtx), "123.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123.0fp\"", Converter::ArkValue<Ark_String>("123.0fp", &fixCtx), "123.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123.0px\"", Converter::ArkValue<Ark_String>("123.0px", &fixCtx), "123.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
    { "\"50%\"", Converter::ArkValue<Ark_String>("50%", &fixCtx), "50.00%" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureLengthPositiveInvalidValues = {
    { "\"0.0vp\"", Converter::ArkValue<Ark_String>("0.0vp", &fixCtx) },
    { "\"0.0fp\"", Converter::ArkValue<Ark_String>("0.0fp", &fixCtx) },
    { "\"0.0px\"", Converter::ArkValue<Ark_String>("0.0px", &fixCtx) },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx) },
    { "\"-2.3vp\"", Converter::ArkValue<Ark_String>("-2.3vp", &fixCtx) },
    { "\"-4.5fp\"", Converter::ArkValue<Ark_String>("-4.5fp", &fixCtx) },
    { "\"-5.6px\"", Converter::ArkValue<Ark_String>("-5.6px", &fixCtx) },
    { "\"-80%\"", Converter::ArkValue<Ark_String>("-80%", &fixCtx) },
};

// Fixture 'ResDataForLength' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureResDataForLengthValidValues = {
    { "ResId:RES_DATA_FOR_LENGTH_0_ID", CreateResource(RES_DATA_FOR_LENGTH_0_ID, ResourceType::FLOAT), "432.00vp" },
    { "ResName:RES_DATA_FOR_LENGTH_0_STR", CreateResource(RES_DATA_FOR_LENGTH_0_STR, ResourceType::FLOAT), "432.00vp" },
    { "ResId:RES_DATA_FOR_LENGTH_1_ID", CreateResource(RES_DATA_FOR_LENGTH_1_ID, ResourceType::FLOAT), "123.00fp" },
    { "ResName:RES_DATA_FOR_LENGTH_1_STR", CreateResource(RES_DATA_FOR_LENGTH_1_STR, ResourceType::FLOAT), "123.00fp" },
    { "ResId:RES_DATA_FOR_LENGTH_2_ID", CreateResource(RES_DATA_FOR_LENGTH_2_ID, ResourceType::FLOAT), "22.55px" },
    { "ResName:RES_DATA_FOR_LENGTH_2_STR", CreateResource(RES_DATA_FOR_LENGTH_2_STR, ResourceType::FLOAT), "22.55px" },
    { "ResId:RES_DATA_FOR_LENGTH_3_ID", CreateResource(RES_DATA_FOR_LENGTH_3_ID, ResourceType::FLOAT), "50.00%" },
    { "ResName:RES_DATA_FOR_LENGTH_3_STR", CreateResource(RES_DATA_FOR_LENGTH_3_STR, ResourceType::FLOAT), "50.00%" },
    { "ResId:RES_DATA_FOR_LENGTH_4_ID", CreateResource(RES_DATA_FOR_LENGTH_4_ID, ResourceType::FLOAT), "0.00vp" },
    { "ResName:RES_DATA_FOR_LENGTH_4_STR", CreateResource(RES_DATA_FOR_LENGTH_4_STR, ResourceType::FLOAT), "0.00vp" },
    { "ResId:RES_DATA_FOR_LENGTH_5_ID", CreateResource(RES_DATA_FOR_LENGTH_5_ID, ResourceType::FLOAT), "0.00fp" },
    { "ResName:RES_DATA_FOR_LENGTH_5_STR", CreateResource(RES_DATA_FOR_LENGTH_5_STR, ResourceType::FLOAT), "0.00fp" },
    { "ResId:RES_DATA_FOR_LENGTH_6_ID", CreateResource(RES_DATA_FOR_LENGTH_6_ID, ResourceType::FLOAT), "0.00px" },
    { "ResName:RES_DATA_FOR_LENGTH_6_STR", CreateResource(RES_DATA_FOR_LENGTH_6_STR, ResourceType::FLOAT), "0.00px" },
    { "ResId:RES_DATA_FOR_LENGTH_7_ID", CreateResource(RES_DATA_FOR_LENGTH_7_ID, ResourceType::FLOAT), "0.00%" },
    { "ResName:RES_DATA_FOR_LENGTH_7_STR", CreateResource(RES_DATA_FOR_LENGTH_7_STR, ResourceType::FLOAT), "0.00%" },
    { "ResId:RES_DATA_FOR_LENGTH_8_ID", CreateResource(RES_DATA_FOR_LENGTH_8_ID, ResourceType::FLOAT), "-2.30vp" },
    { "ResName:RES_DATA_FOR_LENGTH_8_STR", CreateResource(RES_DATA_FOR_LENGTH_8_STR, ResourceType::FLOAT), "-2.30vp" },
    { "ResId:RES_DATA_FOR_LENGTH_9_ID", CreateResource(RES_DATA_FOR_LENGTH_9_ID, ResourceType::FLOAT), "-4.50fp" },
    { "ResName:RES_DATA_FOR_LENGTH_9_STR", CreateResource(RES_DATA_FOR_LENGTH_9_STR, ResourceType::FLOAT), "-4.50fp" },
    { "ResId:RES_DATA_FOR_LENGTH_10_ID", CreateResource(RES_DATA_FOR_LENGTH_10_ID, ResourceType::FLOAT), "-5.60px" },
    { "ResName:RES_DATA_FOR_LENGTH_10_STR", CreateResource(RES_DATA_FOR_LENGTH_10_STR, ResourceType::FLOAT),
        "-5.60px" },
    { "ResId:RES_DATA_FOR_LENGTH_11_ID", CreateResource(RES_DATA_FOR_LENGTH_11_ID, ResourceType::FLOAT), "-80.00%" },
    { "ResName:RES_DATA_FOR_LENGTH_11_STR", CreateResource(RES_DATA_FOR_LENGTH_11_STR, ResourceType::FLOAT),
        "-80.00%" },
};

// Fixture 'LengthAny' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureLengthAnyValidValues = {
    { "\"123.0vp\"", Converter::ArkValue<Ark_String>("123.0vp", &fixCtx), "123.00vp" },
    { "\"0.0vp\"", Converter::ArkValue<Ark_String>("0.0vp", &fixCtx), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123.0fp\"", Converter::ArkValue<Ark_String>("123.0fp", &fixCtx), "123.00fp" },
    { "\"0.0fp\"", Converter::ArkValue<Ark_String>("0.0fp", &fixCtx), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123.0px\"", Converter::ArkValue<Ark_String>("123.0px", &fixCtx), "123.00px" },
    { "\"0.0px\"", Converter::ArkValue<Ark_String>("0.0px", &fixCtx), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
    { "\"-2.3vp\"", Converter::ArkValue<Ark_String>("-2.3vp", &fixCtx), "-2.30vp" },
    { "\"-4.5fp\"", Converter::ArkValue<Ark_String>("-4.5fp", &fixCtx), "-4.50fp" },
    { "\"-5.6px\"", Converter::ArkValue<Ark_String>("-5.6px", &fixCtx), "-5.60px" },
    { "\"50%\"", Converter::ArkValue<Ark_String>("50%", &fixCtx), "50.00%" },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx), "0.00%" },
    { "\"-80%\"", Converter::ArkValue<Ark_String>("-80%", &fixCtx), "-80.00%" },
};

// Fixture 'LengthMetricsNonNeg_' for type 'Ark_LengthMetrics'
std::vector<std::tuple<std::string, Ark_LengthMetrics, std::string>> testFixtureLengthMetricsNonNeg_ValidValues = {
    { "123.0_vp", Converter::ArkValue<Ark_LengthMetrics>(123.0_vp, &fixCtx), "123.00vp" },
    { "0.0_vp", Converter::ArkValue<Ark_LengthMetrics>(0.0_vp, &fixCtx), "0.00vp" },
    { "1.23_vp", Converter::ArkValue<Ark_LengthMetrics>(1.23_vp, &fixCtx), "1.23vp" },
    { "123.0_fp", Converter::ArkValue<Ark_LengthMetrics>(123.0_fp, &fixCtx), "123.00fp" },
    { "0.0_fp", Converter::ArkValue<Ark_LengthMetrics>(0.0_fp, &fixCtx), "0.00fp" },
    { "1.23_fp", Converter::ArkValue<Ark_LengthMetrics>(1.23_fp, &fixCtx), "1.23fp" },
    { "123.0_px", Converter::ArkValue<Ark_LengthMetrics>(123.0_px, &fixCtx), "123.00px" },
    { "0.0_px", Converter::ArkValue<Ark_LengthMetrics>(0.0_px, &fixCtx), "0.00px" },
    { "1.23_px", Converter::ArkValue<Ark_LengthMetrics>(1.23_px, &fixCtx), "1.23px" },
    { "0.5_pct", Converter::ArkValue<Ark_LengthMetrics>(0.5_pct, &fixCtx), "50.00%" },
    { "0.0_pct", Converter::ArkValue<Ark_LengthMetrics>(0.0_pct, &fixCtx), "0.00%" },
};

std::vector<std::tuple<std::string, Ark_LengthMetrics>> testFixtureLengthMetricsNonNeg_InvalidValues = {
    { "-2.3_vp", Converter::ArkValue<Ark_LengthMetrics>(-2.3_vp, &fixCtx) },
    { "-4.5_fp", Converter::ArkValue<Ark_LengthMetrics>(-4.5_fp, &fixCtx) },
    { "-5.6_px", Converter::ArkValue<Ark_LengthMetrics>(-5.6_px, &fixCtx) },
    { "-0.8_pct", Converter::ArkValue<Ark_LengthMetrics>(-0.8_pct, &fixCtx) },
};

// Fixture 'BaselineOffsetNum' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureBaselineOffsetNumValidValues = {
    { "123", Converter::ArkValue<Ark_Number>(123, &fixCtx), "123" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "-2", Converter::ArkValue<Ark_Number>(-2, &fixCtx), "-2" },
};

// Fixture 'BaselineOffsetStr' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureBaselineOffsetStrValidValues = {
    { "\"123vp\"", Converter::ArkValue<Ark_String>("123vp", &fixCtx), "123" },
    { "\"-123vp\"", Converter::ArkValue<Ark_String>("-123vp", &fixCtx), "-123" },
    { "\"0vp\"", Converter::ArkValue<Ark_String>("0vp", &fixCtx), "0" },
    { "\"123fp\"", Converter::ArkValue<Ark_String>("123fp", &fixCtx), "123" },
    { "\"-123fp\"", Converter::ArkValue<Ark_String>("-123fp", &fixCtx), "-123" },
    { "\"0fp\"", Converter::ArkValue<Ark_String>("0fp", &fixCtx), "0" },
    { "\"123px\"", Converter::ArkValue<Ark_String>("123px", &fixCtx), "123" },
    { "\"-123px\"", Converter::ArkValue<Ark_String>("-123px", &fixCtx), "-123" },
    { "\"0px\"", Converter::ArkValue<Ark_String>("0px", &fixCtx), "0" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1" },
    { "\"123lpx\"", Converter::ArkValue<Ark_String>("123lpx", &fixCtx), "123" },
    { "\"-123lpx\"", Converter::ArkValue<Ark_String>("-123lpx", &fixCtx), "-123" },
    { "\"0lpx\"", Converter::ArkValue<Ark_String>("0lpx", &fixCtx), "0" },
};

// Fixture 'CopyOptions' for type 'Ark_CopyOptions'
std::vector<std::tuple<std::string, Ark_CopyOptions, std::string>> testFixtureCopyOptionsValidValues = {
    { "ARK_COPY_OPTIONS_NONE", Converter::ArkValue<Ark_CopyOptions>(ARK_COPY_OPTIONS_NONE, &fixCtx),
        "CopyOptions.None" },
    { "ARK_COPY_OPTIONS_IN_APP", Converter::ArkValue<Ark_CopyOptions>(ARK_COPY_OPTIONS_IN_APP, &fixCtx),
        "CopyOptions.InApp" },
    { "ARK_COPY_OPTIONS_LOCAL_DEVICE", Converter::ArkValue<Ark_CopyOptions>(ARK_COPY_OPTIONS_LOCAL_DEVICE, &fixCtx),
        "CopyOptions.Local" },
};

std::vector<std::tuple<std::string, Ark_CopyOptions>> testFixtureCopyOptionsInvalidValues = {
    { "static_cast<Ark_CopyOptions>(-1)",
        Converter::ArkValue<Ark_CopyOptions>(static_cast<Ark_CopyOptions>(-1), &fixCtx) },
    { "static_cast<Ark_CopyOptions>(INT_MAX)",
        Converter::ArkValue<Ark_CopyOptions>(static_cast<Ark_CopyOptions>(INT_MAX), &fixCtx) },
};

// Fixture 'DummyColoringStrategy' for type 'Ark_ColoringStrategy'
std::vector<std::tuple<std::string, Ark_ColoringStrategy, std::string>>
    testFixtureDummyColoringStrategyValidValues = {};

// Fixture 'ShadowType' for type 'Ark_ShadowType'
std::vector<std::tuple<std::string, Ark_ShadowType, std::string>> testFixtureShadowTypeValidValues = {
    { "ARK_SHADOW_TYPE_COLOR", Converter::ArkValue<Ark_ShadowType>(ARK_SHADOW_TYPE_COLOR, &fixCtx), "0" },
    { "ARK_SHADOW_TYPE_BLUR", Converter::ArkValue<Ark_ShadowType>(ARK_SHADOW_TYPE_BLUR, &fixCtx), "1" },
};

// Fixture 'DimensionsNumNonNeg' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureDimensionsNumNonNegValidValues = {
    { "123", Converter::ArkValue<Ark_Float64>(123, &fixCtx), "123.00vp" },
    { "0", Converter::ArkValue<Ark_Float64>(0, &fixCtx), "0.00vp" },
    { "1.23", Converter::ArkValue<Ark_Float64>(1.23, &fixCtx), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_Float64>> testFixtureDimensionsNumNonNegInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Float64>(-1, &fixCtx) },
};

// Fixture 'DimensionsStrNonPerc' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonPercValidValues = {
    { "\"123vp\"", Converter::ArkValue<Ark_String>("123vp", &fixCtx), "123.00vp" },
    { "\"0fp\"", Converter::ArkValue<Ark_String>("0fp", &fixCtx), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureDimensionsStrNonPercInvalidValues = {
    { "\"20%\"", Converter::ArkValue<Ark_String>("20%", &fixCtx) },
    { "\"0%\"", Converter::ArkValue<Ark_String>("0%", &fixCtx) },
    { "\"-20%\"", Converter::ArkValue<Ark_String>("-20%", &fixCtx) },
};

// Fixture 'DimensionsNumAny' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureDimensionsNumAnyValidValues = {
    { "123", Converter::ArkValue<Ark_Number>(123, &fixCtx), "123.00vp" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0.00vp" },
    { "1.23", Converter::ArkValue<Ark_Number>(1.23, &fixCtx), "1.23vp" },
    { "-2", Converter::ArkValue<Ark_Number>(-2, &fixCtx), "-2.00vp" },
    { "-3.45", Converter::ArkValue<Ark_Number>(-3.45, &fixCtx), "-3.45vp" },
};

// Fixture 'DimensionsStrNonNeg' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonNegValidValues = {
    { "\"123vp\"", Converter::ArkValue<Ark_String>("123vp", &fixCtx), "123.00vp" },
    { "\"0vp\"", Converter::ArkValue<Ark_String>("0vp", &fixCtx), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123fp\"", Converter::ArkValue<Ark_String>("123fp", &fixCtx), "123.00fp" },
    { "\"0fp\"", Converter::ArkValue<Ark_String>("0fp", &fixCtx), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123px\"", Converter::ArkValue<Ark_String>("123px", &fixCtx), "123.00px" },
    { "\"0px\"", Converter::ArkValue<Ark_String>("0px", &fixCtx), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
    { "\"123lpx\"", Converter::ArkValue<Ark_String>("123lpx", &fixCtx), "123.00lpx" },
    { "\"0lpx\"", Converter::ArkValue<Ark_String>("0lpx", &fixCtx), "0.00lpx" },
    { "\"1.23lpx\"", Converter::ArkValue<Ark_String>("1.23lpx", &fixCtx), "1.23lpx" },
    { "\"20%\"", Converter::ArkValue<Ark_String>("20%", &fixCtx), "20.00%" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureDimensionsStrNonNegInvalidValues = {
    { "\"-123vp\"", Converter::ArkValue<Ark_String>("-123vp", &fixCtx) },
    { "\"-123vp\"", Converter::ArkValue<Ark_String>("-123vp", &fixCtx) },
    { "\"-123px\"", Converter::ArkValue<Ark_String>("-123px", &fixCtx) },
    { "\"-123lpx\"", Converter::ArkValue<Ark_String>("-123lpx", &fixCtx) },
    { "\"-20%\"", Converter::ArkValue<Ark_String>("-20%", &fixCtx) },
};

// Fixture 'DimensionsStrNonNegNonPct' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonNegNonPctValidValues = {
    { "\"123vp\"", Converter::ArkValue<Ark_String>("123vp", &fixCtx), "123.00vp" },
    { "\"0vp\"", Converter::ArkValue<Ark_String>("0vp", &fixCtx), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp", &fixCtx), "1.23vp" },
    { "\"123fp\"", Converter::ArkValue<Ark_String>("123fp", &fixCtx), "123.00fp" },
    { "\"0fp\"", Converter::ArkValue<Ark_String>("0fp", &fixCtx), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp", &fixCtx), "1.23fp" },
    { "\"123px\"", Converter::ArkValue<Ark_String>("123px", &fixCtx), "123.00px" },
    { "\"0px\"", Converter::ArkValue<Ark_String>("0px", &fixCtx), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px", &fixCtx), "1.23px" },
    { "\"123lpx\"", Converter::ArkValue<Ark_String>("123lpx", &fixCtx), "123.00lpx" },
    { "\"0lpx\"", Converter::ArkValue<Ark_String>("0lpx", &fixCtx), "0.00lpx" },
    { "\"1.23lpx\"", Converter::ArkValue<Ark_String>("1.23lpx", &fixCtx), "1.23lpx" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureDimensionsStrNonNegNonPctInvalidValues = {
    { "\"-123vp\"", Converter::ArkValue<Ark_String>("-123vp", &fixCtx) },
    { "\"-123vp\"", Converter::ArkValue<Ark_String>("-123vp", &fixCtx) },
    { "\"-123px\"", Converter::ArkValue<Ark_String>("-123px", &fixCtx) },
    { "\"-123lpx\"", Converter::ArkValue<Ark_String>("-123lpx", &fixCtx) },
    { "\"20%\"", Converter::ArkValue<Ark_String>("20%", &fixCtx) },
    { "\"-20%\"", Converter::ArkValue<Ark_String>("-20%", &fixCtx) },
};

// Fixture 'DimensionsResAny' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureDimensionsResAnyValidValues = {
    { "ResId:DIMENSIONS_RES_ANY_0_ID", CreateResource(DIMENSIONS_RES_ANY_0_ID, ResourceType::FLOAT), "123.00vp" },
    { "ResName:DIMENSIONS_RES_ANY_0_STR", CreateResource(DIMENSIONS_RES_ANY_0_STR, ResourceType::FLOAT), "123.00vp" },
    { "ResId:DIMENSIONS_RES_ANY_1_ID", CreateResource(DIMENSIONS_RES_ANY_1_ID, ResourceType::FLOAT), "0.00vp" },
    { "ResName:DIMENSIONS_RES_ANY_1_STR", CreateResource(DIMENSIONS_RES_ANY_1_STR, ResourceType::FLOAT), "0.00vp" },
    { "ResId:DIMENSIONS_RES_ANY_2_ID", CreateResource(DIMENSIONS_RES_ANY_2_ID, ResourceType::FLOAT), "1.23vp" },
    { "ResName:DIMENSIONS_RES_ANY_2_STR", CreateResource(DIMENSIONS_RES_ANY_2_STR, ResourceType::FLOAT), "1.23vp" },
    { "ResId:DIMENSIONS_RES_ANY_3_ID", CreateResource(DIMENSIONS_RES_ANY_3_ID, ResourceType::FLOAT), "123.00fp" },
    { "ResName:DIMENSIONS_RES_ANY_3_STR", CreateResource(DIMENSIONS_RES_ANY_3_STR, ResourceType::FLOAT), "123.00fp" },
    { "ResId:DIMENSIONS_RES_ANY_4_ID", CreateResource(DIMENSIONS_RES_ANY_4_ID, ResourceType::FLOAT), "0.00fp" },
    { "ResName:DIMENSIONS_RES_ANY_4_STR", CreateResource(DIMENSIONS_RES_ANY_4_STR, ResourceType::FLOAT), "0.00fp" },
    { "ResId:DIMENSIONS_RES_ANY_5_ID", CreateResource(DIMENSIONS_RES_ANY_5_ID, ResourceType::FLOAT), "1.23fp" },
    { "ResName:DIMENSIONS_RES_ANY_5_STR", CreateResource(DIMENSIONS_RES_ANY_5_STR, ResourceType::FLOAT), "1.23fp" },
    { "ResId:DIMENSIONS_RES_ANY_6_ID", CreateResource(DIMENSIONS_RES_ANY_6_ID, ResourceType::FLOAT), "123.00px" },
    { "ResName:DIMENSIONS_RES_ANY_6_STR", CreateResource(DIMENSIONS_RES_ANY_6_STR, ResourceType::FLOAT), "123.00px" },
    { "ResId:DIMENSIONS_RES_ANY_7_ID", CreateResource(DIMENSIONS_RES_ANY_7_ID, ResourceType::FLOAT), "0.00px" },
    { "ResName:DIMENSIONS_RES_ANY_7_STR", CreateResource(DIMENSIONS_RES_ANY_7_STR, ResourceType::FLOAT), "0.00px" },
    { "ResId:DIMENSIONS_RES_ANY_8_ID", CreateResource(DIMENSIONS_RES_ANY_8_ID, ResourceType::FLOAT), "1.23px" },
    { "ResName:DIMENSIONS_RES_ANY_8_STR", CreateResource(DIMENSIONS_RES_ANY_8_STR, ResourceType::FLOAT), "1.23px" },
    { "ResId:DIMENSIONS_RES_ANY_9_ID", CreateResource(DIMENSIONS_RES_ANY_9_ID, ResourceType::FLOAT), "-2.30vp" },
    { "ResName:DIMENSIONS_RES_ANY_9_STR", CreateResource(DIMENSIONS_RES_ANY_9_STR, ResourceType::FLOAT), "-2.30vp" },
    { "ResId:DIMENSIONS_RES_ANY_10_ID", CreateResource(DIMENSIONS_RES_ANY_10_ID, ResourceType::FLOAT), "-4.50fp" },
    { "ResName:DIMENSIONS_RES_ANY_10_STR", CreateResource(DIMENSIONS_RES_ANY_10_STR, ResourceType::FLOAT), "-4.50fp" },
    { "ResId:DIMENSIONS_RES_ANY_11_ID", CreateResource(DIMENSIONS_RES_ANY_11_ID, ResourceType::FLOAT), "-5.60px" },
    { "ResName:DIMENSIONS_RES_ANY_11_STR", CreateResource(DIMENSIONS_RES_ANY_11_STR, ResourceType::FLOAT), "-5.60px" },
    { "ResId:DIMENSIONS_RES_ANY_12_ID", CreateResource(DIMENSIONS_RES_ANY_12_ID, ResourceType::FLOAT), "50.00%" },
    { "ResName:DIMENSIONS_RES_ANY_12_STR", CreateResource(DIMENSIONS_RES_ANY_12_STR, ResourceType::FLOAT), "50.00%" },
    { "ResId:DIMENSIONS_RES_ANY_13_ID", CreateResource(DIMENSIONS_RES_ANY_13_ID, ResourceType::FLOAT), "0.00%" },
    { "ResName:DIMENSIONS_RES_ANY_13_STR", CreateResource(DIMENSIONS_RES_ANY_13_STR, ResourceType::FLOAT), "0.00%" },
    { "ResId:DIMENSIONS_RES_ANY_14_ID", CreateResource(DIMENSIONS_RES_ANY_14_ID, ResourceType::FLOAT), "-80.00%" },
    { "ResName:DIMENSIONS_RES_ANY_14_STR", CreateResource(DIMENSIONS_RES_ANY_14_STR, ResourceType::FLOAT), "-80.00%" },
};

// Fixture 'DimensionsResNonNeg' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureDimensionsResNonNegValidValues = {
    { "ResId:DIMENSIONS_RES_NON_NEG_0_ID", CreateResource(DIMENSIONS_RES_NON_NEG_0_ID, ResourceType::FLOAT),
        "123.00vp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_0_STR", CreateResource(DIMENSIONS_RES_NON_NEG_0_STR, ResourceType::FLOAT),
        "123.00vp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_1_ID", CreateResource(DIMENSIONS_RES_NON_NEG_1_ID, ResourceType::FLOAT), "0.00vp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_1_STR", CreateResource(DIMENSIONS_RES_NON_NEG_1_STR, ResourceType::FLOAT),
        "0.00vp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_2_ID", CreateResource(DIMENSIONS_RES_NON_NEG_2_ID, ResourceType::FLOAT), "1.23vp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_2_STR", CreateResource(DIMENSIONS_RES_NON_NEG_2_STR, ResourceType::FLOAT),
        "1.23vp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_3_ID", CreateResource(DIMENSIONS_RES_NON_NEG_3_ID, ResourceType::FLOAT),
        "123.00fp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_3_STR", CreateResource(DIMENSIONS_RES_NON_NEG_3_STR, ResourceType::FLOAT),
        "123.00fp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_4_ID", CreateResource(DIMENSIONS_RES_NON_NEG_4_ID, ResourceType::FLOAT), "0.00fp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_4_STR", CreateResource(DIMENSIONS_RES_NON_NEG_4_STR, ResourceType::FLOAT),
        "0.00fp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_5_ID", CreateResource(DIMENSIONS_RES_NON_NEG_5_ID, ResourceType::FLOAT), "1.23fp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_5_STR", CreateResource(DIMENSIONS_RES_NON_NEG_5_STR, ResourceType::FLOAT),
        "1.23fp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_6_ID", CreateResource(DIMENSIONS_RES_NON_NEG_6_ID, ResourceType::FLOAT),
        "123.00px" },
    { "ResName:DIMENSIONS_RES_NON_NEG_6_STR", CreateResource(DIMENSIONS_RES_NON_NEG_6_STR, ResourceType::FLOAT),
        "123.00px" },
    { "ResId:DIMENSIONS_RES_NON_NEG_7_ID", CreateResource(DIMENSIONS_RES_NON_NEG_7_ID, ResourceType::FLOAT), "0.00px" },
    { "ResName:DIMENSIONS_RES_NON_NEG_7_STR", CreateResource(DIMENSIONS_RES_NON_NEG_7_STR, ResourceType::FLOAT),
        "0.00px" },
    { "ResId:DIMENSIONS_RES_NON_NEG_8_ID", CreateResource(DIMENSIONS_RES_NON_NEG_8_ID, ResourceType::FLOAT), "1.23px" },
    { "ResName:DIMENSIONS_RES_NON_NEG_8_STR", CreateResource(DIMENSIONS_RES_NON_NEG_8_STR, ResourceType::FLOAT),
        "1.23px" },
    { "ResId:DIMENSIONS_RES_NON_NEG_9_ID", CreateResource(DIMENSIONS_RES_NON_NEG_9_ID, ResourceType::FLOAT), "20.00%" },
    { "ResName:DIMENSIONS_RES_NON_NEG_9_STR", CreateResource(DIMENSIONS_RES_NON_NEG_9_STR, ResourceType::FLOAT),
        "20.00%" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureDimensionsResNonNegInvalidValues = {
    { "ResId:DIMENSIONS_RES_NON_NEG_10_ID", CreateResource(DIMENSIONS_RES_NON_NEG_10_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_10_STR", CreateResource(DIMENSIONS_RES_NON_NEG_10_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_NEG_11_ID", CreateResource(DIMENSIONS_RES_NON_NEG_11_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_11_STR", CreateResource(DIMENSIONS_RES_NON_NEG_11_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_NEG_12_ID", CreateResource(DIMENSIONS_RES_NON_NEG_12_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_12_STR", CreateResource(DIMENSIONS_RES_NON_NEG_12_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_NEG_13_ID", CreateResource(DIMENSIONS_RES_NON_NEG_13_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_13_STR", CreateResource(DIMENSIONS_RES_NON_NEG_13_STR, ResourceType::FLOAT) },
};

// Fixture 'DimensionsResNonNegNonPct' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureDimensionsResNonNegNonPctValidValues = {
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_0_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_0_ID, ResourceType::FLOAT), "123.00vp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR, ResourceType::FLOAT), "123.00vp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_1_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_1_ID, ResourceType::FLOAT), "0.00vp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR, ResourceType::FLOAT), "0.00vp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_2_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_2_ID, ResourceType::FLOAT), "1.23vp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR, ResourceType::FLOAT), "1.23vp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_3_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_3_ID, ResourceType::FLOAT), "123.00fp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR, ResourceType::FLOAT), "123.00fp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_4_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_4_ID, ResourceType::FLOAT), "0.00fp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR, ResourceType::FLOAT), "0.00fp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_5_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_5_ID, ResourceType::FLOAT), "1.23fp" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR, ResourceType::FLOAT), "1.23fp" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_6_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_6_ID, ResourceType::FLOAT), "123.00px" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR, ResourceType::FLOAT), "123.00px" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_7_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_7_ID, ResourceType::FLOAT), "0.00px" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR, ResourceType::FLOAT), "0.00px" },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_8_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_8_ID, ResourceType::FLOAT), "1.23px" },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR, ResourceType::FLOAT), "1.23px" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureDimensionsResNonNegNonPctInvalidValues = {
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_9_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_9_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_10_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_10_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_11_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_11_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_12_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_12_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_NEG_NON_PCT_13_ID",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_13_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR",
        CreateResource(DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR, ResourceType::FLOAT) },
};

// Fixture 'DimensionsResNonPct' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureDimensionsResNonPctValidValues = {
    { "ResId:DIMENSIONS_RES_NON_PCT_0_ID", CreateResource(DIMENSIONS_RES_NON_PCT_0_ID, ResourceType::FLOAT),
        "123.00vp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_0_STR", CreateResource(DIMENSIONS_RES_NON_PCT_0_STR, ResourceType::FLOAT),
        "123.00vp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_1_ID", CreateResource(DIMENSIONS_RES_NON_PCT_1_ID, ResourceType::FLOAT), "0.00vp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_1_STR", CreateResource(DIMENSIONS_RES_NON_PCT_1_STR, ResourceType::FLOAT),
        "0.00vp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_2_ID", CreateResource(DIMENSIONS_RES_NON_PCT_2_ID, ResourceType::FLOAT), "1.23vp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_2_STR", CreateResource(DIMENSIONS_RES_NON_PCT_2_STR, ResourceType::FLOAT),
        "1.23vp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_3_ID", CreateResource(DIMENSIONS_RES_NON_PCT_3_ID, ResourceType::FLOAT),
        "123.00fp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_3_STR", CreateResource(DIMENSIONS_RES_NON_PCT_3_STR, ResourceType::FLOAT),
        "123.00fp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_4_ID", CreateResource(DIMENSIONS_RES_NON_PCT_4_ID, ResourceType::FLOAT), "0.00fp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_4_STR", CreateResource(DIMENSIONS_RES_NON_PCT_4_STR, ResourceType::FLOAT),
        "0.00fp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_5_ID", CreateResource(DIMENSIONS_RES_NON_PCT_5_ID, ResourceType::FLOAT), "1.23fp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_5_STR", CreateResource(DIMENSIONS_RES_NON_PCT_5_STR, ResourceType::FLOAT),
        "1.23fp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_6_ID", CreateResource(DIMENSIONS_RES_NON_PCT_6_ID, ResourceType::FLOAT),
        "123.00px" },
    { "ResName:DIMENSIONS_RES_NON_PCT_6_STR", CreateResource(DIMENSIONS_RES_NON_PCT_6_STR, ResourceType::FLOAT),
        "123.00px" },
    { "ResId:DIMENSIONS_RES_NON_PCT_7_ID", CreateResource(DIMENSIONS_RES_NON_PCT_7_ID, ResourceType::FLOAT), "0.00px" },
    { "ResName:DIMENSIONS_RES_NON_PCT_7_STR", CreateResource(DIMENSIONS_RES_NON_PCT_7_STR, ResourceType::FLOAT),
        "0.00px" },
    { "ResId:DIMENSIONS_RES_NON_PCT_8_ID", CreateResource(DIMENSIONS_RES_NON_PCT_8_ID, ResourceType::FLOAT), "1.23px" },
    { "ResName:DIMENSIONS_RES_NON_PCT_8_STR", CreateResource(DIMENSIONS_RES_NON_PCT_8_STR, ResourceType::FLOAT),
        "1.23px" },
    { "ResId:DIMENSIONS_RES_NON_PCT_9_ID", CreateResource(DIMENSIONS_RES_NON_PCT_9_ID, ResourceType::FLOAT),
        "-123.00vp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_9_STR", CreateResource(DIMENSIONS_RES_NON_PCT_9_STR, ResourceType::FLOAT),
        "-123.00vp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_10_ID", CreateResource(DIMENSIONS_RES_NON_PCT_10_ID, ResourceType::FLOAT),
        "-123.00fp" },
    { "ResName:DIMENSIONS_RES_NON_PCT_10_STR", CreateResource(DIMENSIONS_RES_NON_PCT_10_STR, ResourceType::FLOAT),
        "-123.00fp" },
    { "ResId:DIMENSIONS_RES_NON_PCT_11_ID", CreateResource(DIMENSIONS_RES_NON_PCT_11_ID, ResourceType::FLOAT),
        "-123.00px" },
    { "ResName:DIMENSIONS_RES_NON_PCT_11_STR", CreateResource(DIMENSIONS_RES_NON_PCT_11_STR, ResourceType::FLOAT),
        "-123.00px" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureDimensionsResNonPctInvalidValues = {
    { "ResId:DIMENSIONS_RES_NON_PCT_12_ID", CreateResource(DIMENSIONS_RES_NON_PCT_12_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_PCT_12_STR", CreateResource(DIMENSIONS_RES_NON_PCT_12_STR, ResourceType::FLOAT) },
    { "ResId:DIMENSIONS_RES_NON_PCT_13_ID", CreateResource(DIMENSIONS_RES_NON_PCT_13_ID, ResourceType::FLOAT) },
    { "ResName:DIMENSIONS_RES_NON_PCT_13_STR", CreateResource(DIMENSIONS_RES_NON_PCT_13_STR, ResourceType::FLOAT) },
};

// Fixture 'MaxFontScaleNum' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMaxFontScaleNumValidValues = {
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1.000000" },
    { "2.5", Converter::ArkValue<Ark_Number>(2.5, &fixCtx), "2.500000" },
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100.000000" },
};

// Fixture 'MaxFontScaleRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureMaxFontScaleResValidValues = {
    { "ResId:MAX_FONT_SCALE_RES_0_ID", CreateResource(MAX_FONT_SCALE_RES_0_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:MAX_FONT_SCALE_RES_0_STR", CreateResource(MAX_FONT_SCALE_RES_0_STR, ResourceType::FLOAT), "1.000000" },
    { "ResId:MAX_FONT_SCALE_RES_1_ID", CreateResource(MAX_FONT_SCALE_RES_1_ID, ResourceType::FLOAT), "3.410000" },
    { "ResName:MAX_FONT_SCALE_RES_1_STR", CreateResource(MAX_FONT_SCALE_RES_1_STR, ResourceType::FLOAT), "3.410000" },
    { "ResId:MAX_FONT_SCALE_RES_2_ID", CreateResource(MAX_FONT_SCALE_RES_2_ID, ResourceType::FLOAT), "50.000000" },
    { "ResName:MAX_FONT_SCALE_RES_2_STR", CreateResource(MAX_FONT_SCALE_RES_2_STR, ResourceType::FLOAT), "50.000000" },
};

// Fixture 'MinFontScaleNum' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMinFontScaleNumValidValues = {
    { "0.1", Converter::ArkValue<Ark_Number>(0.1, &fixCtx), "0.100000" },
    { "0.89", Converter::ArkValue<Ark_Number>(0.89, &fixCtx), "0.890000" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1.000000" },
};

// Fixture 'MinFontScaleRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureMinFontScaleResValidValues = {
    { "ResId:MIN_FONT_SCALE_RES_0_ID", CreateResource(MIN_FONT_SCALE_RES_0_ID, ResourceType::FLOAT), "0.125000" },
    { "ResName:MIN_FONT_SCALE_RES_0_STR", CreateResource(MIN_FONT_SCALE_RES_0_STR, ResourceType::FLOAT), "0.125000" },
    { "ResId:MIN_FONT_SCALE_RES_1_ID", CreateResource(MIN_FONT_SCALE_RES_1_ID, ResourceType::FLOAT), "0.500000" },
    { "ResName:MIN_FONT_SCALE_RES_1_STR", CreateResource(MIN_FONT_SCALE_RES_1_STR, ResourceType::FLOAT), "0.500000" },
    { "ResId:MIN_FONT_SCALE_RES_2_ID", CreateResource(MIN_FONT_SCALE_RES_2_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:MIN_FONT_SCALE_RES_2_STR", CreateResource(MIN_FONT_SCALE_RES_2_STR, ResourceType::FLOAT), "1.000000" },
};

// Fixture 'NumberAnything' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberAnythingValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx), "-100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12.34" },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78, &fixCtx), "-56.78" },
};

// Fixture 'MotionBlurRadiusNumber' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMotionBlurRadiusNumberValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12.340000152587891" },
    { "10", Converter::ArkValue<Ark_Number>(10, &fixCtx), "10" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1" },
    { "0.1", Converter::ArkValue<Ark_Number>(0.1, &fixCtx), "0.10000000149011612" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "-0.1", Converter::ArkValue<Ark_Number>(-0.1, &fixCtx), "0" },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx), "0" },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78, &fixCtx), "0" },
};

// Fixture 'MotionBlurAnchorNumber' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMotionBlurAnchorNumberValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "1" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "1" },
    { "10", Converter::ArkValue<Ark_Number>(10, &fixCtx), "1" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1" },
    { "0.1", Converter::ArkValue<Ark_Number>(0.1, &fixCtx), "0.10000000149011612" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "-0.1", Converter::ArkValue<Ark_Number>(-0.1, &fixCtx), "0" },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx), "0" },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78, &fixCtx), "0" },
};

// Fixture 'NumberFloatAnything' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberFloatAnythingValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100.000000" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0.000000" },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx), "-100.000000" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12.340000" },
    { "-56.73", Converter::ArkValue<Ark_Number>(-56.73, &fixCtx), "-56.730000" },
};

// Fixture 'StringFloatAnything' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringFloatAnythingValidValues = {
    { "\"100\"", Converter::ArkValue<Ark_String>("100", &fixCtx), "100.000000" },
    { "\"0\"", Converter::ArkValue<Ark_String>("0", &fixCtx), "0.000000" },
    { "\"-100\"", Converter::ArkValue<Ark_String>("-100", &fixCtx), "-100.000000" },
    { "\"12.34\"", Converter::ArkValue<Ark_String>("12.34", &fixCtx), "12.340000" },
    { "\"-56.73\"", Converter::ArkValue<Ark_String>("-56.73", &fixCtx), "-56.730000" },
    { "\"Inf\"", Converter::ArkValue<Ark_String>("Inf", &fixCtx), "inf" },
    { "\"NaN\"", Converter::ArkValue<Ark_String>("NaN", &fixCtx), "nan" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureStringFloatAnythingInvalidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc", &fixCtx) },
};

// Fixture 'NumberFloatNonNeg' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberFloatNonNegValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100.000000" },
    { "50", Converter::ArkValue<Ark_Number>(50, &fixCtx), "50.000000" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0.000000" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberFloatNonNegInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
};

// Fixture 'NumberFloatPos' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberFloatPosValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100.000000" },
    { "50", Converter::ArkValue<Ark_Number>(50, &fixCtx), "50.000000" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberFloatPosInvalidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx) },
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
};

// Fixture 'NumberIntFloor' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberIntFloorValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx), "-100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12" },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78, &fixCtx), "-56" },
};

// Fixture 'NumberNonNeg' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberNonNegValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12.34" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberNonNegInvalidValues = {
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78, &fixCtx) },
};

// Fixture 'NumberPosIntFloor' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberPosIntFloorValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberPosIntFloorInvalidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx) },
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
    { "-23.45", Converter::ArkValue<Ark_Number>(-23.45, &fixCtx) },
};

// Fixture 'NumberNonNegIntFloor' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberNonNegIntFloorValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12" },
    { "12.55", Converter::ArkValue<Ark_Number>(12.55, &fixCtx), "12" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberNonNegIntFloorInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
    { "-23.45", Converter::ArkValue<Ark_Number>(-23.45, &fixCtx) },
};

// Fixture 'NumberNonNegIntCeil' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberNonNegIntCeilValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "13" },
    { "12.55", Converter::ArkValue<Ark_Number>(12.55, &fixCtx), "13" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberNonNegIntCeilInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
    { "-23.45", Converter::ArkValue<Ark_Number>(-23.45, &fixCtx) },
};

// Fixture 'FlingSpeedLimit' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureFlingSpeedLimitValidValues = {
    { "15000", Converter::ArkValue<Ark_Number>(15000, &fixCtx), "15000.00vp" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12.34vp" },
    { "0.05", Converter::ArkValue<Ark_Number>(0.05, &fixCtx), "0.05vp" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureFlingSpeedLimitInvalidValues = {
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78, &fixCtx) },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx) },
};

// Fixture 'TextMarqueeStep' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureTextMarqueeStepValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100.00" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12.34" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1.00" },
    { "0.09", Converter::ArkValue<Ark_Number>(0.09, &fixCtx), "0.09" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureTextMarqueeStepInvalidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx) },
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
    { "-23.45", Converter::ArkValue<Ark_Number>(-23.45, &fixCtx) },
};

// Fixture 'TextMarqueeLoop' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureTextMarqueeLoopValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "7", Converter::ArkValue<Ark_Number>(7, &fixCtx), "7" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "-1" },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx), "-1" },
    { "12.34", Converter::ArkValue<Ark_Number>(12.34, &fixCtx), "12" },
    { "-56.78", Converter::ArkValue<Ark_Number>(-56.78, &fixCtx), "-1" },
};

// Fixture 'NumberPercentageThresholdFloor' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberPercentageThresholdFloorValidValues = {
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1" },
    { "10", Converter::ArkValue<Ark_Number>(10, &fixCtx), "10" },
    { "22.2", Converter::ArkValue<Ark_Number>(22.2, &fixCtx), "22" },
    { "56.55", Converter::ArkValue<Ark_Number>(56.55, &fixCtx), "56" },
    { "99.0", Converter::ArkValue<Ark_Number>(99.0, &fixCtx), "99" },
    { "99.9", Converter::ArkValue<Ark_Number>(99.9, &fixCtx), "99" },
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "100.1", Converter::ArkValue<Ark_Number>(100.1, &fixCtx), "100" },
    { "100.99", Converter::ArkValue<Ark_Number>(100.99, &fixCtx), "100" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureNumberPercentageThresholdFloorInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
    { "-23.1", Converter::ArkValue<Ark_Number>(-23.1, &fixCtx) },
    { "-33.6", Converter::ArkValue<Ark_Number>(-33.6, &fixCtx) },
    { "101", Converter::ArkValue<Ark_Number>(101, &fixCtx) },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx) },
    { "0.1", Converter::ArkValue<Ark_Number>(0.1, &fixCtx) },
    { "0.99", Converter::ArkValue<Ark_Number>(0.99, &fixCtx) },
};

// Fixture 'FontWeightNumbers' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureFontWeightNumbersValidValues = {
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100" },
    { "200", Converter::ArkValue<Ark_Number>(200, &fixCtx), "200" },
    { "300", Converter::ArkValue<Ark_Number>(300, &fixCtx), "300" },
    { "400", Converter::ArkValue<Ark_Number>(400, &fixCtx), "400" },
    { "500", Converter::ArkValue<Ark_Number>(500, &fixCtx), "500" },
    { "600", Converter::ArkValue<Ark_Number>(600, &fixCtx), "600" },
    { "700", Converter::ArkValue<Ark_Number>(700, &fixCtx), "700" },
    { "800", Converter::ArkValue<Ark_Number>(800, &fixCtx), "800" },
    { "900", Converter::ArkValue<Ark_Number>(900, &fixCtx), "900" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureFontWeightNumbersInvalidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx) },
    { "1000", Converter::ArkValue<Ark_Number>(1000, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
};

// Fixture 'FontWeightStrings' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontWeightStringsValidValues = {
    { "\"100\"", Converter::ArkValue<Ark_String>("100", &fixCtx), "100" },
    { "\"200\"", Converter::ArkValue<Ark_String>("200", &fixCtx), "200" },
    { "\"300\"", Converter::ArkValue<Ark_String>("300", &fixCtx), "300" },
    { "\"400\"", Converter::ArkValue<Ark_String>("400", &fixCtx), "400" },
    { "\"500\"", Converter::ArkValue<Ark_String>("500", &fixCtx), "500" },
    { "\"600\"", Converter::ArkValue<Ark_String>("600", &fixCtx), "600" },
    { "\"700\"", Converter::ArkValue<Ark_String>("700", &fixCtx), "700" },
    { "\"800\"", Converter::ArkValue<Ark_String>("800", &fixCtx), "800" },
    { "\"900\"", Converter::ArkValue<Ark_String>("900", &fixCtx), "900" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureFontWeightStringsInvalidValues = {
    { "\"0\"", Converter::ArkValue<Ark_String>("0", &fixCtx) },
    { "\"1000\"", Converter::ArkValue<Ark_String>("1000", &fixCtx) },
    { "\"-100\"", Converter::ArkValue<Ark_String>("-100", &fixCtx) },
};

// Fixture 'FontWeightResStrings' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureFontWeightResStringsValidValues = {
    { "ResId:FONT_WEIGHT_RES_STRINGS_0_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_0_ID, ResourceType::STRING), "100" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_0_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_0_STR, ResourceType::STRING),
        "100" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_1_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_1_ID, ResourceType::STRING), "200" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_1_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_1_STR, ResourceType::STRING),
        "200" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_2_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_2_ID, ResourceType::STRING), "300" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_2_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_2_STR, ResourceType::STRING),
        "300" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_3_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_3_ID, ResourceType::STRING), "400" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_3_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_3_STR, ResourceType::STRING),
        "400" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_4_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_4_ID, ResourceType::STRING), "500" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_4_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_4_STR, ResourceType::STRING),
        "500" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_5_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_5_ID, ResourceType::STRING), "600" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_5_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_5_STR, ResourceType::STRING),
        "600" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_6_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_6_ID, ResourceType::STRING), "700" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_6_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_6_STR, ResourceType::STRING),
        "700" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_7_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_7_ID, ResourceType::STRING), "800" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_7_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_7_STR, ResourceType::STRING),
        "800" },
    { "ResId:FONT_WEIGHT_RES_STRINGS_8_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_8_ID, ResourceType::STRING), "900" },
    { "ResName:FONT_WEIGHT_RES_STRINGS_8_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_8_STR, ResourceType::STRING),
        "900" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureFontWeightResStringsInvalidValues = {
    { "ResId:FONT_WEIGHT_RES_STRINGS_9_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_9_ID, ResourceType::STRING) },
    { "ResName:FONT_WEIGHT_RES_STRINGS_9_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_9_STR, ResourceType::STRING) },
    { "ResId:FONT_WEIGHT_RES_STRINGS_10_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_10_ID, ResourceType::STRING) },
    { "ResName:FONT_WEIGHT_RES_STRINGS_10_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_10_STR, ResourceType::STRING) },
    { "ResId:FONT_WEIGHT_RES_STRINGS_11_ID", CreateResource(FONT_WEIGHT_RES_STRINGS_11_ID, ResourceType::STRING) },
    { "ResName:FONT_WEIGHT_RES_STRINGS_11_STR", CreateResource(FONT_WEIGHT_RES_STRINGS_11_STR, ResourceType::STRING) },
};

// Fixture 'ScrollableFrictionNum' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureScrollableFrictionNumValidValues = {
    { "0.125", Converter::ArkValue<Ark_Number>(0.125, &fixCtx), "0.125" },
    { "0.75", Converter::ArkValue<Ark_Number>(0.75, &fixCtx), "0.75" },
    { "2", Converter::ArkValue<Ark_Number>(2, &fixCtx), "2" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureScrollableFrictionNumInvalidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx) },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx) },
};

// Fixture 'ScrollableFrictionRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureScrollableFrictionResValidValues = {
    { "ResId:SCROLLABLE_FRICTION_RES_0_ID", CreateResource(SCROLLABLE_FRICTION_RES_0_ID, ResourceType::FLOAT),
        "0.125" },
    { "ResName:SCROLLABLE_FRICTION_RES_0_STR", CreateResource(SCROLLABLE_FRICTION_RES_0_STR, ResourceType::FLOAT),
        "0.125" },
    { "ResId:SCROLLABLE_FRICTION_RES_1_ID", CreateResource(SCROLLABLE_FRICTION_RES_1_ID, ResourceType::FLOAT),
        "0.875" },
    { "ResName:SCROLLABLE_FRICTION_RES_1_STR", CreateResource(SCROLLABLE_FRICTION_RES_1_STR, ResourceType::FLOAT),
        "0.875" },
    { "ResId:SCROLLABLE_FRICTION_RES_2_ID", CreateResource(SCROLLABLE_FRICTION_RES_2_ID, ResourceType::FLOAT), "2" },
    { "ResName:SCROLLABLE_FRICTION_RES_2_STR", CreateResource(SCROLLABLE_FRICTION_RES_2_STR, ResourceType::FLOAT),
        "2" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureScrollableFrictionResInvalidValues = {
    { "ResId:SCROLLABLE_FRICTION_RES_3_ID", CreateResource(SCROLLABLE_FRICTION_RES_3_ID, ResourceType::FLOAT) },
    { "ResName:SCROLLABLE_FRICTION_RES_3_STR", CreateResource(SCROLLABLE_FRICTION_RES_3_STR, ResourceType::FLOAT) },
    { "ResId:SCROLLABLE_FRICTION_RES_4_ID", CreateResource(SCROLLABLE_FRICTION_RES_4_ID, ResourceType::FLOAT) },
    { "ResName:SCROLLABLE_FRICTION_RES_4_STR", CreateResource(SCROLLABLE_FRICTION_RES_4_STR, ResourceType::FLOAT) },
};

// Fixture 'Opacity' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureOpacityValidValues = {
    { "0.1f", Converter::ArkValue<Ark_Number>(0.1f, &fixCtx), "0.100000" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0.000000" },
    { "0.9f", Converter::ArkValue<Ark_Number>(0.9f, &fixCtx), "0.900000" },
    { "1", Converter::ArkValue<Ark_Number>(1, &fixCtx), "1.000000" },
    { "-0.1f", Converter::ArkValue<Ark_Number>(-0.1f, &fixCtx), "0.000000" },
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "1.000000" },
    { "-100", Converter::ArkValue<Ark_Number>(-100, &fixCtx), "0.000000" },
    { "1.1f", Converter::ArkValue<Ark_Number>(1.1f, &fixCtx), "1.000000" },
};

// Fixture 'OpacityResource' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureOpacityResourceValidValues = {
    { "ResId:OPACITY_RESOURCE_0_ID", CreateResource(OPACITY_RESOURCE_0_ID, ResourceType::FLOAT), "0.100000" },
    { "ResName:OPACITY_RESOURCE_0_STR", CreateResource(OPACITY_RESOURCE_0_STR, ResourceType::FLOAT), "0.100000" },
    { "ResId:OPACITY_RESOURCE_1_ID", CreateResource(OPACITY_RESOURCE_1_ID, ResourceType::FLOAT), "0.000000" },
    { "ResName:OPACITY_RESOURCE_1_STR", CreateResource(OPACITY_RESOURCE_1_STR, ResourceType::FLOAT), "0.000000" },
    { "ResId:OPACITY_RESOURCE_2_ID", CreateResource(OPACITY_RESOURCE_2_ID, ResourceType::FLOAT), "0.900000" },
    { "ResName:OPACITY_RESOURCE_2_STR", CreateResource(OPACITY_RESOURCE_2_STR, ResourceType::FLOAT), "0.900000" },
    { "ResId:OPACITY_RESOURCE_3_ID", CreateResource(OPACITY_RESOURCE_3_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:OPACITY_RESOURCE_3_STR", CreateResource(OPACITY_RESOURCE_3_STR, ResourceType::FLOAT), "1.000000" },
    { "ResId:OPACITY_RESOURCE_4_ID", CreateResource(OPACITY_RESOURCE_4_ID, ResourceType::FLOAT), "0.000000" },
    { "ResName:OPACITY_RESOURCE_4_STR", CreateResource(OPACITY_RESOURCE_4_STR, ResourceType::FLOAT), "0.000000" },
    { "ResId:OPACITY_RESOURCE_5_ID", CreateResource(OPACITY_RESOURCE_5_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:OPACITY_RESOURCE_5_STR", CreateResource(OPACITY_RESOURCE_5_STR, ResourceType::FLOAT), "1.000000" },
    { "ResId:OPACITY_RESOURCE_6_ID", CreateResource(OPACITY_RESOURCE_6_ID, ResourceType::FLOAT), "0.000000" },
    { "ResName:OPACITY_RESOURCE_6_STR", CreateResource(OPACITY_RESOURCE_6_STR, ResourceType::FLOAT), "0.000000" },
    { "ResId:OPACITY_RESOURCE_7_ID", CreateResource(OPACITY_RESOURCE_7_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:OPACITY_RESOURCE_7_STR", CreateResource(OPACITY_RESOURCE_7_STR, ResourceType::FLOAT), "1.000000" },
};

// Fixture 'FixtureNavBarWidthRange' for type 'Ark_Tuple_Dimension_Dimension'
std::vector<std::tuple<std::string, Ark_Tuple_Dimension_Dimension, std::string>>
    testFixtureFixtureNavBarWidthRangeValidValues = {
        { "std::pair<const Dimension, const Dimension>{0.1_fp, 10.0_vp}",
            Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
                std::pair<const Dimension, const Dimension> { 0.1_fp, 10.0_vp }, &fixCtx),
            "0.10fp, 10.00vp" },
        { "std::pair<const Dimension, const Dimension>{0.1_px, 112.0_vp}",
            Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
                std::pair<const Dimension, const Dimension> { 0.1_px, 112.0_vp }, &fixCtx),
            "0.10px, 112.00vp" },
        { "std::pair<const Dimension, const Dimension>{5, 6}",
            Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
                std::pair<const Dimension, const Dimension> { 5, 6 }, &fixCtx),
            "5.00px, 6.00px" },
        { "std::pair<const Dimension, const Dimension>{0.5_pct, 100}",
            Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
                std::pair<const Dimension, const Dimension> { 0.5_pct, 100 }, &fixCtx),
            "50.00%, 100.00px" },
    };

std::vector<std::tuple<std::string, Ark_Tuple_Dimension_Dimension>> testFixtureFixtureNavBarWidthRangeInvalidValues = {
    { "std::pair<const Dimension, const Dimension>{0, 0}",
        Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
            std::pair<const Dimension, const Dimension> { 0, 0 }, &fixCtx) },
    { "std::pair<const Dimension, const Dimension>{-0.1f, INT_MIN}",
        Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
            std::pair<const Dimension, const Dimension> { -0.1f, INT_MIN }, &fixCtx) },
    { "std::pair<const Dimension, const Dimension>{-123._px, 0._fp}",
        Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
            std::pair<const Dimension, const Dimension> { -123._px, 0._fp }, &fixCtx) },
    { "std::pair<const Dimension, const Dimension>{0, -0.15_pct}",
        Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
            std::pair<const Dimension, const Dimension> { 0, -0.15_pct }, &fixCtx) },
    { "std::pair<const Dimension, const Dimension>{0._px, -432.01_vp}",
        Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(
            std::pair<const Dimension, const Dimension> { 0._px, -432.01_vp }, &fixCtx) },
};

// Fixture 'TextInputBarState' for type 'Ark_BarState'
std::vector<std::tuple<std::string, Ark_BarState, std::string>> testFixtureTextInputBarStateValidValues = {
    { "ARK_BAR_STATE_OFF", Converter::ArkValue<Ark_BarState>(ARK_BAR_STATE_OFF, &fixCtx), "BarState.OFF" },
    { "ARK_BAR_STATE_AUTO", Converter::ArkValue<Ark_BarState>(ARK_BAR_STATE_AUTO, &fixCtx), "BarState.AUTO" },
    { "ARK_BAR_STATE_ON", Converter::ArkValue<Ark_BarState>(ARK_BAR_STATE_ON, &fixCtx), "BarState.ON" },
};

std::vector<std::tuple<std::string, Ark_BarState>> testFixtureTextInputBarStateInvalidValues = {
    { "static_cast<Ark_BarState>(-1)", Converter::ArkValue<Ark_BarState>(static_cast<Ark_BarState>(-1), &fixCtx) },
    { "static_cast<Ark_BarState>(INT_MAX)",
        Converter::ArkValue<Ark_BarState>(static_cast<Ark_BarState>(INT_MAX), &fixCtx) },
};

// Fixture 'TextInputBreakWord' for type 'Ark_WordBreak'
std::vector<std::tuple<std::string, Ark_WordBreak, std::string>> testFixtureTextInputBreakWordValidValues = {
    { "ARK_WORD_BREAK_NORMAL", Converter::ArkValue<Ark_WordBreak>(ARK_WORD_BREAK_NORMAL, &fixCtx), "normal" },
    { "ARK_WORD_BREAK_BREAK_ALL", Converter::ArkValue<Ark_WordBreak>(ARK_WORD_BREAK_BREAK_ALL, &fixCtx), "break-all" },
    { "ARK_WORD_BREAK_BREAK_WORD", Converter::ArkValue<Ark_WordBreak>(ARK_WORD_BREAK_BREAK_WORD, &fixCtx),
        "break-word" },
};

std::vector<std::tuple<std::string, Ark_WordBreak>> testFixtureTextInputBreakWordInvalidValues = {
    { "static_cast<Ark_WordBreak>(-1)", Converter::ArkValue<Ark_WordBreak>(static_cast<Ark_WordBreak>(-1), &fixCtx) },
    { "static_cast<Ark_WordBreak>(INT_MAX)",
        Converter::ArkValue<Ark_WordBreak>(static_cast<Ark_WordBreak>(INT_MAX), &fixCtx) },
};

// Fixture 'TextSelectableMode' for type 'Ark_TextSelectableMode'
std::vector<std::tuple<std::string, Ark_TextSelectableMode, std::string>> testFixtureTextSelectableModeValidValues = {
    { "ARK_TEXT_SELECTABLE_MODE_SELECTABLE_UNFOCUSABLE",
        Converter::ArkValue<Ark_TextSelectableMode>(ARK_TEXT_SELECTABLE_MODE_SELECTABLE_UNFOCUSABLE, &fixCtx),
        "selectable-unfocusable" },
    { "ARK_TEXT_SELECTABLE_MODE_SELECTABLE_FOCUSABLE",
        Converter::ArkValue<Ark_TextSelectableMode>(ARK_TEXT_SELECTABLE_MODE_SELECTABLE_FOCUSABLE, &fixCtx),
        "selectable-focusable" },
    { "ARK_TEXT_SELECTABLE_MODE_UNSELECTABLE",
        Converter::ArkValue<Ark_TextSelectableMode>(ARK_TEXT_SELECTABLE_MODE_UNSELECTABLE, &fixCtx), "unselectable" },
};

std::vector<std::tuple<std::string, Ark_TextSelectableMode>> testFixtureTextSelectableModeInvalidValues = {
    { "static_cast<Ark_TextSelectableMode>(-1)",
        Converter::ArkValue<Ark_TextSelectableMode>(static_cast<Ark_TextSelectableMode>(-1), &fixCtx) },
    { "static_cast<Ark_TextSelectableMode>(INT_MAX)",
        Converter::ArkValue<Ark_TextSelectableMode>(static_cast<Ark_TextSelectableMode>(INT_MAX), &fixCtx) },
};

// Fixture 'FrictionResource' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureFrictionResourceValidValues = {
    { "ResId:FRICTION_RESOURCE_0_ID", CreateResource(FRICTION_RESOURCE_0_ID, ResourceType::FLOAT), "0.100000" },
    { "ResName:FRICTION_RESOURCE_0_STR", CreateResource(FRICTION_RESOURCE_0_STR, ResourceType::FLOAT), "0.100000" },
    { "ResId:FRICTION_RESOURCE_1_ID", CreateResource(FRICTION_RESOURCE_1_ID, ResourceType::FLOAT), "0.000000" },
    { "ResName:FRICTION_RESOURCE_1_STR", CreateResource(FRICTION_RESOURCE_1_STR, ResourceType::FLOAT), "0.000000" },
    { "ResId:FRICTION_RESOURCE_2_ID", CreateResource(FRICTION_RESOURCE_2_ID, ResourceType::FLOAT), "0.900000" },
    { "ResName:FRICTION_RESOURCE_2_STR", CreateResource(FRICTION_RESOURCE_2_STR, ResourceType::FLOAT), "0.900000" },
    { "ResId:FRICTION_RESOURCE_3_ID", CreateResource(FRICTION_RESOURCE_3_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:FRICTION_RESOURCE_3_STR", CreateResource(FRICTION_RESOURCE_3_STR, ResourceType::FLOAT), "1.000000" },
    { "ResId:FRICTION_RESOURCE_4_ID", CreateResource(FRICTION_RESOURCE_4_ID, ResourceType::FLOAT), "0.000000" },
    { "ResName:FRICTION_RESOURCE_4_STR", CreateResource(FRICTION_RESOURCE_4_STR, ResourceType::FLOAT), "0.000000" },
    { "ResId:FRICTION_RESOURCE_5_ID", CreateResource(FRICTION_RESOURCE_5_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:FRICTION_RESOURCE_5_STR", CreateResource(FRICTION_RESOURCE_5_STR, ResourceType::FLOAT), "1.000000" },
    { "ResId:FRICTION_RESOURCE_6_ID", CreateResource(FRICTION_RESOURCE_6_ID, ResourceType::FLOAT), "0.000000" },
    { "ResName:FRICTION_RESOURCE_6_STR", CreateResource(FRICTION_RESOURCE_6_STR, ResourceType::FLOAT), "0.000000" },
    { "ResId:FRICTION_RESOURCE_7_ID", CreateResource(FRICTION_RESOURCE_7_ID, ResourceType::FLOAT), "1.000000" },
    { "ResName:FRICTION_RESOURCE_7_STR", CreateResource(FRICTION_RESOURCE_7_STR, ResourceType::FLOAT), "1.000000" },
};

// Fixture 'TimeFormat' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureTimeFormatValidValues = {
    { "\"aa hh:mm:ss\"", Converter::ArkValue<Ark_String>("aa hh:mm:ss", &fixCtx), "aa hh:mm:ss" },
    { "\"EEEE, M, d, yyyy\"", Converter::ArkValue<Ark_String>("EEEE, M, d, yyyy", &fixCtx), "EEEE, M, d, yyyy" },
    { "\"MMM d, yyyy\"", Converter::ArkValue<Ark_String>("MMM d, yyyy", &fixCtx), "MMM d, yyyy" },
    { "\"EEEE, M, d\"", Converter::ArkValue<Ark_String>("EEEE, M, d", &fixCtx), "EEEE, M, d" },
    { "\"MMM dd\"", Converter::ArkValue<Ark_String>("MMM dd", &fixCtx), "MMM dd" },
    { "\"MM/dd/yyyy\"", Converter::ArkValue<Ark_String>("MM/dd/yyyy", &fixCtx), "MM/dd/yyyy" },
    { "\"EEEE MM dd\"", Converter::ArkValue<Ark_String>("EEEE MM dd", &fixCtx), "EEEE MM dd" },
    { "\"yyyy\"", Converter::ArkValue<Ark_String>("yyyy", &fixCtx), "yyyy" },
    { "\"yy\"", Converter::ArkValue<Ark_String>("yy", &fixCtx), "yy" },
    { "\"MM\"", Converter::ArkValue<Ark_String>("MM", &fixCtx), "MM" },
    { "\"M\"", Converter::ArkValue<Ark_String>("M", &fixCtx), "M" },
    { "\"dd\"", Converter::ArkValue<Ark_String>("dd", &fixCtx), "dd" },
    { "\"d\"", Converter::ArkValue<Ark_String>("d", &fixCtx), "d" },
    { "\"EEEE\"", Converter::ArkValue<Ark_String>("EEEE", &fixCtx), "EEEE" },
    { "\"E, EE, EEE\"", Converter::ArkValue<Ark_String>("E, EE, EEE", &fixCtx), "E, EE, EEE" },
    { "\"MMM d, yyyy\"", Converter::ArkValue<Ark_String>("MMM d, yyyy", &fixCtx), "MMM d, yyyy" },
    { "\"yyyy/M/d\"", Converter::ArkValue<Ark_String>("yyyy/M/d", &fixCtx), "yyyy/M/d" },
    { "\"yyyy-M-d\"", Converter::ArkValue<Ark_String>("yyyy-M-d", &fixCtx), "yyyy-M-d" },
    { "\"yyyy.M.d\"", Converter::ArkValue<Ark_String>("yyyy.M.d", &fixCtx), "yyyy.M.d" },
    { "\"HH:mm:ss\"", Converter::ArkValue<Ark_String>("HH:mm:ss", &fixCtx), "HH:mm:ss" },
    { "\"aa hh:mm:ss\"", Converter::ArkValue<Ark_String>("aa hh:mm:ss", &fixCtx), "aa hh:mm:ss" },
    { "\"hh:mm:ss\"", Converter::ArkValue<Ark_String>("hh:mm:ss", &fixCtx), "hh:mm:ss" },
    { "\"HH:mm\"", Converter::ArkValue<Ark_String>("HH:mm", &fixCtx), "HH:mm" },
    { "\"aa hh:mm\"", Converter::ArkValue<Ark_String>("aa hh:mm", &fixCtx), "aa hh:mm" },
    { "\"hh:mm\"", Converter::ArkValue<Ark_String>("hh:mm", &fixCtx), "hh:mm" },
    { "\"mm:ss\"", Converter::ArkValue<Ark_String>("mm:ss", &fixCtx), "mm:ss" },
    { "\"mm:ss.SS\"", Converter::ArkValue<Ark_String>("mm:ss.SS", &fixCtx), "mm:ss.SS" },
    { "\"mm:ss.SSS\"", Converter::ArkValue<Ark_String>("mm:ss.SSS", &fixCtx), "mm:ss.SSS" },
    { "\"hh:mm:ss aa\"", Converter::ArkValue<Ark_String>("hh:mm:ss aa", &fixCtx), "hh:mm:ss aa" },
    { "\"HH\"", Converter::ArkValue<Ark_String>("HH", &fixCtx), "HH" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureTimeFormatInvalidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
};

// Fixture 'TimeFormatRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureTimeFormatResValidValues = {
    { "ResId:TIME_FORMAT_RES_0_ID", CreateResource(TIME_FORMAT_RES_0_ID, ResourceType::STRING), "aa hh:mm:ss" },
    { "ResName:TIME_FORMAT_RES_0_STR", CreateResource(TIME_FORMAT_RES_0_STR, ResourceType::STRING), "aa hh:mm:ss" },
    { "ResId:TIME_FORMAT_RES_1_ID", CreateResource(TIME_FORMAT_RES_1_ID, ResourceType::STRING), "EEEE, M, d, yyyy" },
    { "ResName:TIME_FORMAT_RES_1_STR", CreateResource(TIME_FORMAT_RES_1_STR, ResourceType::STRING),
        "EEEE, M, d, yyyy" },
    { "ResId:TIME_FORMAT_RES_2_ID", CreateResource(TIME_FORMAT_RES_2_ID, ResourceType::STRING), "MMM d, yyyy" },
    { "ResName:TIME_FORMAT_RES_2_STR", CreateResource(TIME_FORMAT_RES_2_STR, ResourceType::STRING), "MMM d, yyyy" },
    { "ResId:TIME_FORMAT_RES_3_ID", CreateResource(TIME_FORMAT_RES_3_ID, ResourceType::STRING), "EEEE, M, d" },
    { "ResName:TIME_FORMAT_RES_3_STR", CreateResource(TIME_FORMAT_RES_3_STR, ResourceType::STRING), "EEEE, M, d" },
    { "ResId:TIME_FORMAT_RES_4_ID", CreateResource(TIME_FORMAT_RES_4_ID, ResourceType::STRING), "MMM dd" },
    { "ResName:TIME_FORMAT_RES_4_STR", CreateResource(TIME_FORMAT_RES_4_STR, ResourceType::STRING), "MMM dd" },
    { "ResId:TIME_FORMAT_RES_5_ID", CreateResource(TIME_FORMAT_RES_5_ID, ResourceType::STRING), "MM/dd/yyyy" },
    { "ResName:TIME_FORMAT_RES_5_STR", CreateResource(TIME_FORMAT_RES_5_STR, ResourceType::STRING), "MM/dd/yyyy" },
    { "ResId:TIME_FORMAT_RES_6_ID", CreateResource(TIME_FORMAT_RES_6_ID, ResourceType::STRING), "EEEE MM dd" },
    { "ResName:TIME_FORMAT_RES_6_STR", CreateResource(TIME_FORMAT_RES_6_STR, ResourceType::STRING), "EEEE MM dd" },
    { "ResId:TIME_FORMAT_RES_7_ID", CreateResource(TIME_FORMAT_RES_7_ID, ResourceType::STRING), "yyyy" },
    { "ResName:TIME_FORMAT_RES_7_STR", CreateResource(TIME_FORMAT_RES_7_STR, ResourceType::STRING), "yyyy" },
    { "ResId:TIME_FORMAT_RES_8_ID", CreateResource(TIME_FORMAT_RES_8_ID, ResourceType::STRING), "yy" },
    { "ResName:TIME_FORMAT_RES_8_STR", CreateResource(TIME_FORMAT_RES_8_STR, ResourceType::STRING), "yy" },
    { "ResId:TIME_FORMAT_RES_9_ID", CreateResource(TIME_FORMAT_RES_9_ID, ResourceType::STRING), "MM" },
    { "ResName:TIME_FORMAT_RES_9_STR", CreateResource(TIME_FORMAT_RES_9_STR, ResourceType::STRING), "MM" },
    { "ResId:TIME_FORMAT_RES_10_ID", CreateResource(TIME_FORMAT_RES_10_ID, ResourceType::STRING), "M" },
    { "ResName:TIME_FORMAT_RES_10_STR", CreateResource(TIME_FORMAT_RES_10_STR, ResourceType::STRING), "M" },
    { "ResId:TIME_FORMAT_RES_11_ID", CreateResource(TIME_FORMAT_RES_11_ID, ResourceType::STRING), "dd" },
    { "ResName:TIME_FORMAT_RES_11_STR", CreateResource(TIME_FORMAT_RES_11_STR, ResourceType::STRING), "dd" },
    { "ResId:TIME_FORMAT_RES_12_ID", CreateResource(TIME_FORMAT_RES_12_ID, ResourceType::STRING), "d" },
    { "ResName:TIME_FORMAT_RES_12_STR", CreateResource(TIME_FORMAT_RES_12_STR, ResourceType::STRING), "d" },
    { "ResId:TIME_FORMAT_RES_13_ID", CreateResource(TIME_FORMAT_RES_13_ID, ResourceType::STRING), "EEEE" },
    { "ResName:TIME_FORMAT_RES_13_STR", CreateResource(TIME_FORMAT_RES_13_STR, ResourceType::STRING), "EEEE" },
    { "ResId:TIME_FORMAT_RES_14_ID", CreateResource(TIME_FORMAT_RES_14_ID, ResourceType::STRING), "E, EE, EEE" },
    { "ResName:TIME_FORMAT_RES_14_STR", CreateResource(TIME_FORMAT_RES_14_STR, ResourceType::STRING), "E, EE, EEE" },
    { "ResId:TIME_FORMAT_RES_15_ID", CreateResource(TIME_FORMAT_RES_15_ID, ResourceType::STRING), "MMM d, yyyy" },
    { "ResName:TIME_FORMAT_RES_15_STR", CreateResource(TIME_FORMAT_RES_15_STR, ResourceType::STRING), "MMM d, yyyy" },
    { "ResId:TIME_FORMAT_RES_16_ID", CreateResource(TIME_FORMAT_RES_16_ID, ResourceType::STRING), "yyyy/M/d" },
    { "ResName:TIME_FORMAT_RES_16_STR", CreateResource(TIME_FORMAT_RES_16_STR, ResourceType::STRING), "yyyy/M/d" },
    { "ResId:TIME_FORMAT_RES_17_ID", CreateResource(TIME_FORMAT_RES_17_ID, ResourceType::STRING), "yyyy-M-d" },
    { "ResName:TIME_FORMAT_RES_17_STR", CreateResource(TIME_FORMAT_RES_17_STR, ResourceType::STRING), "yyyy-M-d" },
    { "ResId:TIME_FORMAT_RES_18_ID", CreateResource(TIME_FORMAT_RES_18_ID, ResourceType::STRING), "yyyy.M.d" },
    { "ResName:TIME_FORMAT_RES_18_STR", CreateResource(TIME_FORMAT_RES_18_STR, ResourceType::STRING), "yyyy.M.d" },
    { "ResId:TIME_FORMAT_RES_19_ID", CreateResource(TIME_FORMAT_RES_19_ID, ResourceType::STRING), "HH:mm:ss" },
    { "ResName:TIME_FORMAT_RES_19_STR", CreateResource(TIME_FORMAT_RES_19_STR, ResourceType::STRING), "HH:mm:ss" },
    { "ResId:TIME_FORMAT_RES_20_ID", CreateResource(TIME_FORMAT_RES_20_ID, ResourceType::STRING), "aa hh:mm:ss" },
    { "ResName:TIME_FORMAT_RES_20_STR", CreateResource(TIME_FORMAT_RES_20_STR, ResourceType::STRING), "aa hh:mm:ss" },
    { "ResId:TIME_FORMAT_RES_21_ID", CreateResource(TIME_FORMAT_RES_21_ID, ResourceType::STRING), "hh:mm:ss" },
    { "ResName:TIME_FORMAT_RES_21_STR", CreateResource(TIME_FORMAT_RES_21_STR, ResourceType::STRING), "hh:mm:ss" },
    { "ResId:TIME_FORMAT_RES_22_ID", CreateResource(TIME_FORMAT_RES_22_ID, ResourceType::STRING), "HH:mm" },
    { "ResName:TIME_FORMAT_RES_22_STR", CreateResource(TIME_FORMAT_RES_22_STR, ResourceType::STRING), "HH:mm" },
    { "ResId:TIME_FORMAT_RES_23_ID", CreateResource(TIME_FORMAT_RES_23_ID, ResourceType::STRING), "aa hh:mm" },
    { "ResName:TIME_FORMAT_RES_23_STR", CreateResource(TIME_FORMAT_RES_23_STR, ResourceType::STRING), "aa hh:mm" },
    { "ResId:TIME_FORMAT_RES_24_ID", CreateResource(TIME_FORMAT_RES_24_ID, ResourceType::STRING), "hh:mm" },
    { "ResName:TIME_FORMAT_RES_24_STR", CreateResource(TIME_FORMAT_RES_24_STR, ResourceType::STRING), "hh:mm" },
    { "ResId:TIME_FORMAT_RES_25_ID", CreateResource(TIME_FORMAT_RES_25_ID, ResourceType::STRING), "mm:ss" },
    { "ResName:TIME_FORMAT_RES_25_STR", CreateResource(TIME_FORMAT_RES_25_STR, ResourceType::STRING), "mm:ss" },
    { "ResId:TIME_FORMAT_RES_26_ID", CreateResource(TIME_FORMAT_RES_26_ID, ResourceType::STRING), "mm:ss.SS" },
    { "ResName:TIME_FORMAT_RES_26_STR", CreateResource(TIME_FORMAT_RES_26_STR, ResourceType::STRING), "mm:ss.SS" },
    { "ResId:TIME_FORMAT_RES_27_ID", CreateResource(TIME_FORMAT_RES_27_ID, ResourceType::STRING), "mm:ss.SSS" },
    { "ResName:TIME_FORMAT_RES_27_STR", CreateResource(TIME_FORMAT_RES_27_STR, ResourceType::STRING), "mm:ss.SSS" },
    { "ResId:TIME_FORMAT_RES_28_ID", CreateResource(TIME_FORMAT_RES_28_ID, ResourceType::STRING), "hh:mm:ss aa" },
    { "ResName:TIME_FORMAT_RES_28_STR", CreateResource(TIME_FORMAT_RES_28_STR, ResourceType::STRING), "hh:mm:ss aa" },
    { "ResId:TIME_FORMAT_RES_29_ID", CreateResource(TIME_FORMAT_RES_29_ID, ResourceType::STRING), "HH" },
    { "ResName:TIME_FORMAT_RES_29_STR", CreateResource(TIME_FORMAT_RES_29_STR, ResourceType::STRING), "HH" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureTimeFormatResInvalidValues = {
    { "ResId:TIME_FORMAT_RES_30_ID", CreateResource(TIME_FORMAT_RES_30_ID, ResourceType::STRING) },
    { "ResName:TIME_FORMAT_RES_30_STR", CreateResource(TIME_FORMAT_RES_30_STR, ResourceType::STRING) },
};

// Fixture 'FontFeatureNum' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontFeatureNumValidValues = {
    { "\"'ss01' on\"", Converter::ArkValue<Ark_String>("'ss01' on", &fixCtx), "'ss01' 1" },
    { "\"'ss01' off\"", Converter::ArkValue<Ark_String>("'ss01' off", &fixCtx), "'ss01' 0" },
    { "\"'ss01' 1\"", Converter::ArkValue<Ark_String>("'ss01' 1", &fixCtx), "'ss01' 1" },
    { "\"'ss01' 0\"", Converter::ArkValue<Ark_String>("'ss01' 0", &fixCtx), "'ss01' 0" },
    { "\"'ss01' on, 'ss02' on\"", Converter::ArkValue<Ark_String>("'ss01' on, 'ss02' on", &fixCtx),
        "'ss01' 1,'ss02' 1" },
    { "\"'ss01' on, 'ss02' off\"", Converter::ArkValue<Ark_String>("'ss01' on, 'ss02' off", &fixCtx),
        "'ss01' 1,'ss02' 0" },
    { "\"'ss01' on, ss02 off\"", Converter::ArkValue<Ark_String>("'ss01' on, ss02 off", &fixCtx), "'ss01' 1" },
    { "\"'ss01' on\"", Converter::ArkValue<Ark_String>("'ss01' on", &fixCtx), "'ss01' 1" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureFontFeatureNumInvalidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
    { "\"invalid\"", Converter::ArkValue<Ark_String>("invalid", &fixCtx) },
    { "\"ss01 1\"", Converter::ArkValue<Ark_String>("ss01 1", &fixCtx) },
    { "\"ss01 on, ss02 off\"", Converter::ArkValue<Ark_String>("ss01 on, ss02 off", &fixCtx) },
    { "\"'incorrect' on\"", Converter::ArkValue<Ark_String>("'incorrect' on", &fixCtx) },
};

// Fixture 'FontFeatureStr' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontFeatureStrValidValues = {
    { "\"'ss01' on\"", Converter::ArkValue<Ark_String>("'ss01' on", &fixCtx), "'ss01' on" },
    { "\"'ss01' off\"", Converter::ArkValue<Ark_String>("'ss01' off", &fixCtx), "'ss01' off" },
    { "\"'ss01' 1\"", Converter::ArkValue<Ark_String>("'ss01' 1", &fixCtx), "'ss01' on" },
    { "\"'ss01' 0\"", Converter::ArkValue<Ark_String>("'ss01' 0", &fixCtx), "'ss01' off" },
    { "\"'ss01' on, 'ss02' on\"", Converter::ArkValue<Ark_String>("'ss01' on, 'ss02' on", &fixCtx),
        "'ss01' on,'ss02' on" },
    { "\"'ss01' on, 'ss02' off\"", Converter::ArkValue<Ark_String>("'ss01' on, 'ss02' off", &fixCtx),
        "'ss01' on,'ss02' off" },
    { "\"'ss01' on, ss02 off\"", Converter::ArkValue<Ark_String>("'ss01' on, ss02 off", &fixCtx), "'ss01' on" },
    { "\"'ss01' on\"", Converter::ArkValue<Ark_String>("'ss01' on", &fixCtx), "'ss01' on" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureFontFeatureStrInvalidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx) },
    { "\"invalid\"", Converter::ArkValue<Ark_String>("invalid", &fixCtx) },
    { "\"ss01 1\"", Converter::ArkValue<Ark_String>("ss01 1", &fixCtx) },
    { "\"ss01 on, ss02 off\"", Converter::ArkValue<Ark_String>("ss01 on, ss02 off", &fixCtx) },
    { "\"'incorrect' on\"", Converter::ArkValue<Ark_String>("'incorrect' on", &fixCtx) },
};

// Fixture 'TextInputCaretPosition' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureTextInputCaretPositionValidValues = {
    { "\"T\"", Converter::ArkValue<Ark_String>("T", &fixCtx), "Just_only_for_test_data_generation" },
    { "\"Text\"", Converter::ArkValue<Ark_String>("Text", &fixCtx), "Just_only_for_test_data_generation" },
    { "\"Simple Text\"", Converter::ArkValue<Ark_String>("Simple Text", &fixCtx),
        "Just_only_for_test_data_generation" },
    { "\"Very Long\nText with new lines\n    bla-bla-bla\"",
        Converter::ArkValue<Ark_String>("Very Long\nText with new lines\n    bla-bla-bla", &fixCtx),
        "Just_only_for_test_data_generation" },
    { "\"\"", Converter::ArkValue<Ark_String>("", &fixCtx), "Just_only_for_test_data_generation" },
    { "\"        \"", Converter::ArkValue<Ark_String>("        ", &fixCtx), "Just_only_for_test_data_generation" },
};

// Fixture 'ShadowRadiusNumber' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureShadowRadiusNumberValidValues = {
    { "123", Converter::ArkValue<Ark_Number>(123, &fixCtx), "123.000000" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0.000000" },
    { "1.23", Converter::ArkValue<Ark_Number>(1.23, &fixCtx), "1.230000" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureShadowRadiusNumberInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Number>(-1, &fixCtx) },
};

// Fixture 'ShadowRadiusRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureShadowRadiusResValidValues = {
    { "ResId:SHADOW_RADIUS_RES_0_ID", CreateResource(SHADOW_RADIUS_RES_0_ID, ResourceType::FLOAT), "0.100000" },
    { "ResName:SHADOW_RADIUS_RES_0_STR", CreateResource(SHADOW_RADIUS_RES_0_STR, ResourceType::FLOAT), "0.100000" },
    { "ResId:SHADOW_RADIUS_RES_1_ID", CreateResource(SHADOW_RADIUS_RES_1_ID, ResourceType::FLOAT), "3.000000" },
    { "ResName:SHADOW_RADIUS_RES_1_STR", CreateResource(SHADOW_RADIUS_RES_1_STR, ResourceType::FLOAT), "3.000000" },
    { "ResId:SHADOW_RADIUS_RES_2_ID", CreateResource(SHADOW_RADIUS_RES_2_ID, ResourceType::FLOAT), "0.900000" },
    { "ResName:SHADOW_RADIUS_RES_2_STR", CreateResource(SHADOW_RADIUS_RES_2_STR, ResourceType::FLOAT), "0.900000" },
    { "ResId:SHADOW_RADIUS_RES_3_ID", CreateResource(SHADOW_RADIUS_RES_3_ID, ResourceType::FLOAT), "100.000000" },
    { "ResName:SHADOW_RADIUS_RES_3_STR", CreateResource(SHADOW_RADIUS_RES_3_STR, ResourceType::FLOAT), "100.000000" },
    { "ResId:SHADOW_RADIUS_RES_4_ID", CreateResource(SHADOW_RADIUS_RES_4_ID, ResourceType::FLOAT), "1.100000" },
    { "ResName:SHADOW_RADIUS_RES_4_STR", CreateResource(SHADOW_RADIUS_RES_4_STR, ResourceType::FLOAT), "1.100000" },
};

std::vector<std::tuple<std::string, Ark_Resource>> testFixtureShadowRadiusResInvalidValues = {
    { "ResId:SHADOW_RADIUS_RES_5_ID", CreateResource(SHADOW_RADIUS_RES_5_ID, ResourceType::FLOAT) },
    { "ResName:SHADOW_RADIUS_RES_5_STR", CreateResource(SHADOW_RADIUS_RES_5_STR, ResourceType::FLOAT) },
};

// Fixture 'ShadowOffsetNumber' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureShadowOffsetNumberValidValues = {
    { "123", Converter::ArkValue<Ark_Number>(123, &fixCtx), "123.000000" },
    { "0", Converter::ArkValue<Ark_Number>(0, &fixCtx), "0.000000" },
    { "1.23", Converter::ArkValue<Ark_Number>(1.23, &fixCtx), "1.230000" },
    { "-1.23", Converter::ArkValue<Ark_Number>(-1.23, &fixCtx), "-1.230000" },
    { "6.54", Converter::ArkValue<Ark_Number>(6.54, &fixCtx), "6.540000" },
    { "-99", Converter::ArkValue<Ark_Number>(-99, &fixCtx), "-99.000000" },
    { "100", Converter::ArkValue<Ark_Number>(100, &fixCtx), "100.000000" },
};

// Fixture 'ShadowOffsetRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureShadowOffsetResValidValues = {
    { "ResId:SHADOW_OFFSET_RES_0_ID", CreateResource(SHADOW_OFFSET_RES_0_ID, ResourceType::FLOAT), "0.100000" },
    { "ResName:SHADOW_OFFSET_RES_0_STR", CreateResource(SHADOW_OFFSET_RES_0_STR, ResourceType::FLOAT), "0.100000" },
    { "ResId:SHADOW_OFFSET_RES_1_ID", CreateResource(SHADOW_OFFSET_RES_1_ID, ResourceType::FLOAT), "3.000000" },
    { "ResName:SHADOW_OFFSET_RES_1_STR", CreateResource(SHADOW_OFFSET_RES_1_STR, ResourceType::FLOAT), "3.000000" },
    { "ResId:SHADOW_OFFSET_RES_2_ID", CreateResource(SHADOW_OFFSET_RES_2_ID, ResourceType::FLOAT), "0.900000" },
    { "ResName:SHADOW_OFFSET_RES_2_STR", CreateResource(SHADOW_OFFSET_RES_2_STR, ResourceType::FLOAT), "0.900000" },
    { "ResId:SHADOW_OFFSET_RES_3_ID", CreateResource(SHADOW_OFFSET_RES_3_ID, ResourceType::FLOAT), "-100.000000" },
    { "ResName:SHADOW_OFFSET_RES_3_STR", CreateResource(SHADOW_OFFSET_RES_3_STR, ResourceType::FLOAT), "-100.000000" },
    { "ResId:SHADOW_OFFSET_RES_4_ID", CreateResource(SHADOW_OFFSET_RES_4_ID, ResourceType::FLOAT), "99.000000" },
    { "ResName:SHADOW_OFFSET_RES_4_STR", CreateResource(SHADOW_OFFSET_RES_4_STR, ResourceType::FLOAT), "99.000000" },
    { "ResId:SHADOW_OFFSET_RES_5_ID", CreateResource(SHADOW_OFFSET_RES_5_ID, ResourceType::FLOAT), "-1.134000" },
    { "ResName:SHADOW_OFFSET_RES_5_STR", CreateResource(SHADOW_OFFSET_RES_5_STR, ResourceType::FLOAT), "-1.134000" },
    { "ResId:SHADOW_OFFSET_RES_6_ID", CreateResource(SHADOW_OFFSET_RES_6_ID, ResourceType::FLOAT), "1.100000" },
    { "ResName:SHADOW_OFFSET_RES_6_STR", CreateResource(SHADOW_OFFSET_RES_6_STR, ResourceType::FLOAT), "1.100000" },
};

// Fixture 'TimerInputCount' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureTimerInputCountValidValues = {
    { "1.0f", Converter::ArkValue<Ark_Number>(1.0f, &fixCtx), "1.000000" },
    { "25.0f", Converter::ArkValue<Ark_Number>(25.0f, &fixCtx), "25.000000" },
    { "86300000.0f", Converter::ArkValue<Ark_Number>(86300000.0f, &fixCtx), "86300000.000000" },
};

std::vector<std::tuple<std::string, Ark_Number>> testFixtureTimerInputCountInvalidValues = {
    { "-5.0", Converter::ArkValue<Ark_Number>(-5.0, &fixCtx) },
    { "86400001.0", Converter::ArkValue<Ark_Number>(86400001.0, &fixCtx) },
};

// Fixture 'TextTimerDateFormat' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureTextTimerDateFormatValidValues = {
    { "\"HH:mm:ss\"", Converter::ArkValue<Ark_String>("HH:mm:ss", &fixCtx), "HH:mm:ss" },
    { "\"HH:mm\"", Converter::ArkValue<Ark_String>("HH:mm", &fixCtx), "HH:mm" },
    { "\"mm:ss\"", Converter::ArkValue<Ark_String>("mm:ss", &fixCtx), "mm:ss" },
    { "\"mm:ss.SS\"", Converter::ArkValue<Ark_String>("mm:ss.SS", &fixCtx), "mm:ss.SS" },
    { "\"mm:ss.SSS\"", Converter::ArkValue<Ark_String>("mm:ss.SSS", &fixCtx), "mm:ss.SSS" },
    { "\"HH\"", Converter::ArkValue<Ark_String>("HH", &fixCtx), "HH" },
};

std::vector<std::tuple<std::string, Ark_String>> testFixtureTextTimerDateFormatInvalidValues = {
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz", &fixCtx) },
    { "\"zz:rr:tt\"", Converter::ArkValue<Ark_String>("zz:rr:tt", &fixCtx) },
};

// Fixture 'ImageContent' for type 'Ark_ImageContent'
std::vector<std::tuple<std::string, Ark_ImageContent, std::string>> testFixtureImageContentValidValues = {
    { "ARK_IMAGE_CONTENT_EMPTY", Converter::ArkValue<Ark_ImageContent>(ARK_IMAGE_CONTENT_EMPTY, &fixCtx), "" },
};

} // namespace OHOS::Ace::NG::Fixtures
