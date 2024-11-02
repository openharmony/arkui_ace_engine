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

#include "core/components/text/text_theme.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_TEXT_SHADOW_NAME = "textShadow";
const auto ATTRIBUTE_TIME_ZONE_OFFSET_NAME = "timeZoneOffset";
const auto ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_CONTROLLER_NAME = "controller";
const auto ATTRIBUTE_CONTROLLER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FORMAT_NAME = "format";
const auto ATTRIBUTE_FORMAT_DEFAULT_VALUE = "aa hh:mm:ss";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "Harmony"
                                                 "OS Sans";
const auto ATTRIBUTE_TEXT_SHADOW_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_SHADOW_RADIUS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_TYPE_NAME = "type";
const auto ATTRIBUTE_TEXT_SHADOW_TYPE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_SHADOW_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TEXT_SHADOW_OFFSET_X_NAME = "offsetX";
const auto ATTRIBUTE_TEXT_SHADOW_OFFSET_X_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_OFFSET_Y_NAME = "offsetY";
const auto ATTRIBUTE_TEXT_SHADOW_OFFSET_Y_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_FILL_NAME = "fill";
const auto ATTRIBUTE_TEXT_SHADOW_FILL_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_FEATURE_NAME = "fontFeature";
const auto ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_DATE_TIME_OPTIONS_NAME = "dateTimeOptions";
const auto ATTRIBUTE_DATE_TIME_OPTIONS_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class TextClockModifierTest : public ModifierTestBase<GENERATED_ArkUITextClockModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextClockModifier, GENERATED_ARKUI_TEXT_CLOCK> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setTextClockOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextClockOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'options.timeZoneOffset'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROLLER_DEFAULT_VALUE) << "Default value for attribute 'options.controller'";
}

/*
 * @tc.name: setTextClockOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextClockOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setFormatTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFormatTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FORMAT_DEFAULT_VALUE) << "Default value for attribute 'format'";
}

/*
 * @tc.name: setFormatTestFormatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFormatTestFormatValidValues, TestSize.Level1)
{
    Ark_String initValueFormat;

    // Initial setup
    initValueFormat = std::get<1>(Fixtures::testFixtureTimeFormatValidValues[0]);

    auto checkValue = [this, &initValueFormat](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueFormat = initValueFormat;

        inputValueFormat = value;
        modifier_->setFormat(node_, &inputValueFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTimeFormatValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFormatTestFormatInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFormatTestFormatInvalidValues, TestSize.Level1)
{
    Ark_String initValueFormat;

    // Initial setup
    initValueFormat = std::get<1>(Fixtures::testFixtureTimeFormatValidValues[0]);

    auto checkValue = [this, &initValueFormat](const std::string& input, const Ark_String& value) {
        Ark_String inputValueFormat = initValueFormat;

        modifier_->setFormat(node_, &inputValueFormat);
        inputValueFormat = value;
        modifier_->setFormat(node_, &inputValueFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FORMAT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value] : Fixtures::testFixtureTimeFormatInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontColorTestFontColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontColorTestFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, DISABLED_setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
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
        checkValue(input, Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(
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
        checkValue(input, Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setFontFamilyTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextClockModifierTest, setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily = Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

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
        checkValue(input, Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceStr, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily = Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

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
        checkValue(input, Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextShadow =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_RADIUS_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..radius'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_TYPE_DEFAULT_VALUE) << "Default value for attribute 'textShadow..type'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..color'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_OFFSET_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_OFFSET_X_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..offsetX'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_OFFSET_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_OFFSET_Y_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..offsetY'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_FILL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_FILL_DEFAULT_VALUE) << "Default value for attribute 'textShadow..fill'";
}

/*
 * @tc.name: setTextShadowTestTextShadowRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowRadiusValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..radius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowRadiusInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_RADIUS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..radius";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowTypeValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_ShadowType& value, const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumShadowTypeValidValues) {
        checkValue(input, Converter::ArkValue<Opt_ShadowType>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowTypeInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_ShadowType& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_TYPE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumShadowTypeInvalidValues) {
        checkValue(input, Converter::ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowColorValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input,
                          const Opt_Union_Color_String_Resource_ColoringStrategy& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColorValidValues) {
        checkValue(
            input, Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColoringStrategyValidValues) {
        checkValue(input,
            Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value),
            expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(
            input, Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowColorInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Union_Color_String_Resource_ColoringStrategy& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..color";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumColorInvalidValues) {
        checkValue(input, Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    for (auto& [input, value] : Fixtures::testFixtureEnumColoringStrategyInvalidValues) {
        checkValue(
            input, Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
    // Check invalid union
    checkValue(
        "invalid union", Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>());
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowOffsetXValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowOffsetXInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_OFFSET_X_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetX";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowOffsetYValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowOffsetYInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_OFFSET_Y_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetY";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowFillValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowFillValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_FILL_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..fill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, Converter::ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowFillInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowFillInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        Converter::ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Boolean& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_FILL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_FILL_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..fill";
    };

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFontFeatureTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontFeatureTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE) << "Default value for attribute 'fontFeature'";
}

/*
 * @tc.name: setFontFeatureTestFontFeatureValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontFeatureTestFontFeatureValidValues, TestSize.Level1)
{
    Ark_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = std::get<1>(Fixtures::testFixtureFontFeatureValidValues[0]);

    auto checkValue = [this, &initValueFontFeature](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueFontFeature = initValueFontFeature;

        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFeatureValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFontFeatureTestFontFeatureInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontFeatureTestFontFeatureInvalidValues, TestSize.Level1)
{
    Ark_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = std::get<1>(Fixtures::testFixtureFontFeatureValidValues[0]);

    auto checkValue = [this, &initValueFontFeature](const std::string& input, const Ark_String& value) {
        Ark_String inputValueFontFeature = initValueFontFeature;

        modifier_->setFontFeature(node_, &inputValueFontFeature);
        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFeatureInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDateTimeOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setDateTimeOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DATE_TIME_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATE_TIME_OPTIONS_DEFAULT_VALUE) << "Default value for attribute 'dateTimeOptions'";
}

/*
 * @tc.name: setDateTimeOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setDateTimeOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}
} // namespace OHOS::Ace::NG
