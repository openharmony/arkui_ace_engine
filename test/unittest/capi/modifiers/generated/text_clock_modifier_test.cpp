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

#include "core/components/text/text_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_TEXT_SHADOW_NAME = "textShadow";
const auto ATTRIBUTE_TIME_ZONE_OFFSET_NAME = "timeZoneOffset";
const auto ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE = "0.000000";
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
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME = "type";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME = "offsetX";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME = "offsetY";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME = "fill";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_FEATURE_NAME = "fontFeature";
const auto ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE = "";
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
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE) <<
        "Default value for attribute 'options.timeZoneOffset'";
}

/*
 * @tc.name: setTextClockOptionsTestOptionsTimeZoneOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextClockOptionsTestOptionsTimeZoneOffsetValidValues, TestSize.Level1)
{
    Opt_TextClockOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).timeZoneOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_TextClockOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).timeZoneOffset = value;
        modifier_->setTextClockOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextClockOptions, attribute: options.timeZoneOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setTextClockOptionsTestOptionsTimeZoneOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestOptionsTimeZoneOffsetInvalidValues, TestSize.Level1)
{
    Opt_TextClockOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).timeZoneOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Opt_TextClockOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).timeZoneOffset = value;
        modifier_->setTextClockOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextClockOptions, attribute: options.timeZoneOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
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
    Opt_ResourceStr initValueFormat;

    // Initial setup
    initValueFormat = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureTimeFormatValidValues[0]));

    auto checkValue = [this, &initValueFormat](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueFormat = initValueFormat;

        inputValueFormat = value;
        modifier_->setFormat(node_, &inputValueFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTimeFormatValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureTimeFormatResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setFormatTestFormatInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFormatTestFormatInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueFormat;

    // Initial setup
    initValueFormat = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureTimeFormatValidValues[0]));

    auto checkValue = [this, &initValueFormat](const std::string& input, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueFormat = initValueFormat;

        modifier_->setFormat(node_, &inputValueFormat);
        inputValueFormat = value;
        modifier_->setFormat(node_, &inputValueFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FORMAT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value] : Fixtures::testFixtureTimeFormatInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureTimeFormatResInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
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
HWTEST_F(TextClockModifierTest, DISABLED_setFontColorTestFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
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
 * @tc.name: setFontColorTestFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
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
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setFontSizeTestDefaultValues, TestSize.Level1)
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
    Opt_Length initValueFontSize;

    // Initial setup
    initValueFontSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueFontSize = initValueFontSize;

        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
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
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Length initValueFontSize;

    // Initial setup
    initValueFontSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
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
    Opt_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFontStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_FontStyle inputValueFontStyle = initValueFontStyle;

        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontStyleTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFontStyle](const std::string& input, const Opt_FontStyle& value) {
        Opt_FontStyle inputValueFontStyle = initValueFontStyle;

        modifier_->setFontStyle(node_, &inputValueFontStyle);
        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
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
    Opt_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight(node_, &inputValueFontWeight);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_FontWeight_String>());
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontFamilyTestDefaultValues, TestSize.Level1)
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
    Opt_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Opt_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueFontFamily = initValueFontFamily;

        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Opt_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueFontFamily = initValueFontFamily;

        modifier_->setFontFamily(node_, &inputValueFontFamily);
        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
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

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.radius'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.type'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.color'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.offsetX'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.offsetY'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.fill'";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsRadiusValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.radius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.radius";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsTypeValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const std::string& expectedStr, const Opt_ShadowType& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumShadowTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsTypeInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_ShadowType& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumShadowTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsColorValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Color_String_Resource_ColoringStrategy& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColorValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColoringStrategyValidValues) {
        checkValue(
            input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Union_Color_String_Resource_ColoringStrategy& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumColorInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    for (auto& [input, value] : Fixtures::testFixtureEnumColoringStrategyInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetXValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetX";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetYValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetY";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsFillValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsFillValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.fill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsFillInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsFillInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Boolean& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.fill";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
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
    Opt_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureFontFeatureNumValidValues[0]));

    auto checkValue = [this, &initValueFontFeature](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValueFontFeature = initValueFontFeature;

        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFeatureNumValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setFontFeatureTestFontFeatureInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setFontFeatureTestFontFeatureInvalidValues, TestSize.Level1)
{
    Opt_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureFontFeatureNumValidValues[0]));

    auto checkValue = [this, &initValueFontFeature](const std::string& input, const Opt_String& value) {
        Opt_String inputValueFontFeature = initValueFontFeature;

        modifier_->setFontFeature(node_, &inputValueFontFeature);
        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFeatureNumInvalidValues) {
        checkValue(input, ArkValue<Opt_String>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
}

/*
 * @tc.name: setDateTimeOptionsTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setDateTimeOptionsTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}
} // namespace OHOS::Ace::NG
