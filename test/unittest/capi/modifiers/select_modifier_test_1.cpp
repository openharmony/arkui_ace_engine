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

#include "select_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace SelectTest;

namespace SelectTest {
std::vector<std::tuple<std::string, Ark_Number, std::string>> testNumberNonNegIntValidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0), "0" },
    { "1", Converter::ArkValue<Ark_Number>(1), "1" },
};
std::vector<std::tuple<std::string, Ark_String, std::string>> testWeightStringValidValues = {
    { "\"ARK_FONT_WEIGHT_LIGHTER\"", Converter::ArkValue<Ark_String>("lighter"), "FontWeight.Lighter" },
    { "\"ARK_FONT_WEIGHT_NORMAL\"", Converter::ArkValue<Ark_String>("normal"), "FontWeight.Normal" },
    { "\"ARK_FONT_WEIGHT_REGULAR\"", Converter::ArkValue<Ark_String>("regular"), "FontWeight.Regular" },
    { "\"ARK_FONT_WEIGHT_MEDIUM\"", Converter::ArkValue<Ark_String>("medium"), "FontWeight.Medium" },
    { "\"ARK_FONT_WEIGHT_BOLD\"", Converter::ArkValue<Ark_String>("bold"), "FontWeight.Bold" },
    { "\"ARK_FONT_WEIGHT_BOLDER\"", Converter::ArkValue<Ark_String>("bolder"), "FontWeight.Bolder" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testWeightNumberValidValues = {
    { "\"100\"", Converter::ArkValue<Ark_Number>(100), "100" },
    { "\"200\"", Converter::ArkValue<Ark_Number>(200), "200" },
    { "\"300\"", Converter::ArkValue<Ark_Number>(300), "300" },
    { "\"400\"", Converter::ArkValue<Ark_Number>(400), "400" },
    { "\"500\"", Converter::ArkValue<Ark_Number>(500), "500" },
    { "\"600\"", Converter::ArkValue<Ark_Number>(600), "600" },
    { "\"700\"", Converter::ArkValue<Ark_Number>(700), "700" },
    { "\"800\"", Converter::ArkValue<Ark_Number>(800), "800" },
    { "\"900\"", Converter::ArkValue<Ark_Number>(900), "900" },
};

std::vector<std::tuple<std::string, Ark_Resource, std::string>> testIntResValidValues = {
    { "ResId:INT_RES_0_ID", CreateResource(INT_RES_0_STR, Converter::ResourceType::INTEGER), "0" },
    { "ResId:INT_RES_1_ID", CreateResource(INT_RES_1_STR, Converter::ResourceType::INTEGER), "1" },
    { "ResName:INT_RES_2_STR", CreateResource(INT_RES_2_STR, Converter::ResourceType::INTEGER), "12" },
    { "ResId:INT_RES_3_ID", CreateResource(INT_RES_3_STR, Converter::ResourceType::INTEGER), "123" },
    { "ResName:INT_RES_4_STR", CreateResource(INT_RES_4_STR, Converter::ResourceType::INTEGER), "1234" },
    { "ResId:INT_RES_5_ID", CreateResource(INT_RES_5_STR, Converter::ResourceType::INTEGER), "12345" },
    { "ResName:INT_RES_6_STR", CreateResource(INT_RES_6_STR, Converter::ResourceType::INTEGER), "123456" },
};
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testStringResValidValues = {
    { "ResId:STR_RES_0_ID", CreateResource(STR_RES_0_ID, Converter::ResourceType::STRING), "abc" },
    { "ResName:STR_RES_0_STR", CreateResource(STR_RES_0_STR, Converter::ResourceType::STRING), "abc" },
    { "ResId:STR_RES_1_ID", CreateResource(STR_RES_1_ID, Converter::ResourceType::STRING), "" },
    { "ResName:STR_RES_1_STR", CreateResource(STR_RES_1_STR, Converter::ResourceType::STRING), "" },
};
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testColorsResValidValues = {
    { "ResId:COLOR_RES_0_ID", CreateResource(COLOR_RES_0_ID, Converter::ResourceType::COLOR), "#A1FAC0DE" },
    { "ResName:COLOR_RES_0_STR", CreateResource(COLOR_RES_0_STR, Converter::ResourceType::COLOR), "#A1FAC0DE" },
};
std::vector<std::tuple<ResIntegerID, std::string, OHOS::Ace::ResRawValue>> resourceInitTable = {
    { INT_RES_0_ID, INT_RES_0_STR, 0 },
    { INT_RES_1_ID, INT_RES_1_STR, 1 },
    { INT_RES_2_ID, INT_RES_2_STR, 12 },
    { INT_RES_3_ID, INT_RES_3_STR, 123 },
    { INT_RES_4_ID, INT_RES_4_STR, 1234},
    { INT_RES_5_ID, INT_RES_5_STR, 12345 },
    { INT_RES_6_ID, INT_RES_6_STR, 123456 },
    { STR_RES_0_ID, STR_RES_0_STR, "abc" },
    { STR_RES_1_ID, STR_RES_1_STR, "" },
    { COLOR_RES_0_ID, COLOR_RES_0_STR, Color(0xA1FAC0DE) },
    { FONT_FAMILY_RES_1_ID, FONT_FAMILY_RES_NAME, FONT_FAMILY_RES_VALUE },
    { VALUE_RES_1_ID, VALUE_RES_NAME, VALUE_RES_VALUE },
    { OPTIONS_VALUE_RES_1_ID, OPTIONS_VALUE_RES_NAME, OPTIONS_VALUE_RES_VALUE },
    { OPTIONS_ICON_RES_1_ID, OPTIONS_ICON_RES_NAME, OPTIONS_ICON_RES_VALUE },
};
}
/*
 * @tc.name: setSelected1TestSelectedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelected1TestSelectedValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueSelected;
    initValueSelected =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueSelected](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueSelected = initValueSelected;
        inputValueSelected = value;
        modifier_->setSelected1(node_, &inputValueSelected);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelected1, attribute: selected";
    };
// we can check only empty selection, i.e. 0 and 1 indexes
    for (auto& [input, value, expected] : testNumberNonNegIntValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    //todo add recource test
}

/*
 * @tc.name: setSelected1TestSelectedInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelected1TestSelectedInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueSelected;
    initValueSelected =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueSelected](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueSelected = initValueSelected;

        modifier_->setSelected1(node_, &inputValueSelected);
        inputValueSelected = value;
        modifier_->setSelected1(node_, &inputValueSelected);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelected1, attribute: selected";
    };
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Number>(-1));
}

/*
 * @tc.name: setValue0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setValue0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'value'";
}

/*
 * @tc.name: setValue0TestValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setValue0TestValueInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueValue;

    // Initial setup
    initValueValue = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueValue = initValueValue;

        modifier_->setValue0(node_, &inputValueValue);
        inputValueValue = value;
        modifier_->setValue0(node_, &inputValueValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setValue0, attribute: value";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setValue1TestValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setValue1TestValueValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    auto checkValue = [this, &initValueValue](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueValue = initValueValue;

        inputValueValue = value;
        modifier_->setValue1(node_, &inputValueValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setValue1, attribute: value";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : testStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setValue1TestValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setValue1TestValueInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueValue = initValueValue;

        modifier_->setValue1(node_, &inputValueValue);
        inputValueValue = value;
        modifier_->setValue1(node_, &inputValueValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setValue1, attribute: value";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setFont0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont0TestDefaultValues, TestSize.Level1)
{
    modifier_->setFont1(node_, nullptr);
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
 * @tc.name: setFont1TestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontSizeValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).size = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont1, attribute: font.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setFont1TestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Length& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont1(node_, &inputValueFont);
        WriteTo(inputValueFont).size = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont1, attribute: font.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setFont1TestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontWeightValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_Number_String& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).weight = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFont1, attribute: font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : testWeightNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : testWeightStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFont1TestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont1(node_, &inputValueFont);
        WriteTo(inputValueFont).weight = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont1, attribute: font.weight";
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
 * @tc.name: setFont1TestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontFamilyValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).family = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFont1, attribute: font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : testStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setFont1TestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont1(node_, &inputValueFont);
        WriteTo(inputValueFont).family = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont1, attribute: font.family";
    };
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setFont1TestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontStyleValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).style = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont1, attribute: font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFont1TestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFont1TestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_FontStyle& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont1(node_, &inputValueFont);
        WriteTo(inputValueFont).style = value;
        modifier_->setFont1(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont1, attribute: font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontColor0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontColor0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fontColor'";
}

/*
 * @tc.name: setFontColor1TestFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontColor1TestFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        inputValueFontColor = value;
        modifier_->setFontColor1(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontColor1, attribute: fontColor";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : testColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontColor1TestFontColorInvalidValues
 * @tc.desc: DISABLED due to result value is "#FF000000"  instead of "#7FAABBC3"
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontColor1TestFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        modifier_->setFontColor1(node_, &inputValueFontColor);
        inputValueFontColor = value;
        modifier_->setFontColor1(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontColor1, attribute: fontColor";
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
 * @tc.name: setSelectedOptionBgColor0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionBgColor0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionBgColor'";
}

/*
 * @tc.name: setSelectedOptionBgColor1TestSelectedOptionBgColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionBgColor1TestSelectedOptionBgColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionBgColor;

    // Initial setup
    initValueSelectedOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionBgColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionBgColor = initValueSelectedOptionBgColor;

        inputValueSelectedOptionBgColor = value;
        modifier_->setSelectedOptionBgColor1(node_, &inputValueSelectedOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionBgColor1, attribute: selectedOptionBgColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : testColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedOptionBgColor1TestSelectedOptionBgColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionBgColor1TestSelectedOptionBgColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionBgColor;

    // Initial setup
    initValueSelectedOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionBgColor](
                          const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionBgColor = initValueSelectedOptionBgColor;

        modifier_->setSelectedOptionBgColor1(node_, &inputValueSelectedOptionBgColor);
        inputValueSelectedOptionBgColor = value;
        modifier_->setSelectedOptionBgColor1(node_, &inputValueSelectedOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionBgColor1, attribute: selectedOptionBgColor";
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
 * @tc.name: setSelectedOptionFont0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSelectedOptionFont =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionFont.size'";

    resultStr = GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionFont.weight'";

    resultStr = GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionFont.family'";

    resultStr = GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionFont.style'";
}

/*
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontSizeValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).size = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;

    // Initial setup
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const Opt_Length& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).size = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontWeightValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_Number_String& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).weight = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.weight";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : testWeightNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : testWeightStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).weight = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.weight";
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
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontFamilyValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).family = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : testStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).family = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.family";
    };
     // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontStyleValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;

    // Initial setup
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).style = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFont1TestSelectedOptionFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFont1TestSelectedOptionFontStyleInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;

    // Initial setup
    WriteTo(initValueSelectedOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const Opt_FontStyle& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).style = value;
        modifier_->setSelectedOptionFont1(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont1, attribute: selectedOptionFont.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFontColor0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontColor0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionFontColor'";
}

/*
 * @tc.name: setSelectedOptionFontColor1TestSelectedOptionFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontColor1TestSelectedOptionFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionFontColor;

    // Initial setup
    initValueSelectedOptionFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFontColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionFontColor = initValueSelectedOptionFontColor;

        inputValueSelectedOptionFontColor = value;
        modifier_->setSelectedOptionFontColor1(node_, &inputValueSelectedOptionFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setSelectedOptionFontColor1, attribute: selectedOptionFontColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : testColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFontColor1TestSelectedOptionFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontColor1TestSelectedOptionFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionFontColor;

    // Initial setup
    initValueSelectedOptionFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFontColor](
                          const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionFontColor = initValueSelectedOptionFontColor;

        modifier_->setSelectedOptionFontColor1(node_, &inputValueSelectedOptionFontColor);
        inputValueSelectedOptionFontColor = value;
        modifier_->setSelectedOptionFontColor1(node_, &inputValueSelectedOptionFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setSelectedOptionFontColor1, attribute: selectedOptionFontColor";
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
 * @tc.name: setOptionBgColor0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionBgColor0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_BG_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_BG_COLOR_DEFAULT_VALUE) << "Default value for attribute 'optionBgColor'";
}

/*
 * @tc.name: setOptionBgColor1TestOptionBgColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionBgColor1TestOptionBgColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueOptionBgColor;

    // Initial setup
    initValueOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueOptionBgColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueOptionBgColor = initValueOptionBgColor;

        inputValueOptionBgColor = value;
        modifier_->setOptionBgColor1(node_, &inputValueOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionBgColor1, attribute: optionBgColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : testColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setOptionBgColor1TestOptionBgColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionBgColor1TestOptionBgColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueOptionBgColor;

    // Initial setup
    initValueOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueOptionBgColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueOptionBgColor = initValueOptionBgColor;

        modifier_->setOptionBgColor1(node_, &inputValueOptionBgColor);
        inputValueOptionBgColor = value;
        modifier_->setOptionBgColor1(node_, &inputValueOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_BG_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionBgColor1, attribute: optionBgColor";
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

} // namespace OHOS::Ace::NG
