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

#include "text_area_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::TextArea;

/*
 * @tc.name: setTextAreaOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextAreaOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_PLACEHOLDER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_PLACEHOLDER_DEFAULT_VALUE)
        << "Default value for attribute 'value.placeholder'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_TEXT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_TEXT_DEFAULT_VALUE) << "Default value for attribute 'value.text'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_CONTROLLER_DEFAULT_VALUE)
        << "Default value for attribute 'value.controller'";
}

/*
 * @tc.name: setTextAreaOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setTextAreaOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setPlaceholderColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_COLOR_DEFAULT_VALUE) << "Default value for attribute 'placeholderColor'";
}

/*
 * @tc.name: setPlaceholderColorTestPlaceholderColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderColorTestPlaceholderColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValuePlaceholderColor;

    // Initial setup
    initValuePlaceholderColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValuePlaceholderColor = initValuePlaceholderColor;

        inputValuePlaceholderColor = value;
        modifier_->setPlaceholderColor(node_, &inputValuePlaceholderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPlaceholderColor, attribute: placeholderColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setPlaceholderColorTestPlaceholderColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderColorTestPlaceholderColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValuePlaceholderColor;

    // Initial setup
    initValuePlaceholderColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValuePlaceholderColor = initValuePlaceholderColor;

        modifier_->setPlaceholderColor(node_, &inputValuePlaceholderColor);
        inputValuePlaceholderColor = value;
        modifier_->setPlaceholderColor(node_, &inputValuePlaceholderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setPlaceholderColor, attribute: placeholderColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setPlaceholderFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPlaceholderFont =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'placeholderFont.size'";

    resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_WEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'placeholderFont.weight'";

    resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_FAMILY_DEFAULT_VALUE)
        << "Default value for attribute 'placeholderFont.family'";

    resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_DEFAULT_VALUE)
        << "Default value for attribute 'placeholderFont.style'";
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderFontTestPlaceholderFontSizeValidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        inputValuePlaceholderFont.size = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTestPlaceholderFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](const std::string& input, const Opt_Length& value) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        inputValuePlaceholderFont.size = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderFontTestPlaceholderFontWeightValidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](const std::string& input,
                          const Opt_Union_FontWeight_Number_String& value, const std::string& expectedStr) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        inputValuePlaceholderFont.weight = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderFontTestPlaceholderFontWeightInvalidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        inputValuePlaceholderFont.weight = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_Number_String>());
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderFontTestPlaceholderFontFamilyValidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](const std::string& input,
                          const Opt_Union_String_Resource& value, const std::string& expectedStr) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        inputValuePlaceholderFont.family = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderFontTestPlaceholderFontFamilyInvalidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        inputValuePlaceholderFont.family = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_FAMILY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.family";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTestPlaceholderFontStyleValidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](
                          const std::string& input, const Opt_FontStyle& value, const std::string& expectedStr) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        inputValuePlaceholderFont.style = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value), expected);
    }
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTestPlaceholderFontStyleInvalidValues, TestSize.Level1)
{
    Ark_Font initValuePlaceholderFont;

    // Initial setup
    initValuePlaceholderFont.size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValuePlaceholderFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValuePlaceholderFont.family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    initValuePlaceholderFont.style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](const std::string& input, const Opt_FontStyle& value) {
        Ark_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        inputValuePlaceholderFont.style = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setEnterKeyTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setEnterKeyTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE) << "Default value for attribute 'enterKeyType'";
}

/*
 * @tc.name: setEnterKeyTypeTestEnterKeyTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnterKeyTypeTestEnterKeyTypeValidValues, TestSize.Level1)
{
    Ark_EnterKeyType initValueEnterKeyType;

    // Initial setup
    initValueEnterKeyType = std::get<1>(Fixtures::testFixtureEnumEnterKeyTypeValidValues[0]);

    auto checkValue = [this, &initValueEnterKeyType](
                          const std::string& input, const Ark_EnterKeyType& value, const std::string& expectedStr) {
        Ark_EnterKeyType inputValueEnterKeyType = initValueEnterKeyType;

        inputValueEnterKeyType = value;
        modifier_->setEnterKeyType(node_, inputValueEnterKeyType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnterKeyType, attribute: enterKeyType";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumEnterKeyTypeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEnterKeyTypeTestEnterKeyTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setEnterKeyTypeTestEnterKeyTypeInvalidValues, TestSize.Level1)
{
    Ark_EnterKeyType initValueEnterKeyType;

    // Initial setup
    initValueEnterKeyType = std::get<1>(Fixtures::testFixtureEnumEnterKeyTypeValidValues[0]);

    auto checkValue = [this, &initValueEnterKeyType](const std::string& input, const Ark_EnterKeyType& value) {
        Ark_EnterKeyType inputValueEnterKeyType = initValueEnterKeyType;

        modifier_->setEnterKeyType(node_, inputValueEnterKeyType);
        inputValueEnterKeyType = value;
        modifier_->setEnterKeyType(node_, inputValueEnterKeyType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setEnterKeyType, attribute: enterKeyType";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumEnterKeyTypeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setTextAlignTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextAlignTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE) << "Default value for attribute 'textAlign'";
}

/*
 * @tc.name: setTextAlignTestTextAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setTextAlignTestTextAlignValidValues, TestSize.Level1)
{
    Ark_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = std::get<1>(Fixtures::testFixtureEnumTextAlignValidValues[0]);

    auto checkValue = [this, &initValueTextAlign](
                          const std::string& input, const Ark_TextAlign& value, const std::string& expectedStr) {
        Ark_TextAlign inputValueTextAlign = initValueTextAlign;

        inputValueTextAlign = value;
        modifier_->setTextAlign(node_, inputValueTextAlign);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextAlign, attribute: textAlign";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextAlignValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextAlignTestTextAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextAlignTestTextAlignInvalidValues, TestSize.Level1)
{
    Ark_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = std::get<1>(Fixtures::testFixtureEnumTextAlignValidValues[0]);

    auto checkValue = [this, &initValueTextAlign](const std::string& input, const Ark_TextAlign& value) {
        Ark_TextAlign inputValueTextAlign = initValueTextAlign;

        modifier_->setTextAlign(node_, inputValueTextAlign);
        inputValueTextAlign = value;
        modifier_->setTextAlign(node_, inputValueTextAlign);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextAlign, attribute: textAlign";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setCaretColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE) << "Default value for attribute 'caretColor'";
}

/*
 * @tc.name: setCaretColorTestCaretColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretColorTestCaretColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueCaretColor;

    // Initial setup
    initValueCaretColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueCaretColor = initValueCaretColor;

        inputValueCaretColor = value;
        modifier_->setCaretColor(node_, &inputValueCaretColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCaretColor, attribute: caretColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setCaretColorTestCaretColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretColorTestCaretColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueCaretColor;

    // Initial setup
    initValueCaretColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueCaretColor = initValueCaretColor;

        modifier_->setCaretColor(node_, &inputValueCaretColor);
        inputValueCaretColor = value;
        modifier_->setCaretColor(node_, &inputValueCaretColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCaretColor, attribute: caretColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fontColor'";
}

/*
 * @tc.name: setFontColorTestFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontColorTestFontColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueFontColor = initValueFontColor;

        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontColorTestFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueFontColor = initValueFontColor;

        modifier_->setFontColor(node_, &inputValueFontColor);
        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'fontSize'";
}

/*
 * @tc.name: setFontSizeTestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    Ark_Length initValueFontSize;

    // Initial setup
    initValueFontSize = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueFontSize](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueFontSize = initValueFontSize;

        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Length initValueFontSize;

    // Initial setup
    initValueFontSize = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueFontSize](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) << "Default value for attribute 'fontStyle'";
}

/*
 * @tc.name: setFontStyleTestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
{
    Ark_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]);

    auto checkValue = [this, &initValueFontStyle](
                          const std::string& input, const Ark_FontStyle& value, const std::string& expectedStr) {
        Ark_FontStyle inputValueFontStyle = initValueFontStyle;

        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFontStyleTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
{
    Ark_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]);

    auto checkValue = [this, &initValueFontStyle](const std::string& input, const Ark_FontStyle& value) {
        Ark_FontStyle inputValueFontStyle = initValueFontStyle;

        modifier_->setFontStyle(node_, inputValueFontStyle);
        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'fontWeight'";
}

/*
 * @tc.name: setFontWeightTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](const std::string& input,
                          const Ark_Union_Number_FontWeight_String& value, const std::string& expectedStr) {
        Ark_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Ark_Union_Number_FontWeight_String& value) {
        Ark_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight(node_, &inputValueFontWeight);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontFamilyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) << "Default value for attribute 'fontFamily'";
}

/*
 * @tc.name: setFontFamilyTestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Ark_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](
                          const std::string& input, const Ark_ResourceStr& value, const std::string& expectedStr) {
        Ark_ResourceStr inputValueFontFamily = initValueFontFamily;

        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Ark_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueFontFamily = initValueFontFamily;

        modifier_->setFontFamily(node_, &inputValueFontFamily);
        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextOverflowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextOverflowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE) << "Default value for attribute 'textOverflow'";
}

/*
 * @tc.name: setTextOverflowTestTextOverflowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setTextOverflowTestTextOverflowValidValues, TestSize.Level1)
{
    Ark_TextOverflow initValueTextOverflow;

    // Initial setup
    initValueTextOverflow = std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]);

    auto checkValue = [this, &initValueTextOverflow](
                          const std::string& input, const Ark_TextOverflow& value, const std::string& expectedStr) {
        Ark_TextOverflow inputValueTextOverflow = initValueTextOverflow;

        inputValueTextOverflow = value;
        modifier_->setTextOverflow(node_, inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextOverflowValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextOverflowTestTextOverflowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setTextOverflowTestTextOverflowInvalidValues, TestSize.Level1)
{
    Ark_TextOverflow initValueTextOverflow;

    // Initial setup
    initValueTextOverflow = std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]);

    auto checkValue = [this, &initValueTextOverflow](const std::string& input, const Ark_TextOverflow& value) {
        Ark_TextOverflow inputValueTextOverflow = initValueTextOverflow;

        modifier_->setTextOverflow(node_, inputValueTextOverflow);
        inputValueTextOverflow = value;
        modifier_->setTextOverflow(node_, inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextOverflowInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setTextIndentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextIndentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE) << "Default value for attribute 'textIndent'";
}

/*
 * @tc.name: setTextIndentTestTextIndentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextIndentTestTextIndentValidValues, TestSize.Level1)
{
    Ark_Length initValueTextIndent;

    // Initial setup
    initValueTextIndent = std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]);

    auto checkValue = [this, &initValueTextIndent](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueTextIndent = initValueTextIndent;

        inputValueTextIndent = value;
        modifier_->setTextIndent(node_, &inputValueTextIndent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextIndent, attribute: textIndent";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setCaretStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCaretStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_WIDTH_DEFAULT_VALUE)
        << "Default value for attribute 'caretStyle.width'";

    resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'caretStyle.color'";
}

/*
 * @tc.name: setCaretStyleTestCaretStyleWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretStyleTestCaretStyleWidthValidValues, TestSize.Level1)
{
    Ark_CaretStyle initValueCaretStyle;

    // Initial setup
    initValueCaretStyle.width =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueCaretStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        inputValueCaretStyle.width = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.width";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setCaretStyleTestCaretStyleWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretStyleTestCaretStyleWidthInvalidValues, TestSize.Level1)
{
    Ark_CaretStyle initValueCaretStyle;

    // Initial setup
    initValueCaretStyle.width =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueCaretStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](const std::string& input, const Opt_Length& value) {
        Ark_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        inputValueCaretStyle.width = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.width";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setCaretStyleTestCaretStyleColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretStyleTestCaretStyleColorValidValues, TestSize.Level1)
{
    Ark_CaretStyle initValueCaretStyle;

    // Initial setup
    initValueCaretStyle.width =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueCaretStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        inputValueCaretStyle.color = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.color";
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
 * @tc.name: setCaretStyleTestCaretStyleColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretStyleTestCaretStyleColorInvalidValues, TestSize.Level1)
{
    Ark_CaretStyle initValueCaretStyle;

    // Initial setup
    initValueCaretStyle.width =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueCaretStyle.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        inputValueCaretStyle.color = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.color";
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
 * @tc.name: setSelectedBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setSelectedBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'selectedBackgroundColor'";
}

/*
 * @tc.name: setSelectedBackgroundColorTestSelectedBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setSelectedBackgroundColorTestSelectedBackgroundColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueSelectedBackgroundColor;

    // Initial setup
    initValueSelectedBackgroundColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedBackgroundColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueSelectedBackgroundColor = initValueSelectedBackgroundColor;

        inputValueSelectedBackgroundColor = value;
        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input
                                          << ", method: setSelectedBackgroundColor, attribute: selectedBackgroundColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setSelectedBackgroundColorTestSelectedBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setSelectedBackgroundColorTestSelectedBackgroundColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueSelectedBackgroundColor;

    // Initial setup
    initValueSelectedBackgroundColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedBackgroundColor](
                          const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueSelectedBackgroundColor = initValueSelectedBackgroundColor;

        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        inputValueSelectedBackgroundColor = value;
        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setSelectedBackgroundColor, attribute: selectedBackgroundColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setCopyOptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCopyOptionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE) << "Default value for attribute 'copyOption'";
}

/*
 * @tc.name: setCopyOptionTestCopyOptionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setCopyOptionTestCopyOptionValidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOption](
                          const std::string& input, const Ark_CopyOptions& value, const std::string& expectedStr) {
        Ark_CopyOptions inputValueCopyOption = initValueCopyOption;

        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setCopyOptionTestCopyOptionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setCopyOptionTestCopyOptionInvalidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOption](const std::string& input, const Ark_CopyOptions& value) {
        Ark_CopyOptions inputValueCopyOption = initValueCopyOption;

        modifier_->setCopyOption(node_, inputValueCopyOption);
        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setEnableKeyboardOnFocusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnableKeyboardOnFocusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE)
        << "Default value for attribute 'enableKeyboardOnFocus'";
}

/*
 * @tc.name: setEnableKeyboardOnFocusTestEnableKeyboardOnFocusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnableKeyboardOnFocusTestEnableKeyboardOnFocusValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableKeyboardOnFocus;

    // Initial setup
    initValueEnableKeyboardOnFocus = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableKeyboardOnFocus](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableKeyboardOnFocus = initValueEnableKeyboardOnFocus;

        inputValueEnableKeyboardOnFocus = value;
        modifier_->setEnableKeyboardOnFocus(node_, inputValueEnableKeyboardOnFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableKeyboardOnFocus, attribute: enableKeyboardOnFocus";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMaxLengthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxLengthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE) << "Default value for attribute 'maxLength'";
}

/*
 * @tc.name: setMaxLengthTestMaxLengthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxLengthTestMaxLengthValidValues, TestSize.Level1)
{
    Ark_Number initValueMaxLength;

    // Initial setup
    initValueMaxLength = std::get<1>(Fixtures::testFixtureTextMaxLengthValidValues[0]);

    auto checkValue = [this, &initValueMaxLength](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueMaxLength = initValueMaxLength;

        inputValueMaxLength = value;
        modifier_->setMaxLength(node_, &inputValueMaxLength);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMaxLength, attribute: maxLength";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextMaxLengthValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setShowCounterTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultShowCounter =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_VALUE_DEFAULT_VALUE)
        << "Default value for attribute 'showCounter.value'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_DEFAULT_VALUE)
        << "Default value for attribute 'showCounter.options.thresholdPercentage'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_DEFAULT_VALUE)
        << "Default value for attribute 'showCounter.options.highlightBorder'";
}

/*
 * @tc.name: setShowCounterTestShowCounterValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterValueValidValues, TestSize.Level1)
{
    Ark_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        inputValueValue = value;
        modifier_->setShowCounter(node_, inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setShowCounter, attribute: showCounter.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsThresholdPercentageValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsThresholdPercentageValidValues, TestSize.Level1)
{
    Ark_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).thresholdPercentage = value;
        modifier_->setShowCounter(node_, inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.thresholdPercentage";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPercentageThresholdFloorValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsThresholdPercentageInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsThresholdPercentageInvalidValues, TestSize.Level1)
{
    Ark_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Ark_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, inputValueValue, &inputValueOptions);
        WriteTo(inputValueOptions).thresholdPercentage = value;
        modifier_->setShowCounter(node_, inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.thresholdPercentage";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPercentageThresholdFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsHighlightBorderValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsHighlightBorderValidValues, TestSize.Level1)
{
    Ark_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).highlightBorder = value;
        modifier_->setShowCounter(node_, inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input
                                          << ", method: setShowCounter, attribute: showCounter.options.highlightBorder";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsHighlightBorderInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsHighlightBorderInvalidValues, TestSize.Level1)
{
    Ark_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Ark_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, inputValueValue, &inputValueOptions);
        WriteTo(inputValueOptions).highlightBorder = value;
        modifier_->setShowCounter(node_, inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.highlightBorder";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE) << "Default value for attribute 'style'";
}

/*
 * @tc.name: setStyleTestStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setStyleTestStyleValidValues, TestSize.Level1)
{
    Ark_TextContentStyle initValueStyle;

    // Initial setup
    initValueStyle = std::get<1>(Fixtures::testFixtureEnumTextContentStyleValidValues[0]);

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const Ark_TextContentStyle& value, const std::string& expectedStr) {
        Ark_TextContentStyle inputValueStyle = initValueStyle;

        inputValueStyle = value;
        modifier_->setStyle(node_, inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setStyle, attribute: style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextContentStyleValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setStyleTestStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setStyleTestStyleInvalidValues, TestSize.Level1)
{
    Ark_TextContentStyle initValueStyle;

    // Initial setup
    initValueStyle = std::get<1>(Fixtures::testFixtureEnumTextContentStyleValidValues[0]);

    auto checkValue = [this, &initValueStyle](const std::string& input, const Ark_TextContentStyle& value) {
        Ark_TextContentStyle inputValueStyle = initValueStyle;

        modifier_->setStyle(node_, inputValueStyle);
        inputValueStyle = value;
        modifier_->setStyle(node_, inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setStyle, attribute: style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextContentStyleInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setBarStateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setBarStateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE) << "Default value for attribute 'barState'";
}

/*
 * @tc.name: setBarStateTestBarStateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setBarStateTestBarStateValidValues, TestSize.Level1)
{
    Ark_BarState initValueBarState;

    // Initial setup
    initValueBarState = std::get<1>(Fixtures::testFixtureTextInputBarStateValidValues[0]);

    auto checkValue = [this, &initValueBarState](
                          const std::string& input, const Ark_BarState& value, const std::string& expectedStr) {
        Ark_BarState inputValueBarState = initValueBarState;

        inputValueBarState = value;
        modifier_->setBarState(node_, inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputBarStateValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setBarStateTestBarStateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setBarStateTestBarStateInvalidValues, TestSize.Level1)
{
    Ark_BarState initValueBarState;

    // Initial setup
    initValueBarState = std::get<1>(Fixtures::testFixtureTextInputBarStateValidValues[0]);

    auto checkValue = [this, &initValueBarState](const std::string& input, const Ark_BarState& value) {
        Ark_BarState inputValueBarState = initValueBarState;

        modifier_->setBarState(node_, inputValueBarState);
        inputValueBarState = value;
        modifier_->setBarState(node_, inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputBarStateInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setSelectionMenuHiddenTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setSelectionMenuHiddenTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_HIDDEN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_MENU_HIDDEN_DEFAULT_VALUE)
        << "Default value for attribute 'selectionMenuHidden'";
}

/*
 * @tc.name: setSelectionMenuHiddenTestSelectionMenuHiddenValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setSelectionMenuHiddenTestSelectionMenuHiddenValidValues, TestSize.Level1)
{
    Ark_Boolean initValueSelectionMenuHidden;

    // Initial setup
    initValueSelectionMenuHidden = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueSelectionMenuHidden](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueSelectionMenuHidden = initValueSelectionMenuHidden;

        inputValueSelectionMenuHidden = value;
        modifier_->setSelectionMenuHidden(node_, inputValueSelectionMenuHidden);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_HIDDEN_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSelectionMenuHidden, attribute: selectionMenuHidden";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMinFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMinFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'minFontSize'";
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMinFontSizeTestMinFontSizeValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](const std::string& input,
                          const Ark_Union_Number_String_Resource& value, const std::string& expectedStr) {
        Ark_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMinFontSizeTestMinFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'maxFontSize'";
}

/*
 * @tc.name: setMaxFontSizeTestMaxFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxFontSizeTestMaxFontSizeValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](const std::string& input,
                          const Ark_Union_Number_String_Resource& value, const std::string& expectedStr) {
        Ark_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value), expected);
    }
}

} // namespace OHOS::Ace::NG
