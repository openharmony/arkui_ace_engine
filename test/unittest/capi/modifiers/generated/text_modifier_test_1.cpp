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

#include "text_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Text;

/*
 * @tc.name: setTextOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) << "Default value for attribute 'content'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_CONTROLLER_DEFAULT_VALUE)
        << "Default value for attribute 'value.controller'";
}

/*
 * @tc.name: setTextOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setFont0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE) << "Default value for attribute 'font.size'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'font.weight'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE) << "Default value for attribute 'font.family'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE) << "Default value for attribute 'font.style'";
}

/*
 * @tc.name: setFont0TestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestFontSizeValidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_Font inputValueFont = initValueFont;

        inputValueFont.size = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont0, attribute: font.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setFont0TestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Length& value) {
        Ark_Font inputValueFont = initValueFont;

        modifier_->setFont0(node_, &inputValueFont);
        inputValueFont.size = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont0, attribute: font.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setFont0TestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestFontWeightValidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Union_FontWeight_Number_String& value,
                          const std::string& expectedStr) {
        Ark_Font inputValueFont = initValueFont;

        inputValueFont.weight = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFont0, attribute: font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFont0TestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestFontWeightInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Ark_Font inputValueFont = initValueFont;

        modifier_->setFont0(node_, &inputValueFont);
        inputValueFont.weight = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont0, attribute: font.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_Number_String>());
}

/*
 * @tc.name: setFont0TestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestFontFamilyValidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Union_String_Resource& value,
                          const std::string& expectedStr) {
        Ark_Font inputValueFont = initValueFont;

        inputValueFont.family = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFont0, attribute: font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setFont0TestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestFontFamilyInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Union_String_Resource& value) {
        Ark_Font inputValueFont = initValueFont;

        modifier_->setFont0(node_, &inputValueFont);
        inputValueFont.family = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont0, attribute: font.family";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setFont0TestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFont0TestFontStyleValidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const Opt_FontStyle& value, const std::string& expectedStr) {
        Ark_Font inputValueFont = initValueFont;

        inputValueFont.style = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont0, attribute: font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value), expected);
    }
}

/*
 * @tc.name: setFont0TestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont0TestFontStyleInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFont;

    // Initial setup
    initValueFont.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFont.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFont.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFont.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_FontStyle& value) {
        Ark_Font inputValueFont = initValueFont;

        modifier_->setFont0(node_, &inputValueFont);
        inputValueFont.style = value;
        modifier_->setFont0(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont0, attribute: font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFont1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
    std::unique_ptr<JsonValue> resultFontValue =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'font.fontValue.size'";

    resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_WEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'font.fontValue.weight'";

    resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_FAMILY_DEFAULT_VALUE)
        << "Default value for attribute 'font.fontValue.family'";

    resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_STYLE_DEFAULT_VALUE)
        << "Default value for attribute 'font.fontValue.style'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_FONT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'font.options.enableVariableFontWeight'";
}

/*
 * @tc.name: setFont1TestFontFontValueSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueSizeValidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        inputValueFontValue.size = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setFont1TestFontFontValueSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueSizeInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_Length& value) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        inputValueFontValue.size = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setFont1TestFontFontValueWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueWeightValidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](const std::string& input,
                          const Opt_Union_FontWeight_Number_String& value, const std::string& expectedStr) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        inputValueFontValue.weight = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFont1TestFontFontValueWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueWeightInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        inputValueFontValue.weight = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_Number_String>());
}

/*
 * @tc.name: setFont1TestFontFontValueFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueFamilyValidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](const std::string& input,
                          const Opt_Union_String_Resource& value, const std::string& expectedStr) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        inputValueFontValue.family = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setFont1TestFontFontValueFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueFamilyInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        inputValueFontValue.family = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_FAMILY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.family";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setFont1TestFontFontValueStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueStyleValidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_FontStyle& value, const std::string& expectedStr) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        inputValueFontValue.style = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value), expected);
    }
}

/*
 * @tc.name: setFont1TestFontFontValueStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontFontValueStyleInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_FontStyle& value) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        inputValueFontValue.style = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultFontValue = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_FONT_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontValue, ATTRIBUTE_FONT_I_FONT_VALUE_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FONT_VALUE_I_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont1, attribute: font.fontValue.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFont1TestFontOptionsEnableVariableFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontOptionsEnableVariableFontWeightValidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).enableVariableFontWeight = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultOptions = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_FONT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFont1, attribute: font.options.enableVariableFontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setFont1TestFontOptionsEnableVariableFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFont1TestFontOptionsEnableVariableFontWeightInvalidValues, TestSize.Level1)
{
    Ark_Font initValueFontValue;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueFontValue.size = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueFontValue.weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    initValueFontValue.family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFontValue.style = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontValue, &initValueOptions](
                          const std::string& input, const Opt_Boolean& value) {
        Ark_Font inputValueFontValue = initValueFontValue;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        WriteTo(inputValueOptions).enableVariableFontWeight = value;
        modifier_->setFont1(node_, &inputValueFontValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultOptions = GetAttrValue<std::unique_ptr<JsonValue>>(resultFont, ATTRIBUTE_FONT_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_FONT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFont1, attribute: font.options.enableVariableFontWeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setFontColorTestFontColorValidValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueFontSize;

    // Initial setup
    initValueFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](const std::string& input,
                          const Ark_Union_Number_String_Resource& value, const std::string& expectedStr) {
        Ark_Union_Number_String_Resource inputValueFontSize = initValueFontSize;

        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
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
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueFontSize;

    // Initial setup
    initValueFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
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
 * @tc.name: setMinFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, DISABLED_setMinFontSizeTestMinFontSizeValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

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

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontSizeTestMinFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

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

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, DISABLED_setMaxFontSizeTestMaxFontSizeValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

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

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setMaxFontSizeTestMaxFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontSizeTestMaxFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMinFontScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'minFontScale'";
}

/*
 * @tc.name: setMinFontScaleTestMinFontScaleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontScaleTestMinFontScaleValidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const Ark_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setMinFontScaleTestMinFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontScaleTestMinFontScaleInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxFontScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'maxFontScale'";
}

/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontScaleTestMaxFontScaleValidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const Ark_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontScaleTestMaxFontScaleInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
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
 * @tc.name: setFontWeight0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontWeight0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'fontWeight'";
}

/*
 * @tc.name: setFontWeight0TestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontWeight0TestFontWeightValidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](const std::string& input,
                          const Ark_Union_Number_FontWeight_String& value, const std::string& expectedStr) {
        Ark_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        inputValueFontWeight = value;
        modifier_->setFontWeight0(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontWeight0, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontWeight0TestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontWeight0TestFontWeightInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Ark_Union_Number_FontWeight_String& value) {
        Ark_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight0(node_, &inputValueFontWeight);
        inputValueFontWeight = value;
        modifier_->setFontWeight0(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontWeight0, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontWeight1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontWeight1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultFontWeight =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultFontWeight, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultFontWeight, ATTRIBUTE_FONT_WEIGHT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_I_WEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'fontWeight.weight'";

    resultStr =
        GetAttrValue<std::string>(resultOptions, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'fontWeight.options.enableVariableFontWeight'";
}

/*
 * @tc.name: setFontWeight1TestFontWeightWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontWeight1TestFontWeightWeightValidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueWeight;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueWeight, &initValueOptions](const std::string& input,
                          const Ark_Union_Number_FontWeight_String& value, const std::string& expectedStr) {
        Ark_Union_Number_FontWeight_String inputValueWeight = initValueWeight;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        inputValueWeight = value;
        modifier_->setFontWeight1(node_, &inputValueWeight, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFontWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontWeight, ATTRIBUTE_FONT_WEIGHT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontWeight1, attribute: fontWeight.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontWeight1TestFontWeightWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontWeight1TestFontWeightWeightInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueWeight;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueWeight, &initValueOptions](
                          const std::string& input, const Ark_Union_Number_FontWeight_String& value) {
        Ark_Union_Number_FontWeight_String inputValueWeight = initValueWeight;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFontWeight1(node_, &inputValueWeight, &inputValueOptions);
        inputValueWeight = value;
        modifier_->setFontWeight1(node_, &inputValueWeight, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFontWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFontWeight, ATTRIBUTE_FONT_WEIGHT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_I_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontWeight1, attribute: fontWeight.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontWeight1TestFontWeightOptionsEnableVariableFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextModifierTest, DISABLED_setFontWeight1TestFontWeightOptionsEnableVariableFontWeightValidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueWeight;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueWeight, &initValueOptions](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_Union_Number_FontWeight_String inputValueWeight = initValueWeight;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).enableVariableFontWeight = value;
        modifier_->setFontWeight1(node_, &inputValueWeight, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFontWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultFontWeight, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultOptions, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setFontWeight1, attribute: fontWeight.options.enableVariableFontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setFontWeight1TestFontWeightOptionsEnableVariableFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontWeight1TestFontWeightOptionsEnableVariableFontWeightInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueWeight;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    initValueWeight = ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueWeight, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Ark_Union_Number_FontWeight_String inputValueWeight = initValueWeight;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFontWeight1(node_, &inputValueWeight, &inputValueOptions);
        WriteTo(inputValueOptions).enableVariableFontWeight = value;
        modifier_->setFontWeight1(node_, &inputValueWeight, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFontWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultFontWeight, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultOptions, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setFontWeight1, attribute: fontWeight.options.enableVariableFontWeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setTextAlignTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextAlignTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, DISABLED_setTextAlignTestTextAlignValidValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, DISABLED_setTextAlignTestTextAlignInvalidValues, TestSize.Level1)
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
 * @tc.name: setLineHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineHeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'lineHeight'";
}

/*
 * @tc.name: setLineHeightTestLineHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineHeightTestLineHeightValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](const std::string& input,
                          const Ark_Union_Number_String_Resource& value, const std::string& expectedStr) {
        Ark_Union_Number_String_Resource inputValueLineHeight = initValueLineHeight;

        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setLineHeightTestLineHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineHeightTestLineHeightInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueLineHeight = initValueLineHeight;

        modifier_->setLineHeight(node_, &inputValueLineHeight);
        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextOverflowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOverflowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextOverflow =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTextOverflow, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_DEFAULT_VALUE)
        << "Default value for attribute 'textOverflow.overflow'";
}

/*
 * @tc.name: setTextOverflowTestTextOverflowOverflowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOverflowTestTextOverflowOverflowValidValues, TestSize.Level1)
{
    Ark_TextOverflowOptions initValueTextOverflow;

    // Initial setup
    initValueTextOverflow.overflow = std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]);

    auto checkValue = [this, &initValueTextOverflow](
                          const std::string& input, const Ark_TextOverflow& value, const std::string& expectedStr) {
        Ark_TextOverflowOptions inputValueTextOverflow = initValueTextOverflow;

        inputValueTextOverflow.overflow = value;
        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextOverflow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextOverflow, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow.overflow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextOverflowValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextOverflowTestTextOverflowOverflowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOverflowTestTextOverflowOverflowInvalidValues, TestSize.Level1)
{
    Ark_TextOverflowOptions initValueTextOverflow;

    // Initial setup
    initValueTextOverflow.overflow = std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]);

    auto checkValue = [this, &initValueTextOverflow](const std::string& input, const Ark_TextOverflow& value) {
        Ark_TextOverflowOptions inputValueTextOverflow = initValueTextOverflow;

        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        inputValueTextOverflow.overflow = value;
        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextOverflow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextOverflow, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow.overflow";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextOverflowInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontFamilyTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, DISABLED_setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
{
    Ark_Union_String_Resource initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Ark_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Ark_Union_String_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_String_Resource inputValueFontFamily = initValueFontFamily;

        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_String_Resource, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Ark_Union_String_Resource initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Ark_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Ark_Union_String_Resource& value) {
        Ark_Union_String_Resource inputValueFontFamily = initValueFontFamily;

        modifier_->setFontFamily(node_, &inputValueFontFamily);
        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxLinesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) << "Default value for attribute 'maxLines'";
}

/*
 * @tc.name: setMaxLinesTestMaxLinesValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxLinesTestMaxLinesValidValues, TestSize.Level1)
{
    Ark_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueMaxLines](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueMaxLines = initValueMaxLines;

        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDecorationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDecorationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDecoration =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE) << "Default value for attribute 'decoration.type'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'decoration.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE)
        << "Default value for attribute 'decoration.style'";
}

/*
 * @tc.name: setDecorationTestDecorationTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationTypeValidValues, TestSize.Level1)
{
    Ark_DecorationStyleInterface initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Ark_TextDecorationType& value,
                          const std::string& expectedStr) {
        Ark_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        inputValueDecoration.type = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDecoration, attribute: decoration.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextDecorationTypeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDecorationTestDecorationTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDecorationTestDecorationTypeInvalidValues, TestSize.Level1)
{
    Ark_DecorationStyleInterface initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Ark_TextDecorationType& value) {
        Ark_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        inputValueDecoration.type = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDecoration, attribute: decoration.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextDecorationTypeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDecorationTestDecorationColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationColorValidValues, TestSize.Level1)
{
    Ark_DecorationStyleInterface initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        inputValueDecoration.color = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDecoration, attribute: decoration.color";
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
 * @tc.name: setDecorationTestDecorationColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDecorationTestDecorationColorInvalidValues, TestSize.Level1)
{
    Ark_DecorationStyleInterface initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_ResourceColor& value) {
        Ark_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        inputValueDecoration.color = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDecoration, attribute: decoration.color";
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
 * @tc.name: setDecorationTestDecorationStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationStyleValidValues, TestSize.Level1)
{
    Ark_DecorationStyleInterface initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_TextDecorationStyle& value,
                          const std::string& expectedStr) {
        Ark_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        inputValueDecoration.style = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDecoration, attribute: decoration.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextDecorationStyleValidValues) {
        checkValue(input, ArkValue<Opt_TextDecorationStyle>(value), expected);
    }
}

/*
 * @tc.name: setDecorationTestDecorationStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDecorationTestDecorationStyleInvalidValues, TestSize.Level1)
{
    Ark_DecorationStyleInterface initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_TextDecorationStyle& value) {
        Ark_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        inputValueDecoration.style = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDecoration, attribute: decoration.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextDecorationStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_TextDecorationStyle>(value));
    }
}

} // namespace OHOS::Ace::NG
