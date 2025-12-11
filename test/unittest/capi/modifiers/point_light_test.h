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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_COMMON_MODIFIERS_TEST_POINT_LIGHT_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_COMMON_MODIFIERS_TEST_POINT_LIGHT_H
#include <tuple>

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::PointLight {
    using namespace Converter;

    constexpr auto COLORS_RES_0_ID = 100001;
    constexpr auto COLORS_ALPHA_20RES_0_ID = 200002;
    constexpr auto COLORS_ALPHA_20RES_1_ID = 300003;

    constexpr auto COLORS_RES_0_STR = "COLORS_RES_0_STR";
    constexpr auto COLORS_ALPHA_20RES_0_STR = "COLORS_ALPHA_20RES_0_STR";
    constexpr auto COLORS_ALPHA_20RES_1_STR = "COLORS_ALPHA_20RES_1_STR";

    const std::vector<std::tuple<int, std::string, ResRawValue>> resourceInitTable = {
        { COLORS_RES_0_ID, COLORS_RES_0_STR, Color(0xA1FAC0DE) },
        { COLORS_ALPHA_20RES_0_ID, COLORS_ALPHA_20RES_0_STR, Color(0xA1FAC0DE) },
        { COLORS_ALPHA_20RES_1_ID, COLORS_ALPHA_20RES_1_STR, Color(0xFFFAC0DE) },
    };

    const auto ATTRIBUTE_POINT_LIGHT_NAME = "pointLight";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME = "lightSource";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_DEFAULT_VALUE = "No light source";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_NAME = "LightPosition";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_DEFAULT_VALUE = "{}";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_NAME = "x";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_NAME = "y";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_NAME = "z";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_NAME = "lightIntensity";
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_DEFAULT_VALUE = 0.f;
    const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_NAME = "color";
    const auto ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME = "illuminated";
    const auto ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_DEFAULT_VALUE = "IlluminatedType.NONE";
    const auto ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME = "bloom";
    const auto ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE = 0.f;

    // Fixture 'LengthNonNegNonPct' for type 'Ark_Dimension'
    const std::vector<std::tuple<std::string, Ark_Dimension, std::string>> testFixtureLengthLightPosition = {
        { "123.0vp", ArkValue<Ark_Dimension>("123.0vp"), "123.00vp" },
        { "0.0vp", ArkValue<Ark_Dimension>("0.0vp"), "0.00vp" },
        { "1.23vp", ArkValue<Ark_Dimension>("1.23vp"), "1.23vp" },
        { "123.0fp", ArkValue<Ark_Dimension>("123.0fp"), "123.00fp" },
        { "0.0fp", ArkValue<Ark_Dimension>("0.0fp"), "0.00fp" },
        { "1.23fp", ArkValue<Ark_Dimension>("1.23fp"), "1.23fp" },
        { "123.0px", ArkValue<Ark_Dimension>("123.0px"), "123.00px" },
        { "0.0px", ArkValue<Ark_Dimension>("0.0px"), "0.00px" },
        { "1.23px", ArkValue<Ark_Dimension>("1.23px"), "1.23px" },
        { "-2.f", ArkValue<Ark_Dimension>(-2.f), "-2.00vp" },
        { "-2.3vp", ArkValue<Ark_Dimension>("-2.3vp"), "-2.30vp" },
        { "-4.5fp", ArkValue<Ark_Dimension>("-4.5fp"), "-4.50fp" },
        { "-5.6px", ArkValue<Ark_Dimension>("-5.6px"), "-5.60px" },
        { "50.00%", ArkValue<Ark_Dimension>("50.00%"), "50.00%" },
        { "0.00%", ArkValue<Ark_Dimension>("0.00%"), "0.00%" },
        { "-80.00%", ArkValue<Ark_Dimension>("-80.00%"), "-80.00%" },
    };

    // Fixture 'NumberAnything' for type 'Ark_Number'
    const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureIntensityValidValues = {
        { "1.0", ArkValue<Ark_Number>(1.0f), 1.f },
        { "0.0", ArkValue<Ark_Number>(0), 0.f },
        { "0.1", ArkValue<Ark_Number>(0.1f), 0.1f },
        { "0.99", ArkValue<Ark_Number>(0.99f), 0.99f },
        { "1.0", ArkValue<Ark_Number>(1), 1.f },
    };

    const std::vector<std::tuple<std::string, Ark_Number>> testFixtureIntensityInvalidValues = {
        { "100", ArkValue<Ark_Number>(100) },
        { "-0.01", ArkValue<Ark_Number>(-0.01f) },
        { "-100", ArkValue<Ark_Number>(-100) },
        { "12.34", ArkValue<Ark_Number>(12.34f) },
        { "-56.78", ArkValue<Ark_Number>(-56.78f) },
    };

    const std::vector<std::tuple<std::string,
        Ark_IlluminatedType,
        std::string>> testFixtureEnumIlluminatedTypeValidValues = {
        { "ARK_ILLUMINATED_TYPE_NONE", ARK_ILLUMINATED_TYPE_NONE, "IlluminatedType.NONE" },
        { "ARK_ILLUMINATED_TYPE_BORDER", ARK_ILLUMINATED_TYPE_BORDER, "IlluminatedType.BORDER" },
        { "ARK_ILLUMINATED_TYPE_CONTENT", ARK_ILLUMINATED_TYPE_CONTENT, "IlluminatedType.CONTENT" },
        { "ARK_ILLUMINATED_TYPE_BORDER_CONTENT", ARK_ILLUMINATED_TYPE_BORDER_CONTENT,
            "IlluminatedType.BORDER_CONTENT" },
        { "ARK_ILLUMINATED_TYPE_BLOOM_BORDER", ARK_ILLUMINATED_TYPE_BLOOM_BORDER, "IlluminatedType.BLOOM_BORDER" },
        { "ARK_ILLUMINATED_TYPE_BLOOM_BORDER_CONTENT", ARK_ILLUMINATED_TYPE_BLOOM_BORDER_CONTENT,
            "IlluminatedType.BLOOM_BORDER_CONTENT" },
    };

    const std::vector<std::tuple<std::string, Ark_IlluminatedType>> testFixtureEnumIlluminatedTypeInvalidValues = {
        { "-1", static_cast<Ark_IlluminatedType>(-1) },
        { "INT_MAX", static_cast<Ark_IlluminatedType>(INT_MAX) },
    };

    // Fixture 'NumberAnything' for type 'Ark_Number'
    const std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureBloomValidValues = {
        { "100", ArkValue<Ark_Number>(100), "100" },
        { "0", ArkValue<Ark_Number>(0), "0" },
        { "-100", ArkValue<Ark_Number>(-100), "-100" },
        { "12.34", ArkValue<Ark_Number>(12.34), "12.34" },
        { "-56.78", ArkValue<Ark_Number>(-56.78), "-56.78" },
    };

    // Fixture 'ColorsEnum' for type 'Ark_Color'
    const std::vector<std::tuple<std::string, Ark_Color, std::string>> testFixtureColorsEnumValidValues = {
        { "ARK_COLOR_WHITE", ArkValue<Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { "ARK_COLOR_BLACK", ArkValue<Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
        { "ARK_COLOR_BLUE", ArkValue<Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
        { "ARK_COLOR_BROWN", ArkValue<Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
        { "ARK_COLOR_GRAY", ArkValue<Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
        { "ARK_COLOR_GREEN", ArkValue<Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
        { "ARK_COLOR_GREY", ArkValue<Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
        { "ARK_COLOR_ORANGE", ArkValue<Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
        { "ARK_COLOR_PINK", ArkValue<Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
        { "ARK_COLOR_RED", ArkValue<Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
        { "ARK_COLOR_YELLOW", ArkValue<Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
        { "ARK_COLOR_TRANSPARENT", ArkValue<Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
    };

    const std::vector<std::tuple<std::string, Ark_Color>> testFixtureColorsEnumInvalidValues = {
        { "static_cast<Ark_Color>(-1)", ArkValue<Ark_Color>(static_cast<Ark_Color>(-1)) },
        { "static_cast<Ark_Color>(INT_MAX)", ArkValue<Ark_Color>(static_cast<Ark_Color>(INT_MAX)) },
    };

    // Fixture 'ColorsAlpha20Enum' for type 'Ark_Color'
    const std::vector<std::tuple<std::string, Ark_Color, std::string>> testFixtureColorsAlpha20EnumValidValues = {
        { "ARK_COLOR_WHITE", ArkValue<Ark_Color>(ARK_COLOR_WHITE), "#33FFFFFF" },
        { "ARK_COLOR_BLACK", ArkValue<Ark_Color>(ARK_COLOR_BLACK), "#33000000" },
        { "ARK_COLOR_BLUE", ArkValue<Ark_Color>(ARK_COLOR_BLUE), "#330000FF" },
        { "ARK_COLOR_BROWN", ArkValue<Ark_Color>(ARK_COLOR_BROWN), "#33A52A2A" },
        { "ARK_COLOR_GRAY", ArkValue<Ark_Color>(ARK_COLOR_GRAY), "#33808080" },
        { "ARK_COLOR_GREEN", ArkValue<Ark_Color>(ARK_COLOR_GREEN), "#33008000" },
        { "ARK_COLOR_GREY", ArkValue<Ark_Color>(ARK_COLOR_GREY), "#33808080" },
        { "ARK_COLOR_ORANGE", ArkValue<Ark_Color>(ARK_COLOR_ORANGE), "#33FFA500" },
        { "ARK_COLOR_PINK", ArkValue<Ark_Color>(ARK_COLOR_PINK), "#33FFC0CB" },
        { "ARK_COLOR_RED", ArkValue<Ark_Color>(ARK_COLOR_RED), "#33FF0000" },
        { "ARK_COLOR_YELLOW", ArkValue<Ark_Color>(ARK_COLOR_YELLOW), "#33FFFF00" },
        { "ARK_COLOR_TRANSPARENT", ArkValue<Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
    };

    const std::vector<std::tuple<std::string, Ark_Color>> testFixtureColorsAlpha20EnumInvalidValues = {
        { "static_cast<Ark_Color>(-1)", ArkValue<Ark_Color>(static_cast<Ark_Color>(-1)) },
        { "static_cast<Ark_Color>(INT_MAX)", ArkValue<Ark_Color>(static_cast<Ark_Color>(INT_MAX)) },
    };

    // Fixture 'ColorsStr' for type 'Ark_String'
    const std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsStrValidValues = {
        { "\"#123\"", ArkValue<Ark_String>("#123"), "#FF112233" },
        { "\"#11223344\"", ArkValue<Ark_String>("#11223344"), "#11223344" },
        { "\"#123456\"", ArkValue<Ark_String>("#123456"), "#FF123456" },
        { "\"65535\"", ArkValue<Ark_String>("65535"), "#FF00FFFF" },
        { "\"#abcdef\"", ArkValue<Ark_String>("#abcdef"), "#FFABCDEF" },
        { "\"#aBcdeF\"", ArkValue<Ark_String>("#aBcdeF"), "#FFABCDEF" },
        { "\"rgb(255, 100, 55)\"", ArkValue<Ark_String>("rgb(255, 100, 55)"), "#FFFF6437" },
        { "\"rgba(255, 100, 255, 0.5)\"", ArkValue<Ark_String>("rgba(255, 100, 255, 0.5)"), "#80FF64FF" },
    };

    const std::vector<std::tuple<std::string, Ark_String>> testFixtureColorsStrInvalidValues = {
        { "\"invalid\"", ArkValue<Ark_String>("invalid") },
        { "\"\"", ArkValue<Ark_String>("") },
        { "\"rgb(270, 0xf1, 755.5f)\"", ArkValue<Ark_String>("rgb(270, 0xf1, 755.5f)") },
        { "\"RgbA(255, 100, 255, 0.5)\"", ArkValue<Ark_String>("RgbA(255, 100, 255, 0.5)") },
    };

    // Fixture 'ColorsAlpha20Str' for type 'Ark_String'
    const std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsAlpha20StrValidValues = {
        { "\"#123\"", ArkValue<Ark_String>("#123"), "#33112233" },
        { "\"#11223344\"", ArkValue<Ark_String>("#11223344"), "#11223344" },
        { "\"#123456\"", ArkValue<Ark_String>("#123456"), "#33123456" },
        { "\"65535\"", ArkValue<Ark_String>("65535"), "#3300FFFF" },
        { "\"#abcdef\"", ArkValue<Ark_String>("#abcdef"), "#33ABCDEF" },
        { "\"#aBcdeF\"", ArkValue<Ark_String>("#aBcdeF"), "#33ABCDEF" },
        { "\"rgb(255, 100, 55)\"", ArkValue<Ark_String>("rgb(255, 100, 55)"), "#33FF6437" },
        { "\"rgba(255, 100, 255, 0.5)\"", ArkValue<Ark_String>("rgba(255, 100, 255, 0.5)"), "#80FF64FF" },
    };

    const std::vector<std::tuple<std::string, Ark_String>> testFixtureColorsAlpha20StrInvalidValues = {
        { "\"invalid\"", ArkValue<Ark_String>("invalid") },
        { "\"\"", ArkValue<Ark_String>("") },
        { "\"rgb(270, 0xf1, 755.5f)\"", ArkValue<Ark_String>("rgb(270, 0xf1, 755.5f)") },
        { "\"RgbA(255, 100, 255, 0.5)\"", ArkValue<Ark_String>("RgbA(255, 100, 255, 0.5)") },
    };

    // Fixture 'ColorsNum' for type 'Ark_Number'
    const std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureColorsNumValidValues = {
        { "0", ArkValue<Ark_Number>(0), "#00000000" },
        { "1", ArkValue<Ark_Number>(1), "#FF000001" },
        { "65535", ArkValue<Ark_Number>(65535), "#FF00FFFF" },
        { "-1", ArkValue<Ark_Number>(-1), "#FFFFFFFF" },
        { "0xBE7AC0DE", ArkValue<Ark_Number>(0xBE7AC0DE), "#BE7AC0DE" },
        { "std::numeric_limits<float>::quiet_NaN()",
            ArkValue<Ark_Number>(std::numeric_limits<float>::quiet_NaN()), "#80000000" },
        { "std::numeric_limits<float>::infinity()", ArkValue<Ark_Number>(std::numeric_limits<float>::infinity()),
            "#80000000" },
    };

    // Fixture 'ColorsAlpha20Num' for type 'Ark_Number'
    const std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureColorsAlpha20NumValidValues = {
        { "0", ArkValue<Ark_Number>(0), "#00000000" },
        { "1", ArkValue<Ark_Number>(1), "#33000001" },
        { "65535", ArkValue<Ark_Number>(65535), "#3300FFFF" },
        { "-1", ArkValue<Ark_Number>(-1), "#33FFFFFF" },
        { "0xBE7AC0DE", ArkValue<Ark_Number>(0xBE7AC0DE), "#BE7AC0DE" },
        { "std::numeric_limits<float>::quiet_NaN()",
            ArkValue<Ark_Number>(std::numeric_limits<float>::quiet_NaN()), "#80000000" },
        { "std::numeric_limits<float>::infinity()", ArkValue<Ark_Number>(std::numeric_limits<float>::infinity()),
            "#80000000" },
    };

    // Fixture 'ColorsRes' for type 'Ark_Resource'
    const std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsResValidValues = {
        { "ResId:COLORS_RES_0_ID", CreateResource(COLORS_RES_0_ID, ResourceType::COLOR), "#A1FAC0DE" },
        { "ResName:COLORS_RES_0_STR", CreateResource(COLORS_RES_0_STR, ResourceType::COLOR), "#A1FAC0DE" },
    };

    // Fixture 'ColorsAlpha20Res' for type 'Ark_Resource'
    const std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsAlpha20ResValidValues = {
        { "ResId:COLORS_ALPHA_20RES_0_ID", CreateResource(COLORS_ALPHA_20RES_0_ID, ResourceType::COLOR),
            "#A1FAC0DE" },
        { "ResName:COLORS_ALPHA_20RES_0_STR", CreateResource(COLORS_ALPHA_20RES_0_STR, ResourceType::COLOR),
            "#A1FAC0DE" },
        { "ResId:COLORS_ALPHA_20RES_1_ID", CreateResource(COLORS_ALPHA_20RES_1_ID, ResourceType::COLOR),
            "#33FAC0DE" },
        { "ResName:COLORS_ALPHA_20RES_1_STR", CreateResource(COLORS_ALPHA_20RES_1_STR, ResourceType::COLOR),
            "#33FAC0DE" },
    };
}
#endif