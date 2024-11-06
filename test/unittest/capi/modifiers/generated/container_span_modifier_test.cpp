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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

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
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'textBackgroundStyle.color'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_DEFAULT_VALUE)
        << "Default value for attribute 'textBackgroundStyle.radius..topLeft'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'textBackgroundStyle.radius..topRight'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_DEFAULT_VALUE)
        << "Default value for attribute 'textBackgroundStyle.radius..bottomLeft'";

    resultStr = GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'textBackgroundStyle.radius..bottomRight'";
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleColorValidValues, TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        inputValueTextBackgroundStyle.color = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleColorInvalidValues, TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        inputValueTextBackgroundStyle.color = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusTopLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusTopLeftValidValues, TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).topLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..topLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusTopLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusTopLeftInvalidValues, TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).topLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_LEFT_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..topLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusTopRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusTopRightValidValues, TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).topRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..topRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusTopRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusTopRightInvalidValues,
    TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).topRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_TOP_RIGHT_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..topRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomLeftValidValues,
    TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).bottomLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..bottomLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomLeftInvalidValues,
    TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).bottomLeft = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_LEFT_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..bottomLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomRightValidValues,
    TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).bottomRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..bottomRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ContainerSpanModifierTest, setTextBackgroundStyleTestTextBackgroundStyleRadiusBottomRightInvalidValues,
    TestSize.Level1)
{
    Ark_TextBackgroundStyle initValueTextBackgroundStyle;

    // Initial setup
    initValueTextBackgroundStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(WriteTo(initValueTextBackgroundStyle.radius)).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueTextBackgroundStyle](const std::string& input, const Opt_Length& value) {
        Ark_TextBackgroundStyle inputValueTextBackgroundStyle = initValueTextBackgroundStyle;

        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        WriteToUnion<Ark_BorderRadiuses>(WriteTo(inputValueTextBackgroundStyle.radius)).bottomRight = value;
        modifier_->setTextBackgroundStyle(node_, &inputValueTextBackgroundStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextBackgroundStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_BACKGROUND_STYLE_NAME);
        auto resultRadius = GetAttrValue<std::unique_ptr<JsonValue>>(
            resultTextBackgroundStyle, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadius, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BACKGROUND_STYLE_I_RADIUS_I_BOTTOM_RIGHT_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setTextBackgroundStyle, attribute: textBackgroundStyle.radius..bottomRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}
} // namespace OHOS::Ace::NG
