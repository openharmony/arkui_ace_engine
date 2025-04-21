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

std::vector<std::tuple<std::string, Ark_MenuAlignType>> testInvalidValues = {
    { "-1", static_cast<Ark_MenuAlignType>(-1) },
    { "INT_MAX", static_cast<Ark_MenuAlignType>(INT_MAX) },
};
std::vector<std::tuple<std::string, Ark_ArrowPosition, std::string>> testArrowPositionValidValues = {
    { "ARK_ARROW_POSITION_END", ARK_ARROW_POSITION_END, "ArrowPosition.END" },
    { "ARK_ARROW_POSITION_START", ARK_ARROW_POSITION_START, "ArrowPosition.START" },
};

std::vector<std::tuple<std::string, Ark_MenuAlignType, std::string>> testMenuAlignTypeValidValues = {
    { "ARK_MENU_ALIGN_TYPE_START", ARK_MENU_ALIGN_TYPE_START, "MenuAlignType.Start" },
    { "ARK_MENU_ALIGN_TYPE_CENTER", ARK_MENU_ALIGN_TYPE_CENTER, "MenuAlignType.Center" },
    { "ARK_MENU_ALIGN_TYPE_END", ARK_MENU_ALIGN_TYPE_END, "MenuAlignType.End" },
};

typedef std::pair<Ark_Length, double> OneTestStep;
static const std::vector<OneTestStep> offsetTestPlan = {
    { Converter::ArkValue<Ark_Length>(2.5f), 2.5 },
    { Converter::ArkValue<Ark_Length>(-2.5f), -2.5 },
    { Converter::ArkValue<Ark_Length>(5.0_px), 5 },
    { Converter::ArkValue<Ark_Length>(-5.0_px), -5 },
    { Converter::ArkValue<Ark_Length>(22.5_px), 22.5 },
    { Converter::ArkValue<Ark_Length>(-22.5_px), -22.5 },
    { Converter::ArkValue<Ark_Length>(7.0_vp), 7 },
    { Converter::ArkValue<Ark_Length>(-7.0_vp), -7 },
    { Converter::ArkValue<Ark_Length>(1.5_vp), 1.5 },
    { Converter::ArkValue<Ark_Length>(-1.5_vp), -1.5 },
    { Converter::ArkValue<Ark_Length>(65.0_fp), 65 },
    { Converter::ArkValue<Ark_Length>(-65.0_fp), -65 },
    { Converter::ArkValue<Ark_Length>(4.5_fp), 4.5 },
    { Converter::ArkValue<Ark_Length>(-4.5_fp), -4.5 },
    { Converter::ArkValue<Ark_Length>(0.12_pct), 0.12 },
    { Converter::ArkValue<Ark_Length>(-0.12_pct), -0.12 },
};

