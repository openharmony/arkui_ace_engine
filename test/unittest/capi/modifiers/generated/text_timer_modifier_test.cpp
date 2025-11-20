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
const auto ATTRIBUTE_TEXT_SHADOW_NAME = "textShadow";
const auto ATTRIBUTE_IS_COUNT_DOWN_NAME = "isCountDown";
const auto ATTRIBUTE_IS_COUNT_DOWN_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FORMAT_NAME = "format";
const auto ATTRIBUTE_FORMAT_DEFAULT_VALUE = "HH:mm:ss.SS";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME = "type";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME = "offsetX";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME = "offsetY";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME = "fill";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE = "false";
} // namespace

class TextTimerModifierTest : public ModifierTestBase<GENERATED_ArkUITextTimerModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextTimerModifier, GENERATED_ARKUI_TEXT_TIMER> {
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
 * @tc.name: setTextTimerOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_COUNT_DOWN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IS_COUNT_DOWN_DEFAULT_VALUE) << "Default value for attribute 'options.isCountDown'";
}

/*
 * @tc.name: setTextTimerOptionsTestOptionsIsCountDownValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestOptionsIsCountDownValidValues, TestSize.Level1)
{
    Opt_TextTimerOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).isCountDown =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_TextTimerOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).isCountDown = value;
        modifier_->setTextTimerOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_COUNT_DOWN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextTimerOptions, attribute: options.isCountDown";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setTextTimerOptionsTestOptionsIsCountDownInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestOptionsIsCountDownInvalidValues, TestSize.Level1)
{
    Opt_TextTimerOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).isCountDown =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_TextTimerOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).isCountDown = value;
        modifier_->setTextTimerOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_COUNT_DOWN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_IS_COUNT_DOWN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextTimerOptions, attribute: options.isCountDown";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFormatTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFormatTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFormatTestFormatValidValues, TestSize.Level1)
{
    Opt_String initValueFormat;

    // Initial setup
    initValueFormat = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureTextTimerDateFormatValidValues[0]));

    auto checkValue = [this, &initValueFormat](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValueFormat = initValueFormat;

        inputValueFormat = value;
        modifier_->setFormat(node_, &inputValueFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextTimerDateFormatValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setFormatTestFormatInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFormatTestFormatInvalidValues, TestSize.Level1)
{
    Opt_String initValueFormat;

    // Initial setup
    initValueFormat = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureTextTimerDateFormatValidValues[0]));

    auto checkValue = [this, &initValueFormat](const std::string& input, const Opt_String& value) {
        Opt_String inputValueFormat = initValueFormat;

        modifier_->setFormat(node_, &inputValueFormat);
        inputValueFormat = value;
        modifier_->setFormat(node_, &inputValueFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FORMAT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextTimerDateFormatInvalidValues) {
        checkValue(input, ArkValue<Opt_String>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontColorTestFontColorValidValues, TestSize.Level1)
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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
HWTEST_F(TextTimerModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_ResourceStr initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_FontWeight_ResourceStr& value) {
        Opt_Union_Number_FontWeight_ResourceStr inputValueFontWeight = initValueFontWeight;

        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightResStringsValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_ResourceStr initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Opt_Union_Number_FontWeight_ResourceStr& value) {
        Opt_Union_Number_FontWeight_ResourceStr inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight(node_, &inputValueFontWeight);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                              ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightResStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                              ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_FontWeight_ResourceStr>());
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontFamilyTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, DISABLED_setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setTextShadowTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsRadiusValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowRadiusNumberValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowRadiusResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    for (auto& [input, value] : Fixtures::testFixtureShadowRadiusNumberInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureShadowRadiusResInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsTypeValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsTypeInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ShadowType>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsColorValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDummyColoringStrategyValidValues) {
        checkValue(
            input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
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
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetXValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetYValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsFillValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowShadowOptionsFillInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
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
} // namespace OHOS::Ace::NG
