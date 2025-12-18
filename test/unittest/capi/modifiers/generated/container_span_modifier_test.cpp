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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME = "textBackgroundStyle";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_DEFAULT_VALUE = "#00000000";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_NAME = "topLeft";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_NAME = "topRight";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_NAME = "bottomLeft";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_NAME = "bottomRight";
const auto ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_DEFAULT_VALUE = "0.00vp";
} // namespace

class ContainerSpanModifierTest
    : public ModifierTestBase<GENERATED_ArkUIContainerSpanModifier,
          &GENERATED_ArkUINodeModifiers::getContainerSpanModifier, GENERATED_ARKUI_CONTAINER_SPAN> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setTextBackgroundStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextBackgroundStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
    std::unique_ptr<JsonValue> resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
        resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'textBackgroundStyle.color'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_DEFAULT_VALUE) <<
        "Default value for attribute 'textBackgroundStyle.radius.BorderRadiuses.topLeft'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'textBackgroundStyle.radius.BorderRadiuses.topRight'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_DEFAULT_VALUE) <<
        "Default value for attribute 'textBackgroundStyle.radius.BorderRadiuses.bottomLeft'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'textBackgroundStyle.radius.BorderRadiuses.bottomRight'";
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, DISABLED_setTextBackgroundStyleTestTextBackgroundStyleColorValidValues,
    TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteTo(inputValueTextBackgroundStyle).color = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleColorInvalidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteTo(inputValueTextBackgroundStyle).color = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopLeftValidValues,
    TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).topLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.topLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest,
    setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopLeftInvalidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).topLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.topLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest,
    setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopRightValidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).topRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.topRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest,
    setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesTopRightInvalidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).topRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.topRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest,
    setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomLeftValidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).bottomLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.bottomLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest,
    setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomLeftInvalidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).bottomLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.bottomLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest,
    setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomRightValidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).bottomRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.bottomRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest,
    setTextBackgroundStyleTestTextBackgroundStyleRadiusBorderRadiusesBottomRightInvalidValues, TestSize.Level1)
{
    Opt_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    WriteTo(initValueTextBackgroundStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).topRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomLeft =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(initValueTextBackgroundStyle).radius)).bottomRight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Opt_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(WriteTo(inputValueTextBackgroundStyle).radius)).bottomRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius.BorderRadiuses.bottomRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}
} // namespace OHOS::Ace::NG
