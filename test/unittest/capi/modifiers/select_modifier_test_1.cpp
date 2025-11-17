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

std::vector<std::tuple<std::string, Ark_Int32, std::string>> testWeightNumberValidValues = {
    { "\"100\"", Converter::ArkValue<Ark_Int32>(100), "100" },
    { "\"200\"", Converter::ArkValue<Ark_Int32>(200), "200" },
    { "\"300\"", Converter::ArkValue<Ark_Int32>(300), "300" },
    { "\"400\"", Converter::ArkValue<Ark_Int32>(400), "400" },
    { "\"500\"", Converter::ArkValue<Ark_Int32>(500), "500" },
    { "\"600\"", Converter::ArkValue<Ark_Int32>(600), "600" },
    { "\"700\"", Converter::ArkValue<Ark_Int32>(700), "700" },
    { "\"800\"", Converter::ArkValue<Ark_Int32>(800), "800" },
    { "\"900\"", Converter::ArkValue<Ark_Int32>(900), "900" },
};

std::vector<std::tuple<std::string, Ark_Resource, std::string>> testIntResValidValues = {
    { "ResId:INT_RES_0_ID", CreateResource(INT_RES_0_STR, ResourceType::INTEGER), "0" },
    { "ResId:INT_RES_1_ID", CreateResource(INT_RES_1_STR, ResourceType::INTEGER), "1" },
    { "ResName:INT_RES_2_STR", CreateResource(INT_RES_2_STR, ResourceType::INTEGER), "12" },
    { "ResId:INT_RES_3_ID", CreateResource(INT_RES_3_STR, ResourceType::INTEGER), "123" },
    { "ResName:INT_RES_4_STR", CreateResource(INT_RES_4_STR, ResourceType::INTEGER), "1234" },
    { "ResId:INT_RES_5_ID", CreateResource(INT_RES_5_STR, ResourceType::INTEGER), "12345" },
    { "ResName:INT_RES_6_STR", CreateResource(INT_RES_6_STR, ResourceType::INTEGER), "123456" },
};
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testStringResValidValues = {
    { "ResId:STR_RES_0_ID", CreateResource(STR_RES_0_ID, ResourceType::STRING), "abc" },
    { "ResName:STR_RES_0_STR", CreateResource(STR_RES_0_STR, ResourceType::STRING), "abc" },
    { "ResId:STR_RES_1_ID", CreateResource(STR_RES_1_ID, ResourceType::STRING), "" },
    { "ResName:STR_RES_1_STR", CreateResource(STR_RES_1_STR, ResourceType::STRING), "" },
};
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testColorsResValidValues = {
    { "ResId:COLOR_RES_0_ID", CreateResource(COLOR_RES_0_ID, ResourceType::COLOR), "#A1FAC0DE" },
    { "ResName:COLOR_RES_0_STR", CreateResource(COLOR_RES_0_STR, ResourceType::COLOR), "#A1FAC0DE" },
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
 * @tc.name: setSelectedTestSelectedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedTestSelectedValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource_Bindable_Bindable& value) {
        auto inputValueSelected = value;
        modifier_->setSelected(node_, &inputValueSelected);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelected, attribute: selected";
    };
// we can check only empty selection, i.e. 0 and 1 indexes
    for (auto& [input, value, expected] : testNumberNonNegIntValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource_Bindable_Bindable, Ark_Number>(value));
    }
    //todo add resource test
}

