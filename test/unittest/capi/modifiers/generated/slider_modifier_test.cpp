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

#include "core/components/slider/slider_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_TRACK_COLOR_NAME = "trackColor";
const auto ATTRIBUTE_BLOCK_SIZE_NAME = "blockSize";
const auto ATTRIBUTE_BLOCK_STYLE_NAME = "blockStyle";
const auto ATTRIBUTE_SLIDE_RANGE_NAME = "slideRange";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_MIN_NAME = "min";
const auto ATTRIBUTE_MIN_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_MAX_NAME = "max";
const auto ATTRIBUTE_MAX_DEFAULT_VALUE = "100";
const auto ATTRIBUTE_STEP_NAME = "step";
const auto ATTRIBUTE_STEP_DEFAULT_VALUE = "1";
const auto ATTRIBUTE_STYLE_NAME = "style";
const auto ATTRIBUTE_STYLE_DEFAULT_VALUE = "SliderStyle.OutSet";
const auto ATTRIBUTE_DIRECTION_NAME = "direction";
const auto ATTRIBUTE_DIRECTION_DEFAULT_VALUE = "Axis.Horizontal";
const auto ATTRIBUTE_REVERSE_NAME = "reverse";
const auto ATTRIBUTE_REVERSE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_BLOCK_COLOR_NAME = "blockColor";
const auto ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TRACK_COLOR_I_ANGLE_NAME = "angle";
const auto ATTRIBUTE_TRACK_COLOR_I_ANGLE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TRACK_COLOR_I_DIRECTION_NAME = "direction";
const auto ATTRIBUTE_TRACK_COLOR_I_DIRECTION_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TRACK_COLOR_I_COLORS_NAME = "colors";
const auto ATTRIBUTE_TRACK_COLOR_I_COLORS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TRACK_COLOR_I_REPEATING_NAME = "repeating";
const auto ATTRIBUTE_TRACK_COLOR_I_REPEATING_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_MIN_LABEL_NAME = "minLabel";
const auto ATTRIBUTE_MIN_LABEL_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_LABEL_NAME = "maxLabel";
const auto ATTRIBUTE_MAX_LABEL_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_STEPS_NAME = "showSteps";
const auto ATTRIBUTE_SHOW_STEPS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_TRACK_THICKNESS_NAME = "trackThickness";
const auto ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_BLOCK_BORDER_COLOR_NAME = "blockBorderColor";
const auto ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE = "#00000000";
const auto ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME = "blockBorderWidth";
const auto ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_STEP_COLOR_NAME = "stepColor";
const auto ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TRACK_BORDER_RADIUS_NAME = "trackBorderRadius";
const auto ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME = "selectedBorderRadius";
const auto ATTRIBUTE_SELECTED_BORDER_RADIUS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_BLOCK_SIZE_I_WIDTH_NAME = "width";
const auto ATTRIBUTE_BLOCK_SIZE_I_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_NAME = "height";
const auto ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_BLOCK_STYLE_I_TYPE_NAME = "type";
const auto ATTRIBUTE_BLOCK_STYLE_I_TYPE_DEFAULT_VALUE = "SliderBlockType.DEFAULT";
const auto ATTRIBUTE_BLOCK_STYLE_I_IMAGE_NAME = "image";
const auto ATTRIBUTE_BLOCK_STYLE_I_IMAGE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_BLOCK_STYLE_I_SHAPE_NAME = "shape";
const auto ATTRIBUTE_BLOCK_STYLE_I_SHAPE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STEP_SIZE_NAME = "stepSize";
const auto ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME = "sliderInteractionMode";
const auto ATTRIBUTE_SLIDER_INTERACTION_MODE_DEFAULT_VALUE = "SliderInteraction.SLIDE_AND_CLICK";
const auto ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME = "minResponsiveDistance";
const auto ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_SLIDE_RANGE_I_FROM_NAME = "from";
const auto ATTRIBUTE_SLIDE_RANGE_I_FROM_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SLIDE_RANGE_I_TO_NAME = "to";
const auto ATTRIBUTE_SLIDE_RANGE_I_TO_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SHOW_TIPS_NAME = "showTips";
const auto ATTRIBUTE_SHOW_TIPS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_CONTENT_NAME = "content";
const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "";
} // namespace

