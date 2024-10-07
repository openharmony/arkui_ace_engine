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

#include "core/components/checkable/checkable_theme.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
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
const auto ATTRIBUTE_RADIO_STYLE_CHECKED_BACKGROUND_COLOR_NAME = "checkedBackgroundColor";
const auto ATTRIBUTE_RADIO_STYLE_CHECKED_BACKGROUND_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_RADIO_STYLE_UNCHECKED_BORDER_COLOR_NAME = "uncheckedBorderColor";
const auto ATTRIBUTE_RADIO_STYLE_UNCHECKED_BORDER_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_RADIO_STYLE_INDICATOR_COLOR_NAME = "indicatorColor";
const auto ATTRIBUTE_RADIO_STYLE_INDICATOR_COLOR_DEFAULT_VALUE = "#FF000000";
} // namespace

class RadioModifierTest : public ModifierTestBase<GENERATED_ArkUIRadioModifier,
                              &GENERATED_ArkUINodeModifiers::getRadioModifier, GENERATED_ARKUI_RADIO> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<RadioTheme>();

        for (auto&& res : Fixtures::resourceInitTable) {
            AddResource(std::get<0>(res), std::get<2>(res)); // 2 - index of resource
            AddResource(std::get<1>(res), std::get<2>(res)); // 2 - index of resource
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
    EXPECT_EQ(resultStr, ATTRIBUTE_GROUP_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INDICATOR_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_INDICATOR_TYPE_DEFAULT_VALUE);
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
    initValueOptions.indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(
        std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.group = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setRadioOptions, attribute: group";
    };

    for (auto&& value : Fixtures::testFixtureStringValidValues) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
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
    initValueOptions.indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(
        std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.value = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setRadioOptions, attribute: value";
    };

    for (auto&& value : Fixtures::testFixtureStringValidValues) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
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
    initValueOptions.indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(
        std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_RadioIndicatorType& value,
                          const std::string& expectedStr) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.indicatorType = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INDICATOR_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setRadioOptions, attribute: indicatorType";
    };

    for (auto&& value : Fixtures::testFixtureEnumRadioIndicatorTypeValidValues) {
        checkValue(
            std::get<0>(value), Converter::ArkValue<Opt_RadioIndicatorType>(std::get<1>(value)), std::get<2>(value));
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
    initValueOptions.indicatorType = Converter::ArkValue<Opt_RadioIndicatorType>(
        std::get<1>(Fixtures::testFixtureEnumRadioIndicatorTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_RadioIndicatorType& value) {
        Ark_RadioOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        modifier_->setRadioOptions(node, &inputValueOptions);
        inputValueOptions.indicatorType = value;
        modifier_->setRadioOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INDICATOR_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_INDICATOR_TYPE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setRadioOptions, attribute: indicatorType";
    };

    for (auto&& value : Fixtures::testFixtureEnumRadioIndicatorTypeInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_RadioIndicatorType>(std::get<1>(value)));
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
    EXPECT_EQ(resultStr, ATTRIBUTE_CHECKED_DEFAULT_VALUE);
}

/*
 * @tc.name: setCheckedTestCheckedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setCheckedTestCheckedValidValues, TestSize.Level1)
{
    Ark_Boolean initValueChecked;

    // Initial setup
    initValueChecked = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueChecked](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueChecked = initValueChecked;

        inputValueChecked = value;
        modifier_->setChecked(node_, inputValueChecked);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CHECKED_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setChecked, attribute: checked";
    };

    for (auto&& value : Fixtures::testFixtureBooleanValidValues) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
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

    resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_CHECKED_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_CHECKED_BACKGROUND_COLOR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_UNCHECKED_BORDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_UNCHECKED_BORDER_COLOR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_INDICATOR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_INDICATOR_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setRadioStyleTestRadioStyleCheckedBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleCheckedBackgroundColorValidValues, TestSize.Level1)
{
    Ark_RadioStyle initValueRadioStyle;

    // Initial setup
    initValueRadioStyle.checkedBackgroundColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.uncheckedBorderColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.indicatorColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Opt_RadioStyle realInputValue = Converter::ArkValue<Opt_RadioStyle>(initValueRadioStyle);
        Ark_RadioStyle& inputValueRadioStyle = realInputValue.value;

        inputValueRadioStyle.checkedBackgroundColor = value;
        modifier_->setRadioStyle(node_, &realInputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_CHECKED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setRadioStyle, attribute: checkedBackgroundColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(value)),
            std::get<2>(value));
    }
}

/*
 * @tc.name: setRadioStyleTestRadioStyleCheckedBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleCheckedBackgroundColorInvalidValues, TestSize.Level1)
{
    Ark_RadioStyle initValueRadioStyle;

    // Initial setup
    initValueRadioStyle.checkedBackgroundColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.uncheckedBorderColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.indicatorColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_RadioStyle realInputValue = Converter::ArkValue<Opt_RadioStyle>(initValueRadioStyle);
        Ark_RadioStyle& inputValueRadioStyle = realInputValue.value;

        modifier_->setRadioStyle(node_, &realInputValue);
        inputValueRadioStyle.checkedBackgroundColor = value;
        modifier_->setRadioStyle(node_, &realInputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_CHECKED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_CHECKED_BACKGROUND_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setRadioStyle, attribute: checkedBackgroundColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setRadioStyleTestRadioStyleUncheckedBorderColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleUncheckedBorderColorValidValues, TestSize.Level1)
{
    Ark_RadioStyle initValueRadioStyle;

    // Initial setup
    initValueRadioStyle.checkedBackgroundColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.uncheckedBorderColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.indicatorColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Opt_RadioStyle realInputValue = Converter::ArkValue<Opt_RadioStyle>(initValueRadioStyle);
        Ark_RadioStyle& inputValueRadioStyle = realInputValue.value;

        inputValueRadioStyle.uncheckedBorderColor = value;
        modifier_->setRadioStyle(node_, &realInputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_UNCHECKED_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setRadioStyle, attribute: uncheckedBorderColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(value)),
            std::get<2>(value));
    }
}

/*
 * @tc.name: setRadioStyleTestRadioStyleUncheckedBorderColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleUncheckedBorderColorInvalidValues, TestSize.Level1)
{
    Ark_RadioStyle initValueRadioStyle;

    // Initial setup
    initValueRadioStyle.checkedBackgroundColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.uncheckedBorderColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.indicatorColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_RadioStyle realInputValue = Converter::ArkValue<Opt_RadioStyle>(initValueRadioStyle);
        Ark_RadioStyle& inputValueRadioStyle = realInputValue.value;

        modifier_->setRadioStyle(node_, &realInputValue);
        inputValueRadioStyle.uncheckedBorderColor = value;
        modifier_->setRadioStyle(node_, &realInputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_UNCHECKED_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_UNCHECKED_BORDER_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setRadioStyle, attribute: uncheckedBorderColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setRadioStyleTestRadioStyleIndicatorColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleIndicatorColorValidValues, TestSize.Level1)
{
    Ark_RadioStyle initValueRadioStyle;

    // Initial setup
    initValueRadioStyle.checkedBackgroundColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.uncheckedBorderColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.indicatorColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Opt_RadioStyle realInputValue = Converter::ArkValue<Opt_RadioStyle>(initValueRadioStyle);
        Ark_RadioStyle& inputValueRadioStyle = realInputValue.value;

        inputValueRadioStyle.indicatorColor = value;
        modifier_->setRadioStyle(node_, &realInputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_INDICATOR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setRadioStyle, attribute: indicatorColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(value)),
            std::get<2>(value));
    }
}

/*
 * @tc.name: setRadioStyleTestRadioStyleIndicatorColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioModifierTest, setRadioStyleTestRadioStyleIndicatorColorInvalidValues, TestSize.Level1)
{
    Ark_RadioStyle initValueRadioStyle;

    // Initial setup
    initValueRadioStyle.checkedBackgroundColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.uncheckedBorderColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    initValueRadioStyle.indicatorColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueRadioStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_RadioStyle realInputValue = Converter::ArkValue<Opt_RadioStyle>(initValueRadioStyle);
        Ark_RadioStyle& inputValueRadioStyle = realInputValue.value;

        modifier_->setRadioStyle(node_, &realInputValue);
        inputValueRadioStyle.indicatorColor = value;
        modifier_->setRadioStyle(node_, &realInputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultRadioStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RADIO_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRadioStyle, ATTRIBUTE_RADIO_STYLE_INDICATOR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RADIO_STYLE_INDICATOR_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setRadioStyle, attribute: indicatorColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_ResourceColor>());
}
} // namespace OHOS::Ace::NG
