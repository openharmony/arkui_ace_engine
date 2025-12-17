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

#include "core/components/checkable/checkable_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_RADIO_STYLE_NAME = "radioStyle";
const auto ATTRIBUTE_GROUP_NAME = "group";
const auto ATTRIBUTE_GROUP_DEFAULT_VALUE = "";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_INDICATOR_TYPE_NAME = "indicatorType";
const auto ATTRIBUTE_INDICATOR_TYPE_DEFAULT_VALUE = "TICK";
const auto ATTRIBUTE_CHECKED_NAME = "checked";
const auto ATTRIBUTE_CHECKED_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_RADIO_STYLE_I_CHECKED_BACKGROUND_COLOR_NAME = "checkedBackgroundColor";
const auto ATTRIBUTE_RADIO_STYLE_I_CHECKED_BACKGROUND_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_RADIO_STYLE_I_UNCHECKED_BORDER_COLOR_NAME = "uncheckedBorderColor";
const auto ATTRIBUTE_RADIO_STYLE_I_UNCHECKED_BORDER_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_RADIO_STYLE_I_INDICATOR_COLOR_NAME = "indicatorColor";
const auto ATTRIBUTE_RADIO_STYLE_I_INDICATOR_COLOR_DEFAULT_VALUE = "#FF000000";
} // namespace

class RadioModifierTest : public ModifierTestBase<GENERATED_ArkUIRadioModifier,
                              &GENERATED_ArkUINodeModifiers::getRadioModifier, GENERATED_ARKUI_RADIO> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<RadioTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setRadioOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_GROUP_DEFAULT_VALUE) << "Default value for attribute 'options.group'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'options.value'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INDICATOR_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_INDICATOR_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'options.indicatorType'";
}