class SliderModifierTest : public ModifierTestBase<GENERATED_ArkUISliderModifier,
                               &GENERATED_ArkUINodeModifiers::getSliderModifier, GENERATED_ARKUI_SLIDER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SliderTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

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
    Ark_ResourceColor initValueBlockColor;

    // Initial setup
    initValueBlockColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockColor](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueBlockColor = initValueBlockColor;

        inputValueBlockColor = value;
        modifier_->setBlockColor(node_, &inputValueBlockColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockColor, attribute: blockColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_String>(value));
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
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueBlockColor = initValueBlockColor;

        modifier_->setBlockColor(node_, &inputValueBlockColor);
        inputValueBlockColor = value;
        modifier_->setBlockColor(node_, &inputValueBlockColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockColor, attribute: blockColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTrackColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setTrackColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTrackColor =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_COLOR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTrackColor, ATTRIBUTE_TRACK_COLOR_I_ANGLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_I_ANGLE_DEFAULT_VALUE) <<
        "Default value for attribute 'trackColor.LinearGradient.angle'";

    resultStr = GetAttrValue<std::string>(resultTrackColor, ATTRIBUTE_TRACK_COLOR_I_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_I_DIRECTION_DEFAULT_VALUE) <<
        "Default value for attribute 'trackColor.LinearGradient.direction'";

    resultStr = GetAttrValue<std::string>(resultTrackColor, ATTRIBUTE_TRACK_COLOR_I_COLORS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_I_COLORS_DEFAULT_VALUE) <<
        "Default value for attribute 'trackColor.LinearGradient.colors'";

    resultStr = GetAttrValue<std::string>(resultTrackColor, ATTRIBUTE_TRACK_COLOR_I_REPEATING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_COLOR_I_REPEATING_DEFAULT_VALUE) <<
        "Default value for attribute 'trackColor.LinearGradient.repeating'";
}