/*
 * @tc.name: setSelectedTestSelectedInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedTestSelectedInvalidValues, TestSize.Level1)
{
    auto initValueSelected = ArkUnion<Opt_Union_Number_Resource_Bindable_Bindable, Ark_Number>(
        std::get<1>(testNumberNonNegIntValidValues[0]));

    auto checkValue = [this, &initValueSelected](const std::string& input,
        const Opt_Union_Number_Resource_Bindable_Bindable& value) {
        auto inputValueSelected = initValueSelected;
        modifier_->setSelected(node_, &inputValueSelected);
        inputValueSelected = value;
        modifier_->setSelected(node_, &inputValueSelected);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelected, attribute: selected";
    };
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource_Bindable_Bindable, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource_Bindable_Bindable>());
    checkValue("-1", ArkUnion<Opt_Union_Number_Resource_Bindable_Bindable, Ark_Number>(-1));
}

/*
 * @tc.name: setValueTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setValueTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'value'";
}

/*
 * @tc.name: setValueTestValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setValueTestValueInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueValue = ArkUnion<Opt_Union_ResourceStr_Bindable_Bindable, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));

    auto checkValue = [this, &initValueValue](const std::string& input, const Ark_ResourceStr& value) {
        auto inputValueValue = initValueValue;

        modifier_->setValue(node_, &inputValueValue);
        inputValueValue = ArkUnion<Opt_Union_ResourceStr_Bindable_Bindable, Ark_ResourceStr>(value);
        modifier_->setValue(node_, &inputValueValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setValue, attribute: value";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setFontTestDefaultValues, TestSize.Level1)
{
    modifier_->setFont(node_, nullptr);
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
 * @tc.name: setFontTestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestFontSizeValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).size = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setFontTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Length& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).size = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setFontTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestFontWeightValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_I32_String& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).weight = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFont, attribute: font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : testWeightNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : testWeightStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setFontTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const Opt_Union_FontWeight_I32_String& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).weight = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_I32_String>());
}

/*
 * @tc.name: setFontTestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestFontFamilyValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).family = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFont, attribute: font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : testStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setFontTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).family = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.family";
    };
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setFontTestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestFontStyleValidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).style = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_FontStyle& value) {
        Opt_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).style = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SelectModifierTest, DISABLED_setFontColorTestFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
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
 * @tc.name: setFontColorTestFontColorInvalidValues
 * @tc.desc: DISABLED due to result value is "#FF000000"  instead of "#7FAABBC3"
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        modifier_->setFontColor(node_, &inputValueFontColor);
        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
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
 * @tc.name: setSelectedOptionBgColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedOptionBgColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionBgColor'";
}

/*
 * @tc.name: setSelectedOptionBgColorTestSelectedOptionBgColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedOptionBgColorTestSelectedOptionBgColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionBgColor;

    // Initial setup
    initValueSelectedOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionBgColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionBgColor = initValueSelectedOptionBgColor;

        inputValueSelectedOptionBgColor = value;
        modifier_->setSelectedOptionBgColor(node_, &inputValueSelectedOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionBgColor, attribute: selectedOptionBgColor";
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
 * @tc.name: setSelectedOptionBgColorTestSelectedOptionBgColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedOptionBgColorTestSelectedOptionBgColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionBgColor;

    // Initial setup
    initValueSelectedOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionBgColor](
                          const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionBgColor = initValueSelectedOptionBgColor;

        modifier_->setSelectedOptionBgColor(node_, &inputValueSelectedOptionBgColor);
        inputValueSelectedOptionBgColor = value;
        modifier_->setSelectedOptionBgColor(node_, &inputValueSelectedOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_BG_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionBgColor, attribute: selectedOptionBgColor";
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
 * @tc.name: setSelectedOptionFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestDefaultValues, TestSize.Level1)
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
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestSelectedOptionFontSizeValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).size = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedOptionFontTestSelectedOptionFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;

    // Initial setup
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const Opt_Length& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).size = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestSelectedOptionFontWeightValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_I32_String& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).weight = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.weight";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : testWeightNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : testWeightStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedOptionFontTestSelectedOptionFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const Opt_Union_FontWeight_I32_String& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).weight = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_I32_String>());
}

/*
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestSelectedOptionFontFamilyValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).family = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : testStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestSelectedOptionFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).family = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.family";
    };
     // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestSelectedOptionFontStyleValidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;

    // Initial setup
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        WriteTo(inputValueSelectedOptionFont).style = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFontTestSelectedOptionFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestSelectedOptionFontStyleInvalidValues, TestSize.Level1)
{
    Opt_Font initValueSelectedOptionFont;

    // Initial setup
    WriteTo(initValueSelectedOptionFont).size =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueSelectedOptionFont).weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueSelectedOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueSelectedOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFont](const std::string& input, const Opt_FontStyle& value) {
        Opt_Font inputValueSelectedOptionFont = initValueSelectedOptionFont;

        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        WriteTo(inputValueSelectedOptionFont).style = value;
        modifier_->setSelectedOptionFont(node_, &inputValueSelectedOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelectedOptionFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultSelectedOptionFont, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedOptionFont, attribute: selectedOptionFont.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setSelectedOptionFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedOptionFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedOptionFontColor'";
}

/*
 * @tc.name: setSelectedOptionFontColorTestSelectedOptionFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setSelectedOptionFontColorTestSelectedOptionFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionFontColor;

    // Initial setup
    initValueSelectedOptionFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFontColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionFontColor = initValueSelectedOptionFontColor;

        inputValueSelectedOptionFontColor = value;
        modifier_->setSelectedOptionFontColor(node_, &inputValueSelectedOptionFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input <<
            ", method: setSelectedOptionFontColor, attribute: selectedOptionFontColor";
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
 * @tc.name: setSelectedOptionFontColorTestSelectedOptionFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontColorTestSelectedOptionFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedOptionFontColor;

    // Initial setup
    initValueSelectedOptionFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedOptionFontColor](
                          const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedOptionFontColor = initValueSelectedOptionFontColor;

        modifier_->setSelectedOptionFontColor(node_, &inputValueSelectedOptionFontColor);
        inputValueSelectedOptionFontColor = value;
        modifier_->setSelectedOptionFontColor(node_, &inputValueSelectedOptionFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_OPTION_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input <<
            ", method: setSelectedOptionFontColor, attribute: selectedOptionFontColor";
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
 * @tc.name: setOptionBgColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionBgColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_BG_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_BG_COLOR_DEFAULT_VALUE) << "Default value for attribute 'optionBgColor'";
}

/*
 * @tc.name: setOptionBgColorTestOptionBgColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setOptionBgColorTestOptionBgColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueOptionBgColor;

    // Initial setup
    initValueOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueOptionBgColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueOptionBgColor = initValueOptionBgColor;

        inputValueOptionBgColor = value;
        modifier_->setOptionBgColor(node_, &inputValueOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionBgColor, attribute: optionBgColor";
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
 * @tc.name: setOptionBgColorTestOptionBgColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setOptionBgColorTestOptionBgColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueOptionBgColor;

    // Initial setup
    initValueOptionBgColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueOptionBgColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueOptionBgColor = initValueOptionBgColor;

        modifier_->setOptionBgColor(node_, &inputValueOptionBgColor);
        inputValueOptionBgColor = value;
        modifier_->setOptionBgColor(node_, &inputValueOptionBgColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_BG_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_BG_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionBgColor, attribute: optionBgColor";
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
