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

#include "slider_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Slider;

/*
 * @tc.name: setSliderOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'options.value'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_DEFAULT_VALUE) << "Default value for attribute 'options.min'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_DEFAULT_VALUE) << "Default value for attribute 'options.max'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_DEFAULT_VALUE) << "Default value for attribute 'options.step'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE) << "Default value for attribute 'options.style'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE) << "Default value for attribute 'options.direction'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REVERSE_DEFAULT_VALUE) << "Default value for attribute 'options.reverse'";
}

/*
 * @tc.name: setSliderOptionsTestOptionsValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsValueValidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).value = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsValueInvalidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).value = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.value";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setSliderOptionsTestOptionsMinValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsMinValidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).min = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.min";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsMinInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsMinInvalidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).min = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.min";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setSliderOptionsTestOptionsMaxValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsMaxValidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).max = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.max";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsMaxInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsMaxInvalidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).max = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.max";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setSliderOptionsTestOptionsStepValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsStepValidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).step = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.step";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsStepInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsStepInvalidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).step = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.step";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setSliderOptionsTestOptionsStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsStyleValidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_SliderStyle& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).style = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumSliderStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_SliderStyle>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsStyleInvalidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_SliderStyle& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).style = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumSliderStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_SliderStyle>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsDirectionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsDirectionValidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Axis& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).direction = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.direction";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumAxisValidValues) {
        checkValue(input, expected, ArkValue<Opt_Axis>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsDirectionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsDirectionInvalidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Axis& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).direction = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.direction";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumAxisInvalidValues) {
        checkValue(input, ArkValue<Opt_Axis>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsReverseValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsReverseValidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).reverse = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.reverse";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsReverseInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSliderOptionsTestOptionsReverseInvalidValues, TestSize.Level1)
{
    Opt_SliderOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).value =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).min =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).max =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueOptions).style =
        ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    WriteTo(initValueOptions).direction = ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    WriteTo(initValueOptions).reverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_SliderOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).reverse = value;
        modifier_->setSliderOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_REVERSE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderOptions, attribute: options.reverse";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setBlockColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE) << "Default value for attribute 'blockColor'";
}

/*
 * @tc.name: setBlockColorTestBlockColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockColorTestBlockColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueBlockColor;

    // Initial setup
    initValueBlockColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueBlockColor = initValueBlockColor;

        inputValueBlockColor = value;
        modifier_->setBlockColor(node_, &inputValueBlockColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockColor, attribute: blockColor";
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
 * @tc.name: setBlockColorTestBlockColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockColorTestBlockColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueBlockColor;

    // Initial setup
    initValueBlockColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueBlockColor = initValueBlockColor;

        modifier_->setBlockColor(node_, &inputValueBlockColor);
        inputValueBlockColor = value;
        modifier_->setBlockColor(node_, &inputValueBlockColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockColor, attribute: blockColor";
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
 * @tc.name: setTrackColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_DEFAULT_VALUE) << "Default value for attribute 'trackColor'";
}

/*
 * @tc.name: setTrackColorTestTrackColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackColorTestTrackColorValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_LinearGradient initValueTrackColor;

    // Initial setup
    initValueTrackColor = ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueTrackColor](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_ResourceColor_LinearGradient& value) {
        Opt_Union_ResourceColor_LinearGradient inputValueTrackColor = initValueTrackColor;

        inputValueTrackColor = value;
        modifier_->setTrackColor(node_, &inputValueTrackColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTrackColor, attribute: trackColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Color>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Int32>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
}

/*
 * @tc.name: setTrackColorTestTrackColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackColorTestTrackColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_LinearGradient initValueTrackColor;

    // Initial setup
    initValueTrackColor = ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueTrackColor](
                          const std::string& input, const Opt_Union_ResourceColor_LinearGradient& value) {
        Opt_Union_ResourceColor_LinearGradient inputValueTrackColor = initValueTrackColor;

        modifier_->setTrackColor(node_, &inputValueTrackColor);
        inputValueTrackColor = value;
        modifier_->setTrackColor(node_, &inputValueTrackColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTrackColor, attribute: trackColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_Color>(value)));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_ResourceColor_LinearGradient>());
}

/*
 * @tc.name: setSelectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSelectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE) << "Default value for attribute 'selectedColor'";
}

/*
 * @tc.name: setSelectedColorTestSelectedColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedColorTestSelectedColorValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_LinearGradient initValueSelectedColor;

    // Initial setup
    initValueSelectedColor = ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueSelectedColor](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_ResourceColor_LinearGradient& value) {
        Opt_Union_ResourceColor_LinearGradient inputValueSelectedColor = initValueSelectedColor;

        inputValueSelectedColor = value;
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedColor, attribute: selectedColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Color>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Int32>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
}

/*
 * @tc.name: setSelectedColorTestSelectedColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSelectedColorTestSelectedColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_LinearGradient initValueSelectedColor;

    // Initial setup
    initValueSelectedColor = ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueSelectedColor](
                          const std::string& input, const Opt_Union_ResourceColor_LinearGradient& value) {
        Opt_Union_ResourceColor_LinearGradient inputValueSelectedColor = initValueSelectedColor;

        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        inputValueSelectedColor = value;
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedColor, attribute: selectedColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_Color>(value)));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_ResourceColor_LinearGradient>());
}

/*
 * @tc.name: setShowStepsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowStepsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_STEPS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_STEPS_DEFAULT_VALUE) << "Default value for attribute 'showSteps'";
}

/*
 * @tc.name: setShowStepsTestShowStepsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowStepsTestShowStepsValidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowSteps;

    // Initial setup
    initValueShowSteps = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowSteps](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowSteps = initValueShowSteps;

        inputValueShowSteps = value;
        modifier_->setShowSteps(node_, &inputValueShowSteps);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_STEPS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowSteps, attribute: showSteps";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowStepsTestShowStepsInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setShowStepsTestShowStepsInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowSteps;

    // Initial setup
    initValueShowSteps = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowSteps](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowSteps = initValueShowSteps;

        modifier_->setShowSteps(node_, &inputValueShowSteps);
        inputValueShowSteps = value;
        modifier_->setShowSteps(node_, &inputValueShowSteps);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_STEPS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_STEPS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowSteps, attribute: showSteps";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setTrackThicknessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackThicknessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE) << "Default value for attribute 'trackThickness'";
}

/*
 * @tc.name: setTrackThicknessTestTrackThicknessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackThicknessTestTrackThicknessValidValues, TestSize.Level1)
{
    Opt_Length initValueTrackThickness;

    // Initial setup
    initValueTrackThickness =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTrackThickness](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueTrackThickness = initValueTrackThickness;

        inputValueTrackThickness = value;
        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTrackThickness, attribute: trackThickness";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setTrackThicknessTestTrackThicknessInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackThicknessTestTrackThicknessInvalidValues, TestSize.Level1)
{
    Opt_Length initValueTrackThickness;

    // Initial setup
    initValueTrackThickness =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTrackThickness](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueTrackThickness = initValueTrackThickness;

        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        inputValueTrackThickness = value;
        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTrackThickness, attribute: trackThickness";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBlockBorderColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'blockBorderColor'";
}

/*
 * @tc.name: setBlockBorderColorTestBlockBorderColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderColorTestBlockBorderColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueBlockBorderColor;

    // Initial setup
    initValueBlockBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueBlockBorderColor = initValueBlockBorderColor;

        inputValueBlockBorderColor = value;
        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockBorderColor, attribute: blockBorderColor";
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
 * @tc.name: setBlockBorderColorTestBlockBorderColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderColorTestBlockBorderColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueBlockBorderColor;

    // Initial setup
    initValueBlockBorderColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueBlockBorderColor = initValueBlockBorderColor;

        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        inputValueBlockBorderColor = value;
        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockBorderColor, attribute: blockBorderColor";
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
 * @tc.name: setBlockBorderWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE) <<
        "Default value for attribute 'blockBorderWidth'";
}

/*
 * @tc.name: setBlockBorderWidthTestBlockBorderWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderWidthTestBlockBorderWidthValidValues, TestSize.Level1)
{
    Opt_Length initValueBlockBorderWidth;

    // Initial setup
    initValueBlockBorderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderWidth](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueBlockBorderWidth = initValueBlockBorderWidth;

        inputValueBlockBorderWidth = value;
        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockBorderWidth, attribute: blockBorderWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setBlockBorderWidthTestBlockBorderWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderWidthTestBlockBorderWidthInvalidValues, TestSize.Level1)
{
    Opt_Length initValueBlockBorderWidth;

    // Initial setup
    initValueBlockBorderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderWidth](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueBlockBorderWidth = initValueBlockBorderWidth;

        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        inputValueBlockBorderWidth = value;
        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockBorderWidth, attribute: blockBorderWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setStepColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setStepColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE) << "Default value for attribute 'stepColor'";
}

/*
 * @tc.name: setStepColorTestStepColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepColorTestStepColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueStepColor;

    // Initial setup
    initValueStepColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueStepColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueStepColor = initValueStepColor;

        inputValueStepColor = value;
        modifier_->setStepColor(node_, &inputValueStepColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStepColor, attribute: stepColor";
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
 * @tc.name: setStepColorTestStepColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepColorTestStepColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueStepColor;

    // Initial setup
    initValueStepColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueStepColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueStepColor = initValueStepColor;

        modifier_->setStepColor(node_, &inputValueStepColor);
        inputValueStepColor = value;
        modifier_->setStepColor(node_, &inputValueStepColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStepColor, attribute: stepColor";
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
 * @tc.name: setTrackBorderRadiusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackBorderRadiusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE) <<
        "Default value for attribute 'trackBorderRadius'";
}

/*
 * @tc.name: setTrackBorderRadiusTestTrackBorderRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackBorderRadiusTestTrackBorderRadiusValidValues, TestSize.Level1)
{
    Opt_Length initValueTrackBorderRadius;

    // Initial setup
    initValueTrackBorderRadius =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTrackBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueTrackBorderRadius = initValueTrackBorderRadius;

        inputValueTrackBorderRadius = value;
        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTrackBorderRadius, attribute: trackBorderRadius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setTrackBorderRadiusTestTrackBorderRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackBorderRadiusTestTrackBorderRadiusInvalidValues, TestSize.Level1)
{
    Opt_Length initValueTrackBorderRadius;

    // Initial setup
    initValueTrackBorderRadius =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueTrackBorderRadius](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueTrackBorderRadius = initValueTrackBorderRadius;

        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        inputValueTrackBorderRadius = value;
        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTrackBorderRadius, attribute: trackBorderRadius";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setSelectedBorderRadiusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedBorderRadiusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BORDER_RADIUS_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedBorderRadius'";
}

/*
 * @tc.name: setSelectedBorderRadiusTestSelectedBorderRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedBorderRadiusTestSelectedBorderRadiusValidValues, TestSize.Level1)
{
    Opt_Dimension initValueSelectedBorderRadius;

    // Initial setup
    initValueSelectedBorderRadius =
        ArkUnion<Opt_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueSelectedBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Dimension& value) {
        Opt_Dimension inputValueSelectedBorderRadius = initValueSelectedBorderRadius;

        inputValueSelectedBorderRadius = value;
        modifier_->setSelectedBorderRadius(node_, &inputValueSelectedBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedBorderRadius, attribute: selectedBorderRadius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Dimension, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Dimension, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedBorderRadiusTestSelectedBorderRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedBorderRadiusTestSelectedBorderRadiusInvalidValues, TestSize.Level1)
{
    Opt_Dimension initValueSelectedBorderRadius;

    // Initial setup
    initValueSelectedBorderRadius =
        ArkUnion<Opt_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueSelectedBorderRadius](const std::string& input, const Opt_Dimension& value) {
        Opt_Dimension inputValueSelectedBorderRadius = initValueSelectedBorderRadius;

        modifier_->setSelectedBorderRadius(node_, &inputValueSelectedBorderRadius);
        inputValueSelectedBorderRadius = value;
        modifier_->setSelectedBorderRadius(node_, &inputValueSelectedBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BORDER_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedBorderRadius, attribute: selectedBorderRadius";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Dimension, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Dimension, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Dimension, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Dimension, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Dimension>());
}

/*
 * @tc.name: setBlockSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultBlockSize =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'blockSize.width'";

    resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'blockSize.height'";
}

/*
 * @tc.name: setBlockSizeTestBlockSizeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockSizeTestBlockSizeWidthValidValues, TestSize.Level1)
{
    Opt_SizeOptions initValueBlockSize;

    // Initial setup
    WriteTo(initValueBlockSize).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueBlockSize).height =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_SizeOptions inputValueBlockSize = initValueBlockSize;

        WriteTo(inputValueBlockSize).width = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.width";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setBlockSizeTestBlockSizeWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockSizeTestBlockSizeWidthInvalidValues, TestSize.Level1)
{
    Opt_SizeOptions initValueBlockSize;

    // Initial setup
    WriteTo(initValueBlockSize).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueBlockSize).height =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Opt_SizeOptions inputValueBlockSize = initValueBlockSize;

        modifier_->setBlockSize(node_, &inputValueBlockSize);
        WriteTo(inputValueBlockSize).width = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.width";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBlockSizeTestBlockSizeHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockSizeTestBlockSizeHeightValidValues, TestSize.Level1)
{
    Opt_SizeOptions initValueBlockSize;

    // Initial setup
    WriteTo(initValueBlockSize).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueBlockSize).height =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_SizeOptions inputValueBlockSize = initValueBlockSize;

        WriteTo(inputValueBlockSize).height = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.height";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setBlockSizeTestBlockSizeHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockSizeTestBlockSizeHeightInvalidValues, TestSize.Level1)
{
    Opt_SizeOptions initValueBlockSize;

    // Initial setup
    WriteTo(initValueBlockSize).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueBlockSize).height =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Opt_SizeOptions inputValueBlockSize = initValueBlockSize;

        modifier_->setBlockSize(node_, &inputValueBlockSize);
        WriteTo(inputValueBlockSize).height = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.height";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBlockStyleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockStyleTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setStepSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setStepSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE) << "Default value for attribute 'stepSize'";
}

/*
 * @tc.name: setStepSizeTestStepSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepSizeTestStepSizeValidValues, TestSize.Level1)
{
    Opt_Length initValueStepSize;

    // Initial setup
    initValueStepSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStepSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueStepSize = initValueStepSize;

        inputValueStepSize = value;
        modifier_->setStepSize(node_, &inputValueStepSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStepSize, attribute: stepSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setStepSizeTestStepSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepSizeTestStepSizeInvalidValues, TestSize.Level1)
{
    Opt_Length initValueStepSize;

    // Initial setup
    initValueStepSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStepSize](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueStepSize = initValueStepSize;

        modifier_->setStepSize(node_, &inputValueStepSize);
        inputValueStepSize = value;
        modifier_->setStepSize(node_, &inputValueStepSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStepSize, attribute: stepSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setSliderInteractionModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderInteractionModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SLIDER_INTERACTION_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'sliderInteractionMode'";
}

/*
 * @tc.name: setSliderInteractionModeTestSliderInteractionModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderInteractionModeTestSliderInteractionModeValidValues, TestSize.Level1)
{
    Opt_SliderInteraction initValueSliderInteractionMode;

    // Initial setup
    initValueSliderInteractionMode =
        ArkValue<Opt_SliderInteraction>(std::get<1>(Fixtures::testFixtureEnumSliderInteractionValidValues[0]));

    auto checkValue = [this, &initValueSliderInteractionMode](const std::string& input, const std::string& expectedStr,
                          const Opt_SliderInteraction& value) {
        Opt_SliderInteraction inputValueSliderInteractionMode = initValueSliderInteractionMode;

        inputValueSliderInteractionMode = value;
        modifier_->setSliderInteractionMode(node_, &inputValueSliderInteractionMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderInteractionMode, attribute: sliderInteractionMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumSliderInteractionValidValues) {
        checkValue(input, expected, ArkValue<Opt_SliderInteraction>(value));
    }
}

/*
 * @tc.name: setSliderInteractionModeTestSliderInteractionModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderInteractionModeTestSliderInteractionModeInvalidValues, TestSize.Level1)
{
    Opt_SliderInteraction initValueSliderInteractionMode;

    // Initial setup
    initValueSliderInteractionMode =
        ArkValue<Opt_SliderInteraction>(std::get<1>(Fixtures::testFixtureEnumSliderInteractionValidValues[0]));

    auto checkValue = [this, &initValueSliderInteractionMode](
                          const std::string& input, const Opt_SliderInteraction& value) {
        Opt_SliderInteraction inputValueSliderInteractionMode = initValueSliderInteractionMode;

        modifier_->setSliderInteractionMode(node_, &inputValueSliderInteractionMode);
        inputValueSliderInteractionMode = value;
        modifier_->setSliderInteractionMode(node_, &inputValueSliderInteractionMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDER_INTERACTION_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderInteractionMode, attribute: sliderInteractionMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumSliderInteractionInvalidValues) {
        checkValue(input, ArkValue<Opt_SliderInteraction>(value));
    }
}

/*
 * @tc.name: setMinResponsiveDistanceTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinResponsiveDistanceTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE) <<
        "Default value for attribute 'minResponsiveDistance'";
}

/*
 * @tc.name: setMinResponsiveDistanceTestMinResponsiveDistanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setMinResponsiveDistanceTestMinResponsiveDistanceValidValues, TestSize.Level1)
{
    Opt_Number initValueMinResponsiveDistance;

    // Initial setup
    initValueMinResponsiveDistance = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinResponsiveDistance](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueMinResponsiveDistance = initValueMinResponsiveDistance;

        inputValueMinResponsiveDistance = value;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMinResponsiveDistanceTestMinResponsiveDistanceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinResponsiveDistanceTestMinResponsiveDistanceInvalidValues, TestSize.Level1)
{
    Opt_Number initValueMinResponsiveDistance;

    // Initial setup
    initValueMinResponsiveDistance = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinResponsiveDistance](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueMinResponsiveDistance = initValueMinResponsiveDistance;

        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        inputValueMinResponsiveDistance = value;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setSlideRangeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSlideRangeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSlideRange =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_I_FROM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_I_FROM_DEFAULT_VALUE) << "Default value for attribute 'slideRange.from'";

    resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_I_TO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_I_TO_DEFAULT_VALUE) << "Default value for attribute 'slideRange.to'";
}

/*
 * @tc.name: setSlideRangeTestSlideRangeFromValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSlideRangeTestSlideRangeFromValidValues, TestSize.Level1)
{
    Opt_SlideRange initValueSlideRange;

    // Initial setup
    WriteTo(initValueSlideRange).from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueSlideRange).to =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_SlideRange inputValueSlideRange = initValueSlideRange;

        WriteTo(inputValueSlideRange).from = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_I_FROM_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSlideRange, attribute: slideRange.from";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setSlideRangeTestSlideRangeFromInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSlideRangeTestSlideRangeFromInvalidValues, TestSize.Level1)
{
    Opt_SlideRange initValueSlideRange;

    // Initial setup
    WriteTo(initValueSlideRange).from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueSlideRange).to =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Number& value) {
        Opt_SlideRange inputValueSlideRange = initValueSlideRange;

        modifier_->setSlideRange(node_, &inputValueSlideRange);
        WriteTo(inputValueSlideRange).from = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_I_FROM_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_I_FROM_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSlideRange, attribute: slideRange.from";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setSlideRangeTestSlideRangeToValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSlideRangeTestSlideRangeToValidValues, TestSize.Level1)
{
    Opt_SlideRange initValueSlideRange;

    // Initial setup
    WriteTo(initValueSlideRange).from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueSlideRange).to =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_SlideRange inputValueSlideRange = initValueSlideRange;

        WriteTo(inputValueSlideRange).to = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_I_TO_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSlideRange, attribute: slideRange.to";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntCeilValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setSlideRangeTestSlideRangeToInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSlideRangeTestSlideRangeToInvalidValues, TestSize.Level1)
{
    Opt_SlideRange initValueSlideRange;

    // Initial setup
    WriteTo(initValueSlideRange).from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueSlideRange).to =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Number& value) {
        Opt_SlideRange inputValueSlideRange = initValueSlideRange;

        modifier_->setSlideRange(node_, &inputValueSlideRange);
        WriteTo(inputValueSlideRange).to = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_I_TO_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_I_TO_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSlideRange, attribute: slideRange.to";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntCeilInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setDigitalCrownSensitivityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setDigitalCrownSensitivityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE) <<
        "Default value for attribute 'digitalCrownSensitivity'";
}

/*
 * @tc.name: setDigitalCrownSensitivityTestDigitalCrownSensitivityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setDigitalCrownSensitivityTestDigitalCrownSensitivityValidValues, TestSize.Level1)
{
    Opt_CrownSensitivity initValueDigitalCrownSensitivity;

    // Initial setup
    initValueDigitalCrownSensitivity =
        ArkValue<Opt_CrownSensitivity>(std::get<1>(Fixtures::testFixtureEnumCrownSensitivityValidValues[0]));

    auto checkValue = [this, &initValueDigitalCrownSensitivity](
                          const std::string& input, const std::string& expectedStr, const Opt_CrownSensitivity& value) {
        Opt_CrownSensitivity inputValueDigitalCrownSensitivity = initValueDigitalCrownSensitivity;

        inputValueDigitalCrownSensitivity = value;
        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setDigitalCrownSensitivity, attribute: digitalCrownSensitivity";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCrownSensitivityValidValues) {
        checkValue(input, expected, ArkValue<Opt_CrownSensitivity>(value));
    }
}

/*
 * @tc.name: setDigitalCrownSensitivityTestDigitalCrownSensitivityInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    SliderModifierTest, DISABLED_setDigitalCrownSensitivityTestDigitalCrownSensitivityInvalidValues, TestSize.Level1)
{
    Opt_CrownSensitivity initValueDigitalCrownSensitivity;

    // Initial setup
    initValueDigitalCrownSensitivity =
        ArkValue<Opt_CrownSensitivity>(std::get<1>(Fixtures::testFixtureEnumCrownSensitivityValidValues[0]));

    auto checkValue = [this, &initValueDigitalCrownSensitivity](
                          const std::string& input, const Opt_CrownSensitivity& value) {
        Opt_CrownSensitivity inputValueDigitalCrownSensitivity = initValueDigitalCrownSensitivity;

        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        inputValueDigitalCrownSensitivity = value;
        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setDigitalCrownSensitivity, attribute: digitalCrownSensitivity";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCrownSensitivityInvalidValues) {
        checkValue(input, ArkValue<Opt_CrownSensitivity>(value));
    }
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE) <<
        "Default value for attribute 'enableHapticFeedback'";
}

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableHapticFeedback](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

} // namespace OHOS::Ace::NG