/*
 * @tc.name: setOptionFont1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFont1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultOptionFont =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_SIZE_DEFAULT_VALUE) << "Default value for attribute 'optionFont.size'";

    resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'optionFont.weight'";

    resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_FAMILY_DEFAULT_VALUE) <<
        "Default value for attribute 'optionFont.family'";

    resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'optionFont.style'";
}

/*
 * @tc.name: setOptionFont1TestOptionFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFont1TestOptionFontSizeValidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        WriteTo(inputValueOptionFont).size = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setOptionFont1TestOptionFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setOptionFont1TestOptionFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](const std::string& input, const Opt_Length& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        WriteTo(inputValueOptionFont).size = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setOptionFont1TestOptionFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFont1TestOptionFontWeightValidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_Number_String& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        WriteTo(inputValueOptionFont).weight = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.weight";
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
 * @tc.name: setOptionFont1TestOptionFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setOptionFont1TestOptionFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        WriteTo(inputValueOptionFont).weight = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.weight";
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
 * @tc.name: setOptionFont1TestOptionFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFont1TestOptionFontFamilyValidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        WriteTo(inputValueOptionFont).family = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    //todo Ark_Resource
}

/*
 * @tc.name: setOptionFont1TestOptionFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFont1TestOptionFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        WriteTo(inputValueOptionFont).family = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.family";
    };

//todo Ark_Resource
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setOptionFont1TestOptionFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFont1TestOptionFontStyleValidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        WriteTo(inputValueOptionFont).style = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setOptionFont1TestOptionFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFont1TestOptionFontStyleInvalidValues, TestSize.Level1)
{
    Opt_Font initValueOptionFont;

    // Initial setup
    WriteTo(initValueOptionFont).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueOptionFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueOptionFont).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptionFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueOptionFont](const std::string& input, const Opt_FontStyle& value) {
        Opt_Font inputValueOptionFont = initValueOptionFont;

        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        WriteTo(inputValueOptionFont).style = value;
        modifier_->setOptionFont1(node_, &inputValueOptionFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptionFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTION_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptionFont, ATTRIBUTE_OPTION_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionFont1, attribute: optionFont.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setOptionFontColor0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontColor0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'optionFontColor'";
}

/*
 * @tc.name: setOptionFontColor1TestOptionFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontColor1TestOptionFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueOptionFontColor;

    // Initial setup
    initValueOptionFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueOptionFontColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueOptionFontColor = initValueOptionFontColor;

        inputValueOptionFontColor = value;
        modifier_->setOptionFontColor1(node_, &inputValueOptionFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionFontColor1, attribute: optionFontColor";
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
 * @tc.name: setOptionFontColor1TestOptionFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontColor1TestOptionFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueOptionFontColor;

    // Initial setup
    initValueOptionFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueOptionFontColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueOptionFontColor = initValueOptionFontColor;

        modifier_->setOptionFontColor1(node_, &inputValueOptionFontColor);
        inputValueOptionFontColor = value;
        modifier_->setOptionFontColor1(node_, &inputValueOptionFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionFontColor1, attribute: optionFontColor";
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
 * @tc.name: setSpace0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSpace0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SPACE_DEFAULT_VALUE) << "Default value for attribute 'space'";
}

/*
 * @tc.name: setSpace1TestSpaceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSpace1TestSpaceValidValues, TestSize.Level1)
{
    Opt_Length initValueSpace;

    // Initial setup
    initValueSpace = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueSpace](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueSpace = initValueSpace;

        inputValueSpace = value;
        modifier_->setSpace1(node_, &inputValueSpace);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SPACE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setSpace1, attribute: space";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setSpace1TestSpaceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSpace1TestSpaceInvalidValues, TestSize.Level1)
{
    Opt_Length initValueSpace;

    // Initial setup
    initValueSpace = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueSpace](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueSpace = initValueSpace;

        modifier_->setSpace1(node_, &inputValueSpace);
        inputValueSpace = value;
        modifier_->setSpace1(node_, &inputValueSpace);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SPACE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SPACE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSpace1, attribute: space";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setArrowPosition1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setArrowPosition1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ARROW_POSITION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ARROW_POSITION_DEFAULT_VALUE) << "Default value for attribute 'arrowPosition'";
}

/*
 * @tc.name: setArrowPosition1TestArrowPositionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setArrowPosition1TestArrowPositionValidValues, TestSize.Level1)
{
    Opt_ArrowPosition initValueArrowPosition;

    // Initial setup
    initValueArrowPosition =
        ArkValue<Opt_ArrowPosition>(Ark_ArrowPosition::ARK_ARROW_POSITION_START);

    auto checkValue = [this, &initValueArrowPosition](
                          const std::string& input, const std::string& expectedStr, const Opt_ArrowPosition& value) {
        Opt_ArrowPosition inputValueArrowPosition = initValueArrowPosition;

        inputValueArrowPosition = value;
        modifier_->setArrowPosition1(node_, &inputValueArrowPosition);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ARROW_POSITION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setArrowPosition1, attribute: arrowPosition";
    };
    checkValue("ARK_ARROW_POSITION_START", "ArrowPosition.START",
        ArkValue<Opt_ArrowPosition>(Ark_ArrowPosition::ARK_ARROW_POSITION_START));
    checkValue("ARK_ARROW_POSITION_END", "ArrowPosition.END",
        ArkValue<Opt_ArrowPosition>(Ark_ArrowPosition::ARK_ARROW_POSITION_END));
}

/*
 * @tc.name: setArrowPosition1TestArrowPositionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setArrowPosition1TestArrowPositionInvalidValues, TestSize.Level1)
{
    Opt_ArrowPosition initValueArrowPosition;

    // Initial setup
    initValueArrowPosition =
        ArkValue<Opt_ArrowPosition>(Ark_ArrowPosition::ARK_ARROW_POSITION_START);

    auto checkValue = [this, &initValueArrowPosition](const std::string& input, const Opt_ArrowPosition& value) {
        Opt_ArrowPosition inputValueArrowPosition = initValueArrowPosition;

        modifier_->setArrowPosition1(node_, &inputValueArrowPosition);
        inputValueArrowPosition = value;
        modifier_->setArrowPosition1(node_, &inputValueArrowPosition);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ARROW_POSITION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ARROW_POSITION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setArrowPosition1, attribute: arrowPosition";
    };
    std::vector<std::tuple<std::string, Ark_ArrowPosition>> testInvalidValues = {
        { "-1", static_cast<Ark_ArrowPosition>(-1) },
        { "INT_MAX", static_cast<Ark_ArrowPosition>(INT_MAX) },
    };
    for (auto& [input, value] : testInvalidValues) {
        checkValue(input, ArkValue<Opt_ArrowPosition>(value));
    }
}

/*
 * @tc.name: setOptionWidth1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionWidth1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'optionWidth'";
}

/*
 * @tc.name: setOptionWidth1TestOptionWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionWidth1TestOptionWidthValidValues, TestSize.Level1)
{
    Opt_Union_Dimension_OptionWidthMode initValueOptionWidth;
    initValueOptionWidth = ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(
        Ark_OptionWidthMode::ARK_OPTION_WIDTH_MODE_FIT_TRIGGER);
    auto checkValue = [this, &initValueOptionWidth](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Dimension_OptionWidthMode& value) {
        Opt_Union_Dimension_OptionWidthMode inputValueOptionWidth = initValueOptionWidth;
        inputValueOptionWidth = value;
        modifier_->setOptionWidth1(node_, &inputValueOptionWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionWidth1, attribute: optionWidth";
    };
    checkValue("ARK_OPTION_WIDTH_MODE_FIT_TRIGGER", "OptionWidthMode.FIT_TRIGGER",
        ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(
        Ark_OptionWidthMode::ARK_OPTION_WIDTH_MODE_FIT_TRIGGER));
    auto initialWidth = "0.000000";
    checkValue("ARK_OPTION_WIDTH_MODE_FIT_CONTENT", initialWidth,
        ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(
        Ark_OptionWidthMode::ARK_OPTION_WIDTH_MODE_FIT_CONTENT));

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthPositivelValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_Length>(value));
    }
    auto lastSetWidth = "1.230000";
    checkValue("ARK_OPTION_WIDTH_MODE_FIT_CONTENT", lastSetWidth,
        ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(
        Ark_OptionWidthMode::ARK_OPTION_WIDTH_MODE_FIT_CONTENT));
}

/*
 * @tc.name: setOptionWidth1TestOptionWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionWidth1TestOptionWidthInvalidValues, TestSize.Level1)
{
    Opt_Union_Dimension_OptionWidthMode initValueOptionWidth;

    // Initial setup
    initValueOptionWidth = ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(
        Ark_OptionWidthMode::ARK_OPTION_WIDTH_MODE_FIT_TRIGGER);

    auto checkValue = [this, &initValueOptionWidth](
                          const std::string& input, const Opt_Union_Dimension_OptionWidthMode& value) {
        Opt_Union_Dimension_OptionWidthMode inputValueOptionWidth = initValueOptionWidth;

        modifier_->setOptionWidth1(node_, &inputValueOptionWidth);
        inputValueOptionWidth = value;
        modifier_->setOptionWidth1(node_, &inputValueOptionWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionWidth1, attribute: optionWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_Length>(value));
    }
    std::vector<std::tuple<std::string, Ark_OptionWidthMode>> testInvalidValues = {
        { "-1", static_cast<Ark_OptionWidthMode>(-1) },
        { "INT_MAX", static_cast<Ark_OptionWidthMode>(INT_MAX) },
    };
    for (auto& [input, value] : testInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Dimension_OptionWidthMode, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Dimension_OptionWidthMode>());
}

/*
 * @tc.name: setOptionHeight1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionHeight1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'optionHeight'";
}

/*
 * @tc.name: setOptionHeight1TestOptionHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionHeight1TestOptionHeightValidValues, TestSize.Level1)
{
    Opt_Length initValueOptionHeight;

    // Initial setup
    initValueOptionHeight = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueOptionHeight](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueOptionHeight = initValueOptionHeight;

        inputValueOptionHeight = value;
        modifier_->setOptionHeight1(node_, &inputValueOptionHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptionHeight1, attribute: optionHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthPositivelValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setOptionHeight1TestOptionHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setOptionHeight1TestOptionHeightInvalidValues, TestSize.Level1)
{
    Opt_Length initValueOptionHeight;

    // Initial setup
    initValueOptionHeight = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueOptionHeight](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueOptionHeight = initValueOptionHeight;

        modifier_->setOptionHeight1(node_, &inputValueOptionHeight);
        inputValueOptionHeight = value;
        modifier_->setOptionHeight1(node_, &inputValueOptionHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTION_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTION_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOptionHeight1, attribute: optionHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setMenuBackgroundColor1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundColor1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MENU_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MENU_BACKGROUND_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'menuBackgroundColor'";
}

/*
 * @tc.name: setMenuBackgroundColor1TestMenuBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundColor1TestMenuBackgroundColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueMenuBackgroundColor;

    // Initial setup
    initValueMenuBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueMenuBackgroundColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueMenuBackgroundColor = initValueMenuBackgroundColor;

        inputValueMenuBackgroundColor = value;
        modifier_->setMenuBackgroundColor1(node_, &inputValueMenuBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MENU_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMenuBackgroundColor1, attribute: menuBackgroundColor";
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
 * @tc.name: setMenuBackgroundColor1TestMenuBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setMenuBackgroundColor1TestMenuBackgroundColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueMenuBackgroundColor;

    // Initial setup
    initValueMenuBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueMenuBackgroundColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueMenuBackgroundColor = initValueMenuBackgroundColor;

        modifier_->setMenuBackgroundColor1(node_, &inputValueMenuBackgroundColor);
        inputValueMenuBackgroundColor = value;
        modifier_->setMenuBackgroundColor1(node_, &inputValueMenuBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MENU_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MENU_BACKGROUND_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMenuBackgroundColor1, attribute: menuBackgroundColor";
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
 * @tc.name: setMenuBackgroundBlurStyle1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundBlurStyle1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MENU_BACKGROUND_BLUR_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MENU_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'menuBackgroundBlurStyle'";
}

/*
 * @tc.name: setMenuBackgroundBlurStyle1TestMenuBackgroundBlurStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundBlurStyle1TestMenuBackgroundBlurStyleValidValues, TestSize.Level1)
{
    Opt_BlurStyle initValueMenuBackgroundBlurStyle;

    // Initial setup
    initValueMenuBackgroundBlurStyle =
        ArkValue<Opt_BlurStyle>(std::get<1>(Fixtures::testFixtureEnumBlurStyleValidValues[0]));

    auto checkValue = [this, &initValueMenuBackgroundBlurStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_BlurStyle& value) {
        Opt_BlurStyle inputValueMenuBackgroundBlurStyle = initValueMenuBackgroundBlurStyle;

        inputValueMenuBackgroundBlurStyle = value;
        modifier_->setMenuBackgroundBlurStyle1(node_, &inputValueMenuBackgroundBlurStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MENU_BACKGROUND_BLUR_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setMenuBackgroundBlurStyle1, attribute: menuBackgroundBlurStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumBlurStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_BlurStyle>(value));
    }
}

/*
 * @tc.name: setMenuBackgroundBlurStyle1TestMenuBackgroundBlurStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setMenuBackgroundBlurStyle1TestMenuBackgroundBlurStyleInvalidValues,
    TestSize.Level1)
{
    Opt_BlurStyle initValueMenuBackgroundBlurStyle;

    // Initial setup
    initValueMenuBackgroundBlurStyle =
        ArkValue<Opt_BlurStyle>(std::get<1>(Fixtures::testFixtureEnumBlurStyleValidValues[0]));

    auto checkValue = [this, &initValueMenuBackgroundBlurStyle](const std::string& input, const Opt_BlurStyle& value) {
        Opt_BlurStyle inputValueMenuBackgroundBlurStyle = initValueMenuBackgroundBlurStyle;

        modifier_->setMenuBackgroundBlurStyle1(node_, &inputValueMenuBackgroundBlurStyle);
        inputValueMenuBackgroundBlurStyle = value;
        modifier_->setMenuBackgroundBlurStyle1(node_, &inputValueMenuBackgroundBlurStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MENU_BACKGROUND_BLUR_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MENU_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setMenuBackgroundBlurStyle1, attribute: menuBackgroundBlurStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumBlurStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_BlurStyle>(value));
    }
}

/*
 * @tc.name: setControlSize1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setControlSize1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) << "Default value for attribute 'controlSize'";
}

/*
 * @tc.name: setControlSize1TestControlSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setControlSize1TestControlSizeValidValues, TestSize.Level1)
{
    Opt_ControlSize initValueControlSize;

    // Initial setup
    initValueControlSize = ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));

    auto checkValue = [this, &initValueControlSize](
                          const std::string& input, const std::string& expectedStr, const Opt_ControlSize& value) {
        Opt_ControlSize inputValueControlSize = initValueControlSize;

        inputValueControlSize = value;
        modifier_->setControlSize1(node_, &inputValueControlSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setControlSize1, attribute: controlSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumControlSizeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setControlSize1TestControlSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setControlSize1TestControlSizeInvalidValues, TestSize.Level1)
{
    Opt_ControlSize initValueControlSize;

    // Initial setup
    initValueControlSize = ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));

    auto checkValue = [this, &initValueControlSize](const std::string& input, const Opt_ControlSize& value) {
        Opt_ControlSize inputValueControlSize = initValueControlSize;

        modifier_->setControlSize1(node_, &inputValueControlSize);
        inputValueControlSize = value;
        modifier_->setControlSize1(node_, &inputValueControlSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setControlSize1, attribute: controlSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumControlSizeInvalidValues) {
        checkValue(input, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setMenuAlign1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuAlign1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMenuAlign =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MENU_ALIGN_NAME);
    std::unique_ptr<JsonValue> resultOffset =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultMenuAlign, ATTRIBUTE_MENU_ALIGN_I_OFFSET_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMenuAlign, ATTRIBUTE_MENU_ALIGN_I_ALIGN_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MENU_ALIGN_I_ALIGN_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'menuAlign.alignType'";

    resultStr = GetAttrValue<std::string>(resultOffset, ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DX_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DX_DEFAULT_VALUE) <<
        "Default value for attribute 'menuAlign.offset.dx'";

    resultStr = GetAttrValue<std::string>(resultOffset, ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DY_DEFAULT_VALUE) <<
        "Default value for attribute 'menuAlign.offset.dy'";
}

/*
 * @tc.name: setMenuAlign1TestMenuAlignAlignTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuAlign1TestMenuAlignAlignTypeValidValues, TestSize.Level1)
{
    Opt_MenuAlignType initValueAlignType;
    Opt_Offset initValueOffset;

    // Initial setup
    initValueAlignType = ArkValue<Opt_MenuAlignType>(std::get<1>(testMenuAlignTypeValidValues[0]));
    WriteTo(initValueOffset).dx = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValueOffset).dy = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueAlignType, &initValueOffset](
                          const std::string& input, const std::string& expectedStr, const Opt_MenuAlignType& value) {
        Opt_MenuAlignType inputValueAlignType = initValueAlignType;
        Opt_Offset inputValueOffset = initValueOffset;

        inputValueAlignType = value;
        modifier_->setMenuAlign1(node_, &inputValueAlignType, &inputValueOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultMenuAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MENU_ALIGN_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMenuAlign, ATTRIBUTE_MENU_ALIGN_I_ALIGN_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMenuAlign1, attribute: menuAlign.alignType";
    };

    for (auto& [input, value, expected] : testMenuAlignTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_MenuAlignType>(value));
    }
}

/*
 * @tc.name: setMenuAlign1TestMenuAlignAlignTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuAlign1TestMenuAlignAlignTypeInvalidValues, TestSize.Level1)
{
    Opt_MenuAlignType initValueAlignType;
    Opt_Offset initValueOffset;

    // Initial setup
    initValueAlignType = ArkValue<Opt_MenuAlignType>(std::get<1>(testMenuAlignTypeValidValues[0]));
    WriteTo(initValueOffset).dx = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValueOffset).dy = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueAlignType, &initValueOffset](
                          const std::string& input, const Opt_MenuAlignType& value) {
        Opt_MenuAlignType inputValueAlignType = initValueAlignType;
        Opt_Offset inputValueOffset = initValueOffset;

        modifier_->setMenuAlign1(node_, &inputValueAlignType, &inputValueOffset);
        inputValueAlignType = value;
        modifier_->setMenuAlign1(node_, &inputValueAlignType, &inputValueOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultMenuAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MENU_ALIGN_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMenuAlign, ATTRIBUTE_MENU_ALIGN_I_ALIGN_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MENU_ALIGN_I_ALIGN_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMenuAlign1, attribute: menuAlign.alignType";
    };
    std::vector<std::tuple<std::string, Ark_MenuAlignType>> testAlignTypeInvalidValues = {
        { "-1", static_cast<Ark_MenuAlignType>(-1) },
        { "INT_MAX", static_cast<Ark_MenuAlignType>(INT_MAX) },
    };
    for (auto& [input, value] : testAlignTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_MenuAlignType>(value));
    }
}

/*
 * @tc.name: setMenuAlign1TestMenuAlignOffsetDxValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuAlign1TestMenuAlignOffsetDxValidValues, TestSize.Level1)
{
    Opt_MenuAlignType initValueAlignType;
    Opt_Offset initValueOffset;

    // Initial setup
    initValueAlignType = ArkValue<Opt_MenuAlignType>(std::get<1>(testMenuAlignTypeValidValues[0]));
    WriteTo(initValueOffset).dx = Converter::ArkValue<Ark_Length>(0.0f);
    WriteTo(initValueOffset).dy = Converter::ArkValue<Ark_Length>(0.0f);

    auto checkValue = [this, &initValueAlignType, &initValueOffset](
                            const double expected, const Ark_Length& value) {
        Opt_MenuAlignType inputValueAlignType = initValueAlignType;
        Opt_Offset inputValueOffset = initValueOffset;

        WriteTo(inputValueOffset).dx = value;
        modifier_->setMenuAlign1(node_, &inputValueAlignType, &inputValueOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultMenuAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MENU_ALIGN_NAME);
        auto resultOffset =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultMenuAlign, ATTRIBUTE_MENU_ALIGN_I_OFFSET_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOffset, ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DX_NAME);
        EXPECT_FLOAT_EQ(std::stof(resultStr), expected);
    };

    for (auto& [value, expected] : offsetTestPlan) {
        checkValue(expected, value);
    }
}

/*
 * @tc.name: setMenuAlign1TestMenuAlignOffsetDyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuAlign1TestMenuAlignOffsetDyValidValues, TestSize.Level1)
{
    Opt_MenuAlignType initValueAlignType;
    Opt_Offset initValueOffset;

    // Initial setup
    initValueAlignType = ArkValue<Opt_MenuAlignType>(std::get<1>(testMenuAlignTypeValidValues[0]));
    WriteTo(initValueOffset).dx = Converter::ArkValue<Ark_Length>(0.0f);
    WriteTo(initValueOffset).dy = Converter::ArkValue<Ark_Length>(0.0f);
    auto checkValue = [this, &initValueAlignType, &initValueOffset](
                            const double expected, const Ark_Length& value) {
        Opt_MenuAlignType inputValueAlignType = initValueAlignType;
        Opt_Offset inputValueOffset = initValueOffset;

        WriteTo(inputValueOffset).dy = value;
        modifier_->setMenuAlign1(node_, &inputValueAlignType, &inputValueOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultMenuAlign = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MENU_ALIGN_NAME);
        auto resultOffset =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultMenuAlign, ATTRIBUTE_MENU_ALIGN_I_OFFSET_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOffset, ATTRIBUTE_MENU_ALIGN_I_OFFSET_I_DY_NAME);
        EXPECT_FLOAT_EQ(std::stof(resultStr), expected);
    };

    for (auto& [value, expected] : offsetTestPlan) {
        checkValue(expected, value);
    }
}
} // namespace OHOS::Ace::NG