/*
 * @tc.name: setTrackColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setTrackColorTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
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
    Ark_ResourceColor initValueSelectedColor;

    // Initial setup
    initValueSelectedColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedColor](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueSelectedColor = initValueSelectedColor;

        inputValueSelectedColor = value;
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedColor, attribute: selectedColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedColorTestSelectedColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedColorTestSelectedColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueSelectedColor;

    // Initial setup
    initValueSelectedColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueSelectedColor = initValueSelectedColor;

        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        inputValueSelectedColor = value;
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedColor, attribute: selectedColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMinLabelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setMinLabelTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_LABEL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_LABEL_DEFAULT_VALUE) << "Default value for attribute 'minLabel'";
}

/*
 * @tc.name: setMinLabelTestMinLabelValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setMinLabelTestMinLabelValidValues, TestSize.Level1)
{
    Ark_String initValueMinLabel;

    // Initial setup
    initValueMinLabel = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueMinLabel](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueMinLabel = initValueMinLabel;

        inputValueMinLabel = value;
        modifier_->setMinLabel(node_, &inputValueMinLabel);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_LABEL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinLabel, attribute: minLabel";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMaxLabelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setMaxLabelTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LABEL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LABEL_DEFAULT_VALUE) << "Default value for attribute 'maxLabel'";
}

/*
 * @tc.name: setMaxLabelTestMaxLabelValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setMaxLabelTestMaxLabelValidValues, TestSize.Level1)
{
    Ark_String initValueMaxLabel;

    // Initial setup
    initValueMaxLabel = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueMaxLabel](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueMaxLabel = initValueMaxLabel;

        inputValueMaxLabel = value;
        modifier_->setMaxLabel(node_, &inputValueMaxLabel);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LABEL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLabel, attribute: maxLabel";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_Boolean initValueShowSteps;

    // Initial setup
    initValueShowSteps = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueShowSteps](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueShowSteps = initValueShowSteps;

        inputValueShowSteps = value;
        modifier_->setShowSteps(node_, inputValueShowSteps);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_STEPS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowSteps, attribute: showSteps";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_Length initValueTrackThickness;

    // Initial setup
    initValueTrackThickness = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueTrackThickness](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueTrackThickness = initValueTrackThickness;

        inputValueTrackThickness = value;
        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTrackThickness, attribute: trackThickness";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, value);
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
    initValueTrackThickness = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueTrackThickness](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueTrackThickness = initValueTrackThickness;

        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        inputValueTrackThickness = value;
        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTrackThickness, attribute: trackThickness";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, value);
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
    Ark_ResourceColor initValueBlockBorderColor;

    // Initial setup
    initValueBlockBorderColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderColor](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueBlockBorderColor = initValueBlockBorderColor;

        inputValueBlockBorderColor = value;
        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockBorderColor, attribute: blockBorderColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_String>(value));
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
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueBlockBorderColor = initValueBlockBorderColor;

        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        inputValueBlockBorderColor = value;
        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockBorderColor, attribute: blockBorderColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
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
    Ark_Length initValueBlockBorderWidth;

    // Initial setup
    initValueBlockBorderWidth = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueBlockBorderWidth](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueBlockBorderWidth = initValueBlockBorderWidth;

        inputValueBlockBorderWidth = value;
        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockBorderWidth, attribute: blockBorderWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, value);
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
    initValueBlockBorderWidth = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueBlockBorderWidth](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueBlockBorderWidth = initValueBlockBorderWidth;

        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        inputValueBlockBorderWidth = value;
        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockBorderWidth, attribute: blockBorderWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, value);
    }
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
    Ark_ResourceColor initValueStepColor;

    // Initial setup
    initValueStepColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueStepColor](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueStepColor = initValueStepColor;

        inputValueStepColor = value;
        modifier_->setStepColor(node_, &inputValueStepColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStepColor, attribute: stepColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_String>(value));
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
    initValueStepColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueStepColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueStepColor = initValueStepColor;

        modifier_->setStepColor(node_, &inputValueStepColor);
        inputValueStepColor = value;
        modifier_->setStepColor(node_, &inputValueStepColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStepColor, attribute: stepColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
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
    Ark_Length initValueTrackBorderRadius;

    // Initial setup
    initValueTrackBorderRadius = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueTrackBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueTrackBorderRadius = initValueTrackBorderRadius;

        inputValueTrackBorderRadius = value;
        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTrackBorderRadius, attribute: trackBorderRadius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, value);
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
    initValueTrackBorderRadius = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueTrackBorderRadius](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueTrackBorderRadius = initValueTrackBorderRadius;

        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        inputValueTrackBorderRadius = value;
        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTrackBorderRadius, attribute: trackBorderRadius";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, value);
    }
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
    Ark_Length initValueSelectedBorderRadius;

    // Initial setup
    initValueSelectedBorderRadius = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueSelectedBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueSelectedBorderRadius = initValueSelectedBorderRadius;

        inputValueSelectedBorderRadius = value;
        modifier_->setSelectedBorderRadius(node_, &inputValueSelectedBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectedBorderRadius, attribute: selectedBorderRadius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSelectedBorderRadiusTestSelectedBorderRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setSelectedBorderRadiusTestSelectedBorderRadiusInvalidValues, TestSize.Level1)
{
    Ark_Length initValueSelectedBorderRadius;

    // Initial setup
    initValueSelectedBorderRadius = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueSelectedBorderRadius](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueSelectedBorderRadius = initValueSelectedBorderRadius;

        modifier_->setSelectedBorderRadius(node_, &inputValueSelectedBorderRadius);
        inputValueSelectedBorderRadius = value;
        modifier_->setSelectedBorderRadius(node_, &inputValueSelectedBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BORDER_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectedBorderRadius, attribute: selectedBorderRadius";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, value);
    }
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
    Ark_SizeOptions initValueBlockSize;

    // Initial setup
    initValueBlockSize.width = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        inputValueBlockSize.width = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.width";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
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
    initValueBlockSize.width = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        modifier_->setBlockSize(node_, &inputValueBlockSize);
        inputValueBlockSize.width = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_I_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.width";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
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
    Ark_SizeOptions initValueBlockSize;

    // Initial setup
    initValueBlockSize.width = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        inputValueBlockSize.height = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.height";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
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
    initValueBlockSize.width = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height = ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        modifier_->setBlockSize(node_, &inputValueBlockSize);
        inputValueBlockSize.height = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_I_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlockSize, attribute: blockSize.height";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBlockStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultBlockStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultBlockStyle, ATTRIBUTE_BLOCK_STYLE_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_STYLE_I_TYPE_DEFAULT_VALUE) << "Default value for attribute 'blockStyle.type'";

    resultStr = GetAttrValue<std::string>(resultBlockStyle, ATTRIBUTE_BLOCK_STYLE_I_IMAGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_STYLE_I_IMAGE_DEFAULT_VALUE) <<
        "Default value for attribute 'blockStyle.image'";

    resultStr = GetAttrValue<std::string>(resultBlockStyle, ATTRIBUTE_BLOCK_STYLE_I_SHAPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_STYLE_I_SHAPE_DEFAULT_VALUE) <<
        "Default value for attribute 'blockStyle.shape'";
}

/*
 * @tc.name: setBlockStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, DISABLED_setBlockStyleTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
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
    Ark_Length initValueStepSize;

    // Initial setup
    initValueStepSize = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueStepSize](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueStepSize = initValueStepSize;

        inputValueStepSize = value;
        modifier_->setStepSize(node_, &inputValueStepSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStepSize, attribute: stepSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, value);
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
    initValueStepSize = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueStepSize](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueStepSize = initValueStepSize;

        modifier_->setStepSize(node_, &inputValueStepSize);
        inputValueStepSize = value;
        modifier_->setStepSize(node_, &inputValueStepSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStepSize, attribute: stepSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, value);
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
    Ark_SliderInteraction initValueSliderInteractionMode;

    // Initial setup
    initValueSliderInteractionMode = std::get<1>(Fixtures::testFixtureEnumSliderInteractionValidValues[0]);

    auto checkValue = [this, &initValueSliderInteractionMode](const std::string& input, const std::string& expectedStr,
                          const Ark_SliderInteraction& value) {
        Ark_SliderInteraction inputValueSliderInteractionMode = initValueSliderInteractionMode;

        inputValueSliderInteractionMode = value;
        modifier_->setSliderInteractionMode(node_, inputValueSliderInteractionMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSliderInteractionMode, attribute: sliderInteractionMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumSliderInteractionValidValues) {
        checkValue(input, expected, value);
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
                          const std::string& input, const Ark_SliderInteraction& value) {
        Ark_SliderInteraction inputValueSliderInteractionMode = initValueSliderInteractionMode;

        modifier_->setSliderInteractionMode(node_, inputValueSliderInteractionMode);
        inputValueSliderInteractionMode = value;
        modifier_->setSliderInteractionMode(node_, inputValueSliderInteractionMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDER_INTERACTION_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSliderInteractionMode, attribute: sliderInteractionMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumSliderInteractionInvalidValues) {
        checkValue(input, value);
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
    Ark_Number initValueMinResponsiveDistance;

    // Initial setup
    initValueMinResponsiveDistance = std::get<1>(Fixtures::testFixtureNumberNonNegValidValues[0]);

    auto checkValue = [this, &initValueMinResponsiveDistance](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueMinResponsiveDistance = initValueMinResponsiveDistance;

        inputValueMinResponsiveDistance = value;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMinResponsiveDistanceTestMinResponsiveDistanceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinResponsiveDistanceTestMinResponsiveDistanceInvalidValues, TestSize.Level1)
{
    Ark_Number initValueMinResponsiveDistance;

    // Initial setup
    initValueMinResponsiveDistance = std::get<1>(Fixtures::testFixtureNumberNonNegValidValues[0]);

    auto checkValue = [this, &initValueMinResponsiveDistance](const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueMinResponsiveDistance = initValueMinResponsiveDistance;

        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        inputValueMinResponsiveDistance = value;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegInvalidValues) {
        checkValue(input, value);
    }
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
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    initValueSlideRange.to = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        inputValueSlideRange.from = value;
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
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    initValueSlideRange.to = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Number& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        modifier_->setSlideRange(node_, &inputValueSlideRange);
        inputValueSlideRange.from = value;
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
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    initValueSlideRange.to = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        inputValueSlideRange.to = value;
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
    Ark_SlideRange initValueSlideRange;

    // Initial setup
    initValueSlideRange.from =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    initValueSlideRange.to = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntCeilValidValues[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Number& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        modifier_->setSlideRange(node_, &inputValueSlideRange);
        inputValueSlideRange.to = value;
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
 * @tc.name: setShowTipsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_TIPS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_TIPS_DEFAULT_VALUE) << "Default value for attribute 'showTips'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) << "Default value for attribute 'content'";
}

/*
 * @tc.name: setShowTipsTestShowTipsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setShowTipsTestShowTipsValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowTips;
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        inputValueShowTips = value;
        modifier_->setShowTips(node_, inputValueShowTips, &inputValueContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_TIPS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowTips, attribute: showTips";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
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
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        inputValueContent = value;
        modifier_->setShowTips(node_, inputValueShowTips, &inputValueContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setShowTips, attribute: content";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
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
    Opt_ResourceStr initValueContent;

    // Initial setup
    initValueShowTips = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueContent = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueShowTips, &initValueContent](
                          const std::string& input, const Opt_ResourceStr& value) {
        Ark_Boolean inputValueShowTips = initValueShowTips;
        Opt_ResourceStr inputValueContent = initValueContent;

        modifier_->setShowTips(node_, inputValueShowTips, &inputValueContent);
        inputValueContent = value;
        modifier_->setShowTips(node_, inputValueShowTips, &inputValueContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowTips, attribute: content";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}
} // namespace OHOS::Ace::NG
