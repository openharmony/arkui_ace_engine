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

#include "slider_modifier_test.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components/slider/slider_theme.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/linear_gradient_peer.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

/*
 * @tc.name: setSliderOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValueFull = GetJsonValue(node_);
    auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REVERSE_DEFAULT_VALUE);
}

/*
 * @tc.name: setSliderOptionsTestOptionsValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsValueValidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Ark_Float64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(value);
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: value";
    };

    for (auto&& value : Fixtures::testFixtureNumberValueValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Ark_Float64>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsValueInvalidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Union_F64_Bindable_F64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.value = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: value";
    };

    for (auto&& value : Fixtures::testFixtureNumberValueInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(std::get<1>(value)),
            std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Union_F64_Bindable_F64>(), ATTRIBUTE_MIN_DEFAULT_VALUE);
}

/*
 * @tc.name: setSliderOptionsTestOptionsMinValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsMinValidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.min = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: min";
    };

    for (auto&& value : Fixtures::testFixtureNumberMinValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsMinInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsMinInvalidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.min = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: min";
    };

    for (auto&& value : Fixtures::testFixtureNumberMinInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Float64>(), ATTRIBUTE_MIN_DEFAULT_VALUE);
}

/*
 * @tc.name: setSliderOptionsTestOptionsMaxValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsMaxValidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.max = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: max";
    };

    for (auto&& value : Fixtures::testFixtureNumberMaxValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsMaxInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsMaxInvalidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.max = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: max";
    };

    for (auto&& value : Fixtures::testFixtureNumberMaxInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Float64>(), ATTRIBUTE_MIN_DEFAULT_VALUE);
}

/*
 * @tc.name: setSliderOptionsTestOptionsStepValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsStepValidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.step = value;
        modifier_->setSliderOptions(node, &realInputValue);
        std::unique_ptr<JsonValue> jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: step";
    };

    for (auto&& value : Fixtures::testFixtureNumberStepValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsStepInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsStepInvalidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;
        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.step = value;
        modifier_->setSliderOptions(node, &realInputValue);
        std::unique_ptr<JsonValue> jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: step";
    };

    for (auto&& value : Fixtures::testFixtureNumberStepInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Float64>(), ATTRIBUTE_STEP_DEFAULT_VALUE);
}

/*
 * @tc.name: setSliderOptionsTestOptionsStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsStyleValidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValuesSlider[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_SliderStyle& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.style = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: style";
    };

    for (auto&& value : Fixtures::testFixtureEnumSliderStyleValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_SliderStyle>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsStyleInvalidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValuesSlider[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_SliderStyle& value) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.style = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: style";
    };

    for (auto&& value : Fixtures::testFixtureEnumSliderStyleInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_SliderStyle>(std::get<1>(value)));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsDirectionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsDirectionValidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Axis& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.direction = value;
        modifier_->setSliderOptions(node, &realInputValue);
        std::unique_ptr<JsonValue> jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: direction";
    };

    for (auto&& value : Fixtures::testFixtureEnumAxisValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Axis>(std::get<1>(value)), std::get<2>(value));
        return;
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsDirectionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsDirectionInvalidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Axis& value) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.direction = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: direction";
    };

    for (auto&& value : Fixtures::testFixtureEnumAxisInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Axis>(std::get<1>(value)));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsReverseValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsReverseValidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.reverse = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: reverse";
    };

    for (auto&& value : Fixtures::testFixtureBooleanValidValues) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Boolean>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSliderOptionsTestOptionsReverseInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderOptionsTestOptionsReverseInvalidValues, TestSize.Level1)
{
    Ark_SliderOptions initValueOptions;

    // Initial setup
    initValueOptions.value = Converter::ArkUnion<Opt_Union_F64_Bindable_F64, Ark_Float64>(
        std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_SliderOptions realInputValue = Converter::ArkValue<Opt_SliderOptions>(initValueOptions);
        Ark_SliderOptions& inputValueOptions = realInputValue.value;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.reverse = value;
        modifier_->setSliderOptions(node, &realInputValue);
        auto jsonValueFull = GetJsonValue(node);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_REVERSE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSliderOptions, attribute: reverse";
    };

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setBlockColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setBlockColorTestBlockColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockColorTestBlockColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBlockColor;

    // Initial setup
    initValueBlockColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueBlockColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueBlockColor = initValueBlockColor;

        inputValueBlockColor = value;
        auto color = Converter::ArkValue<Opt_ResourceColor>(inputValueBlockColor);
        modifier_->setBlockColor(node_, &color);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlockColor, attribute: blockColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setBlockColorTestBlockColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockColorTestBlockColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBlockColor;

    // Initial setup
    initValueBlockColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueBlockColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueBlockColor = initValueBlockColor;
        auto color = Converter::ArkValue<Opt_ResourceColor>(inputValueBlockColor);
        modifier_->setBlockColor(node_, &color);
        inputValueBlockColor = value;
        color = Converter::ArkValue<Opt_ResourceColor>(inputValueBlockColor);
        modifier_->setBlockColor(node_, &color);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockColor, attribute: blockColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTrackColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setTrackColorResourceColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackColorResourceColorTestValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueTrackColor;

    // Initial setup
    initValueTrackColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueTrackColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueTrackColor = initValueTrackColor;
        inputValueTrackColor = value;

        auto colorGradientUnion =
            Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(inputValueTrackColor);

        modifier_->setTrackColor(node_, &colorGradientUnion);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTrackColor, attribute: resourceColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setTrackColorResourceColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackColorResourceColorTestInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueTrackColor;

    // Initial setup
    initValueTrackColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueTrackColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueTrackColor = initValueTrackColor;

        auto colorGradientUnion =
            Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(inputValueTrackColor);

        modifier_->setTrackColor(node_, &colorGradientUnion);
        inputValueTrackColor = value;
        colorGradientUnion =
            Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(inputValueTrackColor);
        modifier_->setTrackColor(node_, &colorGradientUnion);

        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTrackColor, attribute: resourceColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

// Slider's component owner won't fix an issue in ToJsonValue (slider_paint_property.cpp) because of compatibility,
// so the test is disabled.
/*
 * @tc.name: setTrackColorLinearGradientTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackColorLinearGradientTestValidValues, TestSize.Level1)
{
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStopValues = {
        std::make_pair(Color::RED, Dimension(0.5f)),
        std::make_pair(Color::BLUE, Dimension(1.0f)),
    };

    Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(colorStopValues);
    auto colorGradientUnion =
        Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);

    modifier_->setTrackColor(node_, &colorGradientUnion);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
    auto gradientJsonArray = JsonUtil::ParseJsonString(resultStr);

    ASSERT_EQ(gradientJsonArray->GetArraySize(), colorStopValues.size());
    for (int i = 0; i < gradientJsonArray->GetArraySize(); i++) {
        auto itemJson = gradientJsonArray->GetArrayItem(i);
        auto colorValue = GetAttrValue<std::string>(itemJson, ATTRIBUTE_TRACK_COLOR_GRADIENT_COLOR_NAME);
        auto offsetValue = GetAttrValue<std::string>(itemJson, ATTRIBUTE_TRACK_COLOR_GRADIENT_OFFSET_NAME);
        EXPECT_EQ(colorValue, std::get<0>(colorStopValues.at(i)).value().ToString());
        EXPECT_EQ(offsetValue, std::to_string(std::get<1>(colorStopValues.at(i)).Value()));
    }
}

/*
 * @tc.name: setTrackColorLinearGradientTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackColorLinearGradientTestInvalidValues, TestSize.Level1)
{
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStopValues = {
        std::make_pair(std::nullopt, Dimension(0.5f)),
        std::make_pair(Color::BLUE, Dimension(1.0f)),
    };

    Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(colorStopValues);
    auto colorGradientUnion =
        Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);

    modifier_->setTrackColor(node_, &colorGradientUnion);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectedColorResourceColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setSelectedColorResourceColorTestValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueTrackColor;

    // Initial setup
    initValueTrackColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueTrackColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueTrackColor = initValueTrackColor;
        inputValueTrackColor = value;

        auto colorGradientUnion =
            Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(inputValueTrackColor);

        modifier_->setSelectedColor(node_, &colorGradientUnion);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSelectedColor, attribute: resourceColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSelectedColorResourceColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedColorResourceColorTestInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueTrackColor;

    // Initial setup
    initValueTrackColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueTrackColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueTrackColor = initValueTrackColor;

        auto colorGradientUnion =
            Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(inputValueTrackColor);

        modifier_->setSelectedColor(node_, &colorGradientUnion);
        inputValueTrackColor = value;
        colorGradientUnion =
            Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(inputValueTrackColor);
        modifier_->setSelectedColor(node_, &colorGradientUnion);

        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSelectedColor, attribute: resourceColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setSelectedColorLinearGradientTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedColorLinearGradientTestValidValues, TestSize.Level1)
{
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStopValues = {
        std::make_pair(Color::RED, Dimension(0.5f)),
        std::make_pair(Color::BLUE, Dimension(1.0f)),
    };

    Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(colorStopValues);
    auto colorGradientUnion =
        Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);

    modifier_->setSelectedColor(node_, &colorGradientUnion);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    auto gradientJsonArray = JsonUtil::ParseJsonString(resultStr);

    ASSERT_EQ(gradientJsonArray->GetArraySize(), colorStopValues.size());
    for (int i = 0; i < gradientJsonArray->GetArraySize(); i++) {
        auto itemJson = gradientJsonArray->GetArrayItem(i);
        auto colorValue = GetAttrValue<std::string>(itemJson, ATTRIBUTE_TRACK_COLOR_GRADIENT_COLOR_NAME);
        auto offsetValue = GetAttrValue<std::string>(itemJson, ATTRIBUTE_TRACK_COLOR_GRADIENT_OFFSET_NAME);
        EXPECT_EQ(colorValue, std::get<0>(colorStopValues.at(i)).value().ToString());
        EXPECT_EQ(offsetValue, std::to_string(std::get<1>(colorStopValues.at(i)).Value()));
    }
}

/*
 * @tc.name: setTrackColor1LinearGradientTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackColor1LinearGradientTestInvalidValues, TestSize.Level1)
{
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStopValues = {
        std::make_pair(std::nullopt, Dimension(0.5f)),
        std::make_pair(Color::BLUE, Dimension(1.0f)),
    };

    Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(colorStopValues);
    auto colorGradientUnion =
        Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);

    modifier_->setSelectedColor(node_, &colorGradientUnion);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setShowStepsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowStepsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_STEPS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_STEPS_DEFAULT_VALUE);
}

/*
 * @tc.name: setShowStepsTestShowStepsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowStepsTestShowStepsValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowSteps;

    // Initial setup
    initValueShowSteps = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueShowSteps](
                        const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueShowSteps = initValueShowSteps;

        inputValueShowSteps = value;
        auto showSteps = Converter::ArkValue<Opt_Boolean>(inputValueShowSteps);
        modifier_->setShowSteps(node_, &showSteps);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_STEPS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setShowSteps, attribute: showSteps";
    };

    for (auto&& value : Fixtures::testFixtureBooleanValidValues) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setShowTipsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_TIPS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_TIPS_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: setShowTipsTestShowTipsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestShowTipsValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowTips;
    Ark_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent = Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureStringResValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr realInputValue1 = Converter::ArkValue<Opt_ResourceStr>(initValueContent);

        inputValueShowTips = value;
        auto showTips = Converter::ArkValue<Opt_Boolean>(inputValueShowTips);
        modifier_->setShowTips(node_, &showTips, &realInputValue1);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_TIPS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setShowTips, attribute: showTips";
    };

    for (auto&& value : Fixtures::testFixtureBooleanValidValues) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setShowTipsTestContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestContentValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowTips;
    Ark_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent =
        Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureStringResValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const Opt_ResourceStr& value, const std::string& expectedStr) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr realInputValue1;
        Opt_ResourceStr& inputValueContent = realInputValue1;

        inputValueContent = value;
        auto showTips = Converter::ArkValue<Opt_Boolean>(inputValueShowTips);
        modifier_->setShowTips(node_, &showTips, &realInputValue1);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setShowTips, attribute: content";
    };

    for (auto&& value : Fixtures::testFixtureStringResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_ResourceStr, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
}

/*
 * @tc.name: setShowTipsTestContentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestContentInvalidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowTips;
    Ark_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent =
        Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureStringResValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const Opt_ResourceStr& value) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr realInputValue1;
        Opt_ResourceStr& inputValueContent = realInputValue1;
        auto showTips = Converter::ArkValue<Opt_Boolean>(inputValueShowTips);
        modifier_->setShowTips(node_, &showTips, &realInputValue1);
        inputValueContent = value;
        modifier_->setShowTips(node_, &showTips, &realInputValue1);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setShowTips, attribute: content";
    };

    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setTrackThicknessTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackThicknessTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE);
}

/*
 * @tc.name: setTrackThicknessTestTrackThicknessValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackThicknessTestTrackThicknessValidValues, TestSize.Level1)
{
    Ark_Length initValueTrackThickness;

    // Initial setup
    initValueTrackThickness =
        Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueTrackThickness](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueTrackThickness = initValueTrackThickness;

        inputValueTrackThickness = value;
        auto valueOpt = Converter::ArkValue<Opt_Length>(inputValueTrackThickness);
        modifier_->setTrackThickness(node_, &valueOpt);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTrackThickness, attribute: trackThickness";
    };

    for (auto&& value : Fixtures::testFixtureLengthNumNonNegValidValuesThicknessSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setTrackThicknessTestTrackThicknessInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackThicknessTestTrackThicknessInvalidValues, TestSize.Level1)
{
    Ark_Length initValueTrackThickness;

    // Initial setup
    initValueTrackThickness =
        Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueTrackThickness](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueTrackThickness = initValueTrackThickness;
        auto length = Converter::ArkValue<Opt_Length>(inputValueTrackThickness);
        modifier_->setTrackThickness(node_, &length);
        inputValueTrackThickness = value;
        length = Converter::ArkValue<Opt_Length>(inputValueTrackThickness);
        modifier_->setTrackThickness(node_, &length);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTrackThickness, attribute: trackThickness";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(value)));
    }
}

/*
 * @tc.name: setBlockBorderColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setBlockBorderColorTestBlockBorderColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockBorderColorTestBlockBorderColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBlockBorderColor;

    // Initial setup
    initValueBlockBorderColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueBlockBorderColor = initValueBlockBorderColor;

        inputValueBlockBorderColor = value;
        auto color = Converter::ArkValue<Opt_ResourceColor>(inputValueBlockBorderColor);
        modifier_->setBlockBorderColor(node_, &color);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlockBorderColor, attribute: blockBorderColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setBlockBorderColorTestBlockBorderColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderColorTestBlockBorderColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBlockBorderColor;

    // Initial setup
    initValueBlockBorderColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueBlockBorderColor = initValueBlockBorderColor;
        auto color = Converter::ArkValue<Opt_ResourceColor>(inputValueBlockBorderColor);
        modifier_->setBlockBorderColor(node_, &color);
        inputValueBlockBorderColor = value;
        color = Converter::ArkValue<Opt_ResourceColor>(inputValueBlockBorderColor);
        modifier_->setBlockBorderColor(node_, &color);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockBorderColor, attribute: blockBorderColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setBlockBorderWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setBlockBorderWidthTestBlockBorderWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderWidthTestBlockBorderWidthValidValues, TestSize.Level1)
{
    Ark_Length initValueBlockBorderWidth;

    // Initial setup
    initValueBlockBorderWidth = std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesSlider[0]);

    auto checkValue = [this, &initValueBlockBorderWidth](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueBlockBorderWidth = initValueBlockBorderWidth;

        inputValueBlockBorderWidth = value;
        auto length = Converter::ArkValue<Opt_Length>(inputValueBlockBorderWidth);
        modifier_->setBlockBorderWidth(node_, &length);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlockBorderWidth, attribute: blockBorderWidth";
    };

    for (auto&& value : Fixtures::testFixtureLengthNumNonNegValidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setBlockBorderWidthTestBlockBorderWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockBorderWidthTestBlockBorderWidthInvalidValues, TestSize.Level1)
{
    Ark_Length initValueBlockBorderWidth;

    // Initial setup
    initValueBlockBorderWidth =
        Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderWidth](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueBlockBorderWidth = initValueBlockBorderWidth;
        auto length = Converter::ArkValue<Opt_Length>(inputValueBlockBorderWidth);
        modifier_->setBlockBorderWidth(node_, &length);
        inputValueBlockBorderWidth = value;
        length = Converter::ArkValue<Opt_Length>(inputValueBlockBorderWidth);
        modifier_->setBlockBorderWidth(node_, &length);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockBorderWidth, attribute: blockBorderWidth";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(value)));
    }
}

/*
 * @tc.name: setStepColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setStepColorTestStepColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setStepColorTestStepColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueStepColor;

    // Initial setup
    initValueStepColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueStepColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueStepColor = initValueStepColor;

        inputValueStepColor = value;
        auto color = Converter::ArkValue<Opt_ResourceColor>(inputValueStepColor);
        modifier_->setStepColor(node_, &color);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setStepColor, attribute: stepColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setStepColorTestStepColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepColorTestStepColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueStepColor;

    // Initial setup
    initValueStepColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(
        std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueStepColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueStepColor = initValueStepColor;
        auto color = Converter::ArkValue<Opt_ResourceColor>(inputValueStepColor);
        modifier_->setStepColor(node_, &color);
        inputValueStepColor = value;
        color = Converter::ArkValue<Opt_ResourceColor>(inputValueStepColor);
        modifier_->setStepColor(node_, &color);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setStepColor, attribute: stepColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTrackBorderRadiusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackBorderRadiusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE);
}

/*
 * @tc.name: setTrackBorderRadiusTestTrackBorderRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackBorderRadiusTestTrackBorderRadiusValidValues, TestSize.Level1)
{
    Ark_Length initValueTrackBorderRadius;

    // Initial setup
    initValueTrackBorderRadius = std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesSlider[0]);

    auto checkValue = [this, &initValueTrackBorderRadius](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueTrackBorderRadius = initValueTrackBorderRadius;

        inputValueTrackBorderRadius = value;
        auto length = Converter::ArkValue<Opt_Length>(inputValueTrackBorderRadius);
        modifier_->setTrackBorderRadius(node_, &length);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTrackBorderRadius, attribute: trackBorderRadius";
    };

    for (auto&& value : Fixtures::testFixtureLengthNumNonNegValidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setTrackBorderRadiusTestTrackBorderRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackBorderRadiusTestTrackBorderRadiusInvalidValues, TestSize.Level1)
{
    Ark_Length initValueTrackBorderRadius;

    // Initial setup
    initValueTrackBorderRadius =
        Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueTrackBorderRadius](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueTrackBorderRadius = initValueTrackBorderRadius;
        auto length = Converter::ArkValue<Opt_Length>(inputValueTrackBorderRadius);
        modifier_->setTrackBorderRadius(node_, &length);
        inputValueTrackBorderRadius = value;
        length = Converter::ArkValue<Opt_Length>(inputValueTrackBorderRadius);
        modifier_->setTrackBorderRadius(node_, &length);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTrackBorderRadius, attribute: trackBorderRadius";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(value)));
    }
}

/*
 * @tc.name: setBlockSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultBlockSize =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
    std::string resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_WIDTH_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_HEIGHT_DEFAULT_VALUE);
}

/*
 * @tc.name: setBlockSizeTestBlockSizeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockSizeTestBlockSizeWidthValidValues, TestSize.Level1)
{
    Ark_SizeOptions initValueBlockSize;

    // Initial setup
    initValueBlockSize.width = Converter::ArkValue<Opt_Length>(
        std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesBlockSizeSlider[0]));
    initValueBlockSize.height = Converter::ArkValue<Opt_Length>(
        std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesBlockSizeSlider[0]));

    auto checkValue = [this, &initValueBlockSize](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        inputValueBlockSize.width = value;
        auto size = Converter::ArkValue<Opt_SizeOptions>(inputValueBlockSize);
        modifier_->setBlockSize(node_, &size);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlockSize, attribute: width";
    };

    for (auto&& value : Fixtures::testFixtureLengthNumNonNegValidValuesBlockSizeSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Length>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setBlockSizeTestBlockSizeWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockSizeTestBlockSizeWidthInvalidValues, TestSize.Level1)
{
    Ark_SizeOptions initValueBlockSize;

    // Initial setup
    initValueBlockSize.width =
        Converter::ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height =
        Converter::ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;
        auto size = Converter::ArkValue<Opt_SizeOptions>(inputValueBlockSize);
        modifier_->setBlockSize(node_, &size);
        inputValueBlockSize.width = value;
        size = Converter::ArkValue<Opt_SizeOptions>(inputValueBlockSize);
        modifier_->setBlockSize(node_, &size);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockSize, attribute: width";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_Length, Ark_String>(std::get<1>(value)));
    }
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBlockSizeTestBlockSizeHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockSizeTestBlockSizeHeightValidValues, TestSize.Level1)
{
    Ark_SizeOptions initValueBlockSize;

    // Initial setup
    initValueBlockSize.width = Converter::ArkValue<Opt_Length>(
        std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesBlockSizeSlider[0]));
    initValueBlockSize.height = Converter::ArkValue<Opt_Length>(
        std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesBlockSizeSlider[0]));

    auto checkValue = [this, &initValueBlockSize](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        inputValueBlockSize.height = value;
        auto options = Converter::ArkValue<Opt_SizeOptions>(inputValueBlockSize);
        modifier_->setBlockSize(node_, &options);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlockSize, attribute: height";
    };

    for (auto&& value : Fixtures::testFixtureLengthNumNonNegValidValuesBlockSizeSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Length>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setBlockSizeTestBlockSizeHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockSizeTestBlockSizeHeightInvalidValues, TestSize.Level1)
{
    Ark_SizeOptions initValueBlockSize;

    // Initial setup
    initValueBlockSize.width =
        Converter::ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height =
        Converter::ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;
        auto options = Converter::ArkValue<Opt_SizeOptions>(inputValueBlockSize);
        modifier_->setBlockSize(node_, &options);
        inputValueBlockSize.height = value;
        options = Converter::ArkValue<Opt_SizeOptions>(inputValueBlockSize);
        modifier_->setBlockSize(node_, &options);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_HEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockSize, attribute: height";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Opt_Length, Ark_String>(std::get<1>(value)));
    }
    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBlockStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_STYLE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_STYLE_TYPE_DEFAULT_VALUE);
}

/*
 * @tc.name: setBlockStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setBlockStyleTestValidValues, TestSize.Level1)
{
    Ark_SliderBlockStyle initValueBlockStyle;

    // Initial setup
    initValueBlockStyle.type = Converter::ArkValue<Ark_SliderBlockType>(
        std::get<1>(Fixtures::testFixtureEnumSliderBlockTypeValidValuesSlider[0]));
    initValueBlockStyle.image = Converter::ArkValue<Opt_ResourceStr>();

    auto checkValue = [this, &initValueBlockStyle](const std::string& input, const Ark_SliderBlockType& value,
        const std::string& expectedStr) {
        Ark_SliderBlockStyle inputValueBlockStyle = initValueBlockStyle;

        inputValueBlockStyle.type = value;
        auto style = Converter::ArkValue<Opt_SliderBlockStyle>(inputValueBlockStyle);
        modifier_->setBlockStyle(node_, &style);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_STYLE_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBlockSize, attribute: height";
    };

    for (auto&& value : Fixtures::testFixtureEnumSliderBlockTypeValidValuesSlider) {checkValue(std::get<0>(value),
        Converter::ArkValue<Ark_SliderBlockType>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setStepSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE);
}

/*
 * @tc.name: setStepSizeTestStepSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepSizeTestStepSizeValidValues, TestSize.Level1)
{
    Ark_Length initValueStepSize;

    // Initial setup
    initValueStepSize = std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesSlider[0]);

    auto checkValue = [this, &initValueStepSize](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueStepSize = initValueStepSize;

        inputValueStepSize = value;
        auto stepSize = Converter::ArkValue<Opt_Length>(inputValueStepSize);
        modifier_->setStepSize(node_, &stepSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setStepSize, attribute: stepSize";
    };

    for (auto&& value : Fixtures::testFixtureLengthNumNonNegValidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setStepSizeTestStepSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setStepSizeTestStepSizeInvalidValues, TestSize.Level1)
{
    Ark_Length initValueStepSize;

    // Initial setup
    initValueStepSize = std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesSlider[0]);

    auto checkValue = [this, &initValueStepSize](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueStepSize = initValueStepSize;
        auto stepSize = Converter::ArkValue<Opt_Length>(inputValueStepSize);
        modifier_->setStepSize(node_, &stepSize);
        inputValueStepSize = value;
        stepSize = Converter::ArkValue<Opt_Length>(inputValueStepSize);
        modifier_->setStepSize(node_, &stepSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setStepSize, attribute: stepSize";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_Length, Ark_String>(std::get<1>(value)));
    }
}

/*
 * @tc.name: setSliderInteractionModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderInteractionModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SLIDER_INTERACTION_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setSliderInteractionModeTestSliderInteractionModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderInteractionModeTestSliderInteractionModeValidValues, TestSize.Level1)
{
    Ark_SliderInteraction initValueSliderInteractionMode;

    // Initial setup
    initValueSliderInteractionMode = std::get<1>(Fixtures::testFixtureEnumSliderInteractionValidValues[0]);

    auto checkValue = [this, &initValueSliderInteractionMode](const std::string& input,
                          const enum Ark_SliderInteraction& value, const std::string& expectedStr) {
        Ark_SliderInteraction inputValueSliderInteractionMode = initValueSliderInteractionMode;

        inputValueSliderInteractionMode = value;
        auto sliderInteractionMode = Converter::ArkValue<Opt_SliderInteraction>(inputValueSliderInteractionMode);
        modifier_->setSliderInteractionMode(node_, &sliderInteractionMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSliderInteractionMode, attribute: sliderInteractionMode";
    };

    for (auto&& value : Fixtures::testFixtureEnumSliderInteractionValidValues) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setSliderInteractionModeTestSliderInteractionModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSliderInteractionModeTestSliderInteractionModeInvalidValues, TestSize.Level1)
{
    Ark_SliderInteraction initValueSliderInteractionMode;

    // Initial setup
    initValueSliderInteractionMode = std::get<1>(Fixtures::testFixtureEnumSliderInteractionValidValues[0]);

    auto checkValue = [this, &initValueSliderInteractionMode](
                          const std::string& input, const enum Ark_SliderInteraction& value) {
        Ark_SliderInteraction inputValueSliderInteractionMode = initValueSliderInteractionMode;
        auto sliderInteractionMode = Converter::ArkValue<Opt_SliderInteraction>(inputValueSliderInteractionMode);
        modifier_->setSliderInteractionMode(node_, &sliderInteractionMode);
        inputValueSliderInteractionMode = value;
        sliderInteractionMode = Converter::ArkValue<Opt_SliderInteraction>(inputValueSliderInteractionMode);
        modifier_->setSliderInteractionMode(node_, &sliderInteractionMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDER_INTERACTION_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSliderInteractionMode, attribute: sliderInteractionMode";
    };

    for (auto&& value : Fixtures::testFixtureEnumSliderInteractionInvalidValues) {
        checkValue(std::get<0>(value), std::get<1>(value));
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
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE);
}

/*
 * @tc.name: setMinResponsiveDistanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinResponsiveDistanceValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        modifier_->setMinResponsiveDistance(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto&& value : Fixtures::testFixtureNumberResponsiveDistanceValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setMinResponsiveDistanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinResponsiveDistanceInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueMinResponsiveDistance = Converter::ArkValue<Opt_Float64>(
        std::get<1>(Fixtures::testFixtureNumberResponsiveDistanceValidValuesSlider[0]));

    auto checkValue = [this, &initValueMinResponsiveDistance](
                          const std::string& input, const Opt_Float64& value) {
        auto inputValueMinResponsiveDistance = initValueMinResponsiveDistance;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        inputValueMinResponsiveDistance = value;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto&& value : Fixtures::testFixtureNumberValueInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)));
    }
    checkValue("undefined", Converter::ArkValue<Opt_Float64>());
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

    std::string resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_FROM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_FROM_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_TO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_TO_DEFAULT_VALUE);
}

/*
 * @tc.name: setSlideRangeTestSlideRangeFromValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSlideRangeTestSlideRangeFromValidValues, TestSize.Level1)
{
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        inputValueSlideRange.from = value;
        auto slideRange = Converter::ArkValue<Opt_SlideRange>(inputValueSlideRange);
        modifier_->setSlideRange(node_, &slideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_FROM_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSlideRange, attribute: from";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeFromValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSlideRangeTestSlideRangeFromInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSlideRangeTestSlideRangeFromInvalidValues, TestSize.Level1)
{
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Float64& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;
        auto slideRange = Converter::ArkValue<Opt_SlideRange>(inputValueSlideRange);
        modifier_->setSlideRange(node_, &slideRange);
        inputValueSlideRange.from = value;
        slideRange = Converter::ArkValue<Opt_SlideRange>(inputValueSlideRange);
        modifier_->setSlideRange(node_, &slideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_FROM_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_FROM_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSlideRange, attribute: from";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeFromInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Float64>());
}

/*
 * @tc.name: setSlideRangeTestSlideRangeToValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSlideRangeTestSlideRangeToValidValues, TestSize.Level1)
{
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const Opt_Float64& value, const std::string& expectedStr) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        inputValueSlideRange.to = value;
        auto slideRange = Converter::ArkValue<Opt_SlideRange>(inputValueSlideRange);
        modifier_->setSlideRange(node_, &slideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_TO_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSlideRange, attribute: to";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeToValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)), std::get<2>(value));
    }
}

/*
 * @tc.name: setSlideRangeTestSlideRangeToInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSlideRangeTestSlideRangeToInvalidValues, TestSize.Level1)
{
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Float64>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Float64& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;
        auto slideRange = Converter::ArkValue<Opt_SlideRange>(inputValueSlideRange);
        modifier_->setSlideRange(node_, &slideRange);
        inputValueSlideRange.to = value;
        slideRange = Converter::ArkValue<Opt_SlideRange>(inputValueSlideRange);
        modifier_->setSlideRange(node_, &slideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_TO_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_TO_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSlideRange, attribute: to";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeToInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Float64>(std::get<1>(value)));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Float64>());
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of SliderModifier.setOnChange
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        float value;
        std::optional<int32_t> mode;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onChangeCallback = [](Ark_Int32 nodeId, const Ark_Float64 value, Ark_SliderChangeMode mode) {
        checkEvent = {
            .nodeId = nodeId,
            .value = Converter::Convert<float>(value),
            .mode = EnumToInt(Converter::OptConvert<SliderModel::SliderChangeMode>(mode)),
        };
    };
    auto optCallback = Converter::ArkCallback<Opt_Callback_F64_SliderChangeMode_Void>(onChangeCallback,
         frameNode->GetId());
    modifier_->setOnChange(node_, &optCallback);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(10, 0);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_FLOAT_EQ(checkEvent->value, 10.);
    EXPECT_EQ(checkEvent->mode.value(), 0);
    eventHub->FireChangeEvent(20, 1);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_FLOAT_EQ(checkEvent->value, 20.);
    EXPECT_EQ(checkEvent->mode.value(), 1);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventValueImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setOnChangeEventValueImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        float value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    Callback_Number_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Number value) {
            checkEvent = {
                .nodeId = nodeId,
                .value = Converter::Convert<float>(value)
            };
        }
    };

    modifier_->set_onChangeEvent_value(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(55.4f, 0);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_NEAR(checkEvent->value, 55.4f, FLT_EPSILON);
    eventHub->FireChangeEvent(10.2f, 3);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_NEAR(checkEvent->value, 10.2f, FLT_EPSILON);
}
#ifdef SUPPORT_DIGITAL_CROWN
std::vector<std::tuple<std::string, Opt_CrownSensitivity, std::string>> crownSensitivityTestPlan = {
    { "CrownSensitivity.LOW", Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_LOW),
        "CrownSensitivity.LOW" },
    { "CrownSensitivity.MEDIUM", Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_MEDIUM),
        "CrownSensitivity.MEDIUM" },
    { "CrownSensitivity.HIGH", Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_HIGH),
        "CrownSensitivity.HIGH" },
    { "-1", Converter::ArkValue<Opt_CrownSensitivity>(static_cast<Ark_CrownSensitivity>(-1)),
        ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE },
    { "INT_MAX", Converter::ArkValue<Opt_CrownSensitivity>(static_cast<Ark_CrownSensitivity>(INT_MAX)),
        ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE },
    { "Ark_Empty", Converter::ArkValue<Opt_CrownSensitivity>(static_cast<Ark_CrownSensitivity>(INT_MAX)),
        ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE },
    { "CrownSensitivity.MEDIUM", Converter::ArkValue<Opt_CrownSensitivity>(ARK_CROWN_SENSITIVITY_MEDIUM),
        "CrownSensitivity.MEDIUM" },
};
#endif

/*
 * @tc.name: setDigitalCrownSensitivityDefaultValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setDigitalCrownSensitivityDefaultValuesTest, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE)
        << "Default value for attribute 'digitalCrownSensitivity'";
}

/*
 * @tc.name: setDigitalCrownSensitivityValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setDigitalCrownSensitivityValuesTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDigitalCrownSensitivity, nullptr);
    auto checkValue = [this](
                        const std::string& input, const std::string& expectedStr, const Opt_CrownSensitivity& value) {
        Opt_CrownSensitivity inputValueDigitalCrownSensitivity = value;
        modifier_->setDigitalCrownSensitivity(node_, &inputValueDigitalCrownSensitivity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input
                                        << ", method: setDigitalCrownSensitivity, attribute: digitalCrownSensitivity";
    };
    for (auto& [input, value, expected] : crownSensitivityTestPlan) {
        checkValue(input, expected, value);
    }
}
#endif

/**
 * @tc.name: setEnableHapticFeedbackTest
 * @tc.desc: Check backToTop method of ScrollableCommonMethod modifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setEnableHapticFeedbackTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableHapticFeedback, nullptr);
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE);
    auto enableHapticFeedback = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnableHapticFeedback(node_, &enableHapticFeedback);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, EXPECTED_FALSE);
    enableHapticFeedback = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnableHapticFeedback(node_, &enableHapticFeedback);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, EXPECTED_TRUE);
}
} // namespace OHOS::Ace::NG