/*
 * @tc.name: setRadioOptionsTestOptionsGroupValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioOptionsTestOptionsGroupValidValues, TestSize.Level1)
{
    Ark_RadioOptions initValueOptions;

    // Initial setup
    initValueOptions.group = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.value = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.indicatorType =
        ArkValue<Opt_RadioIndicatorType>(std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.group = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRadioOptions, attribute: options.group";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRadioOptionsTestOptionsValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioOptionsTestOptionsValueValidValues, TestSize.Level1)
{
    Ark_RadioOptions initValueOptions;

    // Initial setup
    initValueOptions.group = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.value = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.indicatorType =
        ArkValue<Opt_RadioIndicatorType>(std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.value = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRadioOptions, attribute: options.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRadioOptionsTestOptionsIndicatorTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, DISABLED_setRadioOptionsTestOptionsIndicatorTypeValidValues, TestSize.Level1)
{
    Ark_RadioOptions initValueOptions;

    // Initial setup
    initValueOptions.group = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.value = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.indicatorType =
        ArkValue<Opt_RadioIndicatorType>(std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_RadioIndicatorType& value) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.indicatorType = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INDICATOR_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRadioOptions, attribute: options.indicatorType";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumRadioIndicatorTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_RadioIndicatorType>(value));
    }
}

/*
 * @tc.name: setRadioOptionsTestOptionsIndicatorTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioOptionsTestOptionsIndicatorTypeInvalidValues, TestSize.Level1)
{
    Ark_RadioOptions initValueOptions;

    // Initial setup
    initValueOptions.group = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.value = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.indicatorType =
        ArkValue<Opt_RadioIndicatorType>(std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_RadioIndicatorType& value) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.indicatorType = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INDICATOR_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_INDICATOR_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRadioOptions, attribute: options.indicatorType";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumRadioIndicatorTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_RadioIndicatorType>(value));
    }
}

/*
 * @tc.name: setCheckedTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setCheckedTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CHECKED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CHECKED_DEFAULT_VALUE) << "Default value for attribute 'checked'";
}

/*
 * @tc.name: setCheckedTestCheckedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setCheckedTestCheckedValidValues, TestSize.Level1)
{
    Opt_Boolean initValueChecked;

    // Initial setup
    initValueChecked = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueChecked](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueChecked = initValueChecked;

        inputValueChecked = value;
        modifier_->setChecked(node_, &inputValueChecked);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CHECKED_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setChecked, attribute: checked";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setCheckedTestCheckedInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setCheckedTestCheckedInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueChecked;

    // Initial setup
    initValueChecked = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueChecked](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueChecked = initValueChecked;

        modifier_->setChecked(node_, &inputValueChecked);
        inputValueChecked = value;
        modifier_->setChecked(node_, &inputValueChecked);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CHECKED_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CHECKED_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setChecked, attribute: checked";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setRadioStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultRadioStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_CHECKED_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_I_CHECKED_BACKGROUND_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'radioStyle.checkedBackgroundColor'";

    resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_UNCHECKED_BORDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_I_UNCHECKED_BORDER_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'radioStyle.uncheckedBorderColor'";

    resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_INDICATOR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_I_INDICATOR_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'radioStyle.indicatorColor'";
}

/*
 * @tc.name: setRadioStyleTestRadioStyleCheckedBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleCheckedBackgroundColorValidValues, TestSize.Level1)
{
    Opt_RadioStyle initValueRadioStyle;

    // Initial setup
    WriteTo(initValueRadioStyle).checkedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).uncheckedBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).indicatorColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_RadioStyle inputValueRadioStyle = initValueRadioStyle;

        WriteTo(inputValueRadioStyle).checkedBackgroundColor = value;
        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_CHECKED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRadioStyle, attribute: radioStyle.checkedBackgroundColor";
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
 * @tc.name: setRadioStyleTestRadioStyleCheckedBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleCheckedBackgroundColorInvalidValues, TestSize.Level1)
{
    Opt_RadioStyle initValueRadioStyle;

    // Initial setup
    WriteTo(initValueRadioStyle).checkedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).uncheckedBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).indicatorColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_RadioStyle inputValueRadioStyle = initValueRadioStyle;

        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        WriteTo(inputValueRadioStyle).checkedBackgroundColor = value;
        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_CHECKED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_I_CHECKED_BACKGROUND_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRadioStyle, attribute: radioStyle.checkedBackgroundColor";
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
 * @tc.name: setRadioStyleTestRadioStyleUncheckedBorderColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleUncheckedBorderColorValidValues, TestSize.Level1)
{
    Opt_RadioStyle initValueRadioStyle;

    // Initial setup
    WriteTo(initValueRadioStyle).checkedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).uncheckedBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).indicatorColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_RadioStyle inputValueRadioStyle = initValueRadioStyle;

        WriteTo(inputValueRadioStyle).uncheckedBorderColor = value;
        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_UNCHECKED_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRadioStyle, attribute: radioStyle.uncheckedBorderColor";
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
 * @tc.name: setRadioStyleTestRadioStyleUncheckedBorderColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleUncheckedBorderColorInvalidValues, TestSize.Level1)
{
    Opt_RadioStyle initValueRadioStyle;

    // Initial setup
    WriteTo(initValueRadioStyle).checkedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).uncheckedBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).indicatorColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_RadioStyle inputValueRadioStyle = initValueRadioStyle;

        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        WriteTo(inputValueRadioStyle).uncheckedBorderColor = value;
        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_UNCHECKED_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_I_UNCHECKED_BORDER_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRadioStyle, attribute: radioStyle.uncheckedBorderColor";
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
 * @tc.name: setRadioStyleTestRadioStyleIndicatorColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleIndicatorColorValidValues, TestSize.Level1)
{
    Opt_RadioStyle initValueRadioStyle;

    // Initial setup
    WriteTo(initValueRadioStyle).checkedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).uncheckedBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).indicatorColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_RadioStyle inputValueRadioStyle = initValueRadioStyle;

        WriteTo(inputValueRadioStyle).indicatorColor = value;
        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_INDICATOR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRadioStyle, attribute: radioStyle.indicatorColor";
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
 * @tc.name: setRadioStyleTestRadioStyleIndicatorColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleIndicatorColorInvalidValues, TestSize.Level1)
{
    Opt_RadioStyle initValueRadioStyle;

    // Initial setup
    WriteTo(initValueRadioStyle).checkedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).uncheckedBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueRadioStyle).indicatorColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_RadioStyle inputValueRadioStyle = initValueRadioStyle;

        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        WriteTo(inputValueRadioStyle).indicatorColor = value;
        modifier_->setRadioStyle(node_, &inputValueRadioStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_I_INDICATOR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_I_INDICATOR_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRadioStyle, attribute: radioStyle.indicatorColor";
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
} // namespace OHOS::Ace::NG
