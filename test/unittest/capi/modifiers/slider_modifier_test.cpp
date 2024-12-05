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
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components/slider/slider_theme.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const auto ATTRIBUTE_BLOCK_SIZE_NAME = "blockSize";
const auto ATTRIBUTE_SLIDE_RANGE_NAME = "slideRange";
const auto ATTRIBUTE_CONSTRUCTOR_NAME = "constructor";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_MIN_NAME = "min";
const auto ATTRIBUTE_MIN_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_MAX_NAME = "max";
const auto ATTRIBUTE_MAX_DEFAULT_VALUE = "100.000000";
const auto ATTRIBUTE_STEP_NAME = "step";
const auto ATTRIBUTE_STEP_DEFAULT_VALUE = "1.000000";
const auto ATTRIBUTE_STYLE_NAME = "style";
const auto ATTRIBUTE_STYLE_DEFAULT_VALUE = "SliderStyle.OutSet";
const auto ATTRIBUTE_DIRECTION_NAME = "direction";
const auto ATTRIBUTE_DIRECTION_DEFAULT_VALUE = "Axis.Horizontal";
const auto ATTRIBUTE_REVERSE_NAME = "reverse";
const auto ATTRIBUTE_REVERSE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_BLOCK_COLOR_NAME = "blockColor";
const auto ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE = "#FFFFFFFF";
const auto ATTRIBUTE_TRACK_COLOR_NAME = "trackColor";
const auto ATTRIBUTE_TRACK_COLOR_DEFAULT_VALUE = "#FFFF0000";
const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "#FFFF0000";
const auto ATTRIBUTE_MIN_LABEL_NAME = "min";
const auto ATTRIBUTE_MAX_LABEL_NAME = "max";
const auto ATTRIBUTE_SHOW_STEPS_NAME = "showSteps";
const auto ATTRIBUTE_SHOW_STEPS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_SHOW_TIPS_NAME = "showTips";
const auto ATTRIBUTE_SHOW_TIPS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_CONTENT_NAME = "content";
const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TRACK_THICKNESS_NAME = "trackThickness";
const auto ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE = "4.00vp";
const auto ATTRIBUTE_BLOCK_BORDER_COLOR_NAME = "blockBorderColor";
const auto ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE = "#00000000";
const auto ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME = "blockBorderWidth";
const auto ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_STEP_COLOR_NAME = "stepColor";
const auto ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE = "#19FF0000";
const auto ATTRIBUTE_TRACK_BORDER_RADIUS_NAME = "trackBorderRadius";
const auto ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME = "selectedBorderRadius";
const auto ATTRIBUTE_SELECTED_BORDER_RADIUS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_BLOCK_SIZE_WIDTH_NAME = "width";
const auto ATTRIBUTE_BLOCK_SIZE_WIDTH_DEFAULT_VALUE = "16.00vp";
const auto ATTRIBUTE_BLOCK_SIZE_HEIGHT_NAME = "height";
const auto ATTRIBUTE_BLOCK_SIZE_HEIGHT_DEFAULT_VALUE = "16.00vp";
const auto ATTRIBUTE_BLOCK_STYLE_TYPE_NAME = "blockType";
const auto ATTRIBUTE_BLOCK_STYLE_TYPE_DEFAULT_VALUE = "BlockStyleType.DEFAULT";
const auto ATTRIBUTE_STEP_SIZE_NAME = "stepSize";
const auto ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE = "4.00vp";
const auto ATTRIBUTE_SLIDER_INTERACTION_MODE_NAME = "sliderInteractionMode";
const auto ATTRIBUTE_SLIDER_INTERACTION_MODE_DEFAULT_VALUE = "SliderInteraction.SLIDE_AND_CLICK";
const auto ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME = "minResponsiveDistance";
const auto ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_SLIDE_RANGE_FROM_NAME = "from";
const auto ATTRIBUTE_SLIDE_RANGE_FROM_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SLIDE_RANGE_TO_NAME = "to";
const auto ATTRIBUTE_SLIDE_RANGE_TO_DEFAULT_VALUE = "";

struct EventsTracker {
    static inline GENERATED_ArkUISliderEventsReceiver sliderEventReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
        .getSliderEventsReceiver = [] () -> const GENERATED_ArkUISliderEventsReceiver* {
            return &sliderEventReceiver;
        }
    };
}; // EventsTracker
} // namespace

namespace Fixtures {
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberInitialValuesSlider = {
    { "0", Converter::ArkValue<Ark_Number>(0), "0.000000" },
    { "100", Converter::ArkValue<Ark_Number>(100), "100.000000" },
    { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberValueValidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Number>(0), "0.000000" },
    { "2.2", Converter::ArkValue<Ark_Number>(2.2), "2.200000" },
    { "99", Converter::ArkValue<Ark_Number>(99), "99.000000" },
    { "100", Converter::ArkValue<Ark_Number>(100), "100.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberValueInvalidValuesSlider = {
    { "-100", Converter::ArkValue<Ark_Number>(-100), ATTRIBUTE_MIN_DEFAULT_VALUE },
    { "200", Converter::ArkValue<Ark_Number>(200), ATTRIBUTE_MAX_DEFAULT_VALUE },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberMinValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
    { "2.2", Converter::ArkValue<Ark_Number>(2.2), "2.200000" },
    { "99", Converter::ArkValue<Ark_Number>(99), "99.000000" },
    { "-100", Converter::ArkValue<Ark_Number>(-100), "-100.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberMinInvalidValuesSlider = {
    { "100", Converter::ArkValue<Ark_Number>(100), ATTRIBUTE_MIN_DEFAULT_VALUE },
    { "200", Converter::ArkValue<Ark_Number>(200), ATTRIBUTE_MIN_DEFAULT_VALUE },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberMaxValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
    { "2.2", Converter::ArkValue<Ark_Number>(2.2), "2.200000" },
    { "99", Converter::ArkValue<Ark_Number>(99), "99.000000" },
    { "200", Converter::ArkValue<Ark_Number>(200), "200.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberMaxInvalidValuesSlider = {
    { "-100", Converter::ArkValue<Ark_Number>(-100), ATTRIBUTE_MIN_DEFAULT_VALUE },
    { "0", Converter::ArkValue<Ark_Number>(0), "0.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberStepValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
    { "0.5", Converter::ArkValue<Ark_Number>(0.5), "0.500000" },
    { "10", Converter::ArkValue<Ark_Number>(10), "10.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberStepInvalidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Number>(0), ATTRIBUTE_STEP_DEFAULT_VALUE },
    { "-1", Converter::ArkValue<Ark_Number>(-1), ATTRIBUTE_STEP_DEFAULT_VALUE },
    { "200", Converter::ArkValue<Ark_Number>(200), ATTRIBUTE_STEP_DEFAULT_VALUE },
};

std::vector<std::tuple<std::string, Ark_SliderStyle,
    std::string>> testFixtureEnumSliderStyleValidValuesSlider = {
    { "ARK_SLIDER_STYLE_OUT_SET", ARK_SLIDER_STYLE_OUT_SET, "SliderStyle.OutSet" },
    { "ARK_SLIDER_STYLE_IN_SET", ARK_SLIDER_STYLE_IN_SET, "SliderStyle.InSet" },
    { "ARK_SLIDER_STYLE_NONE", ARK_SLIDER_STYLE_NONE, "SliderStyle.NONE" },
};

std::vector<std::tuple<std::string, Ark_Axis, std::string>> testFixtureEnumAxisValidValuesSlider = {
    { "ARK_AXIS_VERTICAL", ARK_AXIS_VERTICAL, "Axis.Vertical" },
    { "ARK_AXIS_HORIZONTAL", ARK_AXIS_HORIZONTAL, "Axis.Horizontal" },
};

std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureNumberMinLabelValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_String>("1"), "1.000000" },
    { "2.2", Converter::ArkValue<Ark_String>("2.2"), "2.200000" },
    { "99", Converter::ArkValue<Ark_String>("99"), "99.000000" },
    { "-100", Converter::ArkValue<Ark_String>("-100"), "-100.000000" },
};

std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureNumberMaxLabelValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_String>("1"), "1.000000" },
    { "2.2", Converter::ArkValue<Ark_String>("2.2"), "2.200000" },
    { "99", Converter::ArkValue<Ark_String>("99"), "99.000000" },
    { "200", Converter::ArkValue<Ark_String>("200"), "200.000000" },
};

std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNumNonNegValidValuesThicknessSlider = {
    { "123", Converter::ArkValue<Ark_Length>(123), "123.00px" },
    { "0", Converter::ArkValue<Ark_Length>(0), "4.00vp" },
    { "1.23f", Converter::ArkValue<Ark_Length>(1.23f), "1.23vp" },
};
std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNumNonNegValidValuesSlider = {
    { "123", Converter::ArkValue<Ark_Length>(123), "123.00px" },
    { "0", Converter::ArkValue<Ark_Length>(0), "0.00px" },
    { "1.23f", Converter::ArkValue<Ark_Length>(1.23f), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNumNonNegValidValuesBlockSizeSlider = {
    { "123", Converter::ArkValue<Ark_Length>(123), "123.00px" },
    { "0", Converter::ArkValue<Ark_Length>(0), ATTRIBUTE_BLOCK_SIZE_WIDTH_DEFAULT_VALUE },
    { "1.23f", Converter::ArkValue<Ark_Length>(1.23f), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_SliderBlockType,
    std::string>> testFixtureEnumSliderBlockTypeValidValuesSlider = {
    { "ARK_SLIDER_BLOCK_TYPE_DEFAULT", ARK_SLIDER_BLOCK_TYPE_DEFAULT, "BlockStyleType.DEFAULT" },
    { "ARK_SLIDER_BLOCK_TYPE_IMAGE", ARK_SLIDER_BLOCK_TYPE_IMAGE, "BlockStyleType.IMAGE" },
    { "ARK_SLIDER_BLOCK_TYPE_SHAPE", ARK_SLIDER_BLOCK_TYPE_SHAPE, "BlockStyleType.SHAPE" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberResponsiveDistanceValidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Number>(0), "0.000000" },
    { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
    { "99", Converter::ArkValue<Ark_Number>(99), "99.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberRangeFromValidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Number>(0), "0.000000" },
    { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
    { "99", Converter::ArkValue<Ark_Number>(99), "99.000000" },
    { "100", Converter::ArkValue<Ark_Number>(100), "100.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberRangeFromInvalidValuesSlider = {
    { "-1", Converter::ArkValue<Ark_Number>(-1), "-1.000000" },
    { "200", Converter::ArkValue<Ark_Number>(200), "200.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberRangeToValidValuesSlider = {
    { "100", Converter::ArkValue<Ark_Number>(100), "100.000000" },
    { "0", Converter::ArkValue<Ark_Number>(0), "0.000000" },
    { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
    { "99", Converter::ArkValue<Ark_Number>(99), "99.000000" },
};

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureNumberRangeToInvalidValuesSlider = {
    { "-1", Converter::ArkValue<Ark_Number>(-1), "-1.000000" },
    { "200", Converter::ArkValue<Ark_Number>(200), "200.000000" },
};

} // Fixtures

class SliderModifierTest : public ModifierTestBase<GENERATED_ArkUISliderModifier,
                               &GENERATED_ArkUINodeModifiers::getSliderModifier, GENERATED_ARKUI_SLIDER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        auto theme = SetupThemeStyle(THEME_PATTERN_SLIDER);
        SetupTheme<SliderTheme>();
        for (auto&& res : Fixtures::resourceInitTable) {
            AddResource(std::get<0>(res), std::get<2>(res)); // 2 - index of resource
            AddResource(std::get<1>(res), std::get<2>(res)); // 2 - index of resource
        }
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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

    for (auto&& value : Fixtures::testFixtureNumberValueValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Number>(), ATTRIBUTE_MIN_DEFAULT_VALUE);
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Number>(), ATTRIBUTE_MIN_DEFAULT_VALUE);
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Number>(), ATTRIBUTE_MIN_DEFAULT_VALUE);
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
    initValueOptions.style =
        Converter::ArkValue<Opt_SliderStyle>(std::get<1>(Fixtures::testFixtureEnumSliderStyleValidValues[0]));
    initValueOptions.direction =
        Converter::ArkValue<Opt_Axis>(std::get<1>(Fixtures::testFixtureEnumAxisValidValues[0]));
    initValueOptions.reverse =
        Converter::ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueOptions](
            const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
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
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Number>(), ATTRIBUTE_STEP_DEFAULT_VALUE);
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
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
    initValueOptions.value =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.min =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[0]));
    initValueOptions.max =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[1]));
    initValueOptions.step =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberInitialValuesSlider[2]));
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
HWTEST_F(SliderModifierTest, setBlockColorTestBlockColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBlockColor;

    // Initial setup
    initValueBlockColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueBlockColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueBlockColor = initValueBlockColor;

        inputValueBlockColor = value;
        modifier_->setBlockColor(node_, &inputValueBlockColor);
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
            Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)), std::get<2>(value));
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

        modifier_->setBlockColor(node_, &inputValueBlockColor);
        inputValueBlockColor = value;
        modifier_->setBlockColor(node_, &inputValueBlockColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockColor, attribute: blockColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)));
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
HWTEST_F(SliderModifierTest, setSelectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE);
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
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueSelectedColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueSelectedColor = initValueSelectedColor;

        inputValueSelectedColor = value;
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSelectedColor, attribute: selectedColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)), std::get<2>(value));
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
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueSelectedColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueSelectedColor = initValueSelectedColor;

        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        inputValueSelectedColor = value;
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSelectedColor, attribute: selectedColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)));
    }
    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMinLabelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinLabelTestDefaultValues, TestSize.Level1)
{
    auto jsonValueFull = GetJsonValue(node_);
    auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_LABEL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_DEFAULT_VALUE);
}

/*
 * @tc.name: setMinLabelTestMinLabelValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinLabelTestMinLabelValidValues, TestSize.Level1)
{
    Ark_String initValueMinLabel;

    // Initial setup
    initValueMinLabel = std::get<1>(Fixtures::testFixtureNumberMinLabelValidValuesSlider[0]);

    auto checkValue = [this, &initValueMinLabel](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueMinLabel = initValueMinLabel;

        inputValueMinLabel = value;
        modifier_->setMinLabel(node_, &inputValueMinLabel);
        auto jsonValueFull = GetJsonValue(node_);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_LABEL_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMinLabel, attribute: minLabel";
    };

    for (auto&& value : Fixtures::testFixtureNumberMinLabelValidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setMaxLabelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMaxLabelTestDefaultValues, TestSize.Level1)
{
    auto jsonValueFull = GetJsonValue(node_);
    auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LABEL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_DEFAULT_VALUE);
}

/*
 * @tc.name: setMaxLabelTestMaxLabelValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMaxLabelTestMaxLabelValidValues, TestSize.Level1)
{
    Ark_String initValueMaxLabel;

    // Initial setup
    initValueMaxLabel = std::get<1>(Fixtures::testFixtureNumberMaxLabelValidValuesSlider[0]);

    auto checkValue = [this, &initValueMaxLabel](
                        const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueMaxLabel = initValueMaxLabel;

        inputValueMaxLabel = value;
        modifier_->setMaxLabel(node_, &inputValueMaxLabel);
        auto jsonValueFull = GetJsonValue(node_);
        auto jsonValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValueFull, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LABEL_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMaxLabel, attribute: maxLabel";
    };

    for (auto&& value : Fixtures::testFixtureNumberMaxLabelValidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
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
        modifier_->setShowSteps(node_, inputValueShowSteps);
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
        modifier_->setShowTips(node_, inputValueShowTips, &realInputValue1);
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
        modifier_->setShowTips(node_, inputValueShowTips, &realInputValue1);
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

        modifier_->setShowTips(node_, inputValueShowTips, &realInputValue1);
        inputValueContent = value;
        modifier_->setShowTips(node_, inputValueShowTips, &realInputValue1);
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
    initValueTrackThickness = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueTrackThickness](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueTrackThickness = initValueTrackThickness;

        inputValueTrackThickness = value;
        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
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
    initValueTrackThickness = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueTrackThickness](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueTrackThickness = initValueTrackThickness;

        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        inputValueTrackThickness = value;
        modifier_->setTrackThickness(node_, &inputValueTrackThickness);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_THICKNESS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_THICKNESS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTrackThickness, attribute: trackThickness";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), std::get<1>(value));
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
HWTEST_F(SliderModifierTest, setBlockBorderColorTestBlockBorderColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBlockBorderColor;

    // Initial setup
    initValueBlockBorderColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueBlockBorderColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueBlockBorderColor = initValueBlockBorderColor;

        inputValueBlockBorderColor = value;
        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
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
            Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)),
            std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)), std::get<2>(value));
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

        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        inputValueBlockBorderColor = value;
        modifier_->setBlockBorderColor(node_, &inputValueBlockBorderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockBorderColor, attribute: blockBorderColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)));
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
        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
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
    initValueBlockBorderWidth = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueBlockBorderWidth](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueBlockBorderWidth = initValueBlockBorderWidth;

        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        inputValueBlockBorderWidth = value;
        modifier_->setBlockBorderWidth(node_, &inputValueBlockBorderWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BLOCK_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_BORDER_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockBorderWidth, attribute: blockBorderWidth";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), std::get<1>(value));
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
HWTEST_F(SliderModifierTest, setStepColorTestStepColorValidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueStepColor;

    // Initial setup
    initValueStepColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));

    auto checkValue = [this, &initValueStepColor](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Ark_ResourceColor inputValueStepColor = initValueStepColor;

        inputValueStepColor = value;
        modifier_->setStepColor(node_, &inputValueStepColor);
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
            Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value),
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)), std::get<2>(value));
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

        modifier_->setStepColor(node_, &inputValueStepColor);
        inputValueStepColor = value;
        modifier_->setStepColor(node_, &inputValueStepColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setStepColor, attribute: stepColor";
    };

    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value)));
    }
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(value)));
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
        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
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
    initValueTrackBorderRadius = std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]);

    auto checkValue = [this, &initValueTrackBorderRadius](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueTrackBorderRadius = initValueTrackBorderRadius;

        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        inputValueTrackBorderRadius = value;
        modifier_->setTrackBorderRadius(node_, &inputValueTrackBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_BORDER_RADIUS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTrackBorderRadius, attribute: trackBorderRadius";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), std::get<1>(value));
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
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BORDER_RADIUS_DEFAULT_VALUE);
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
    initValueSelectedBorderRadius = std::get<1>(Fixtures::testFixtureLengthNumNonNegValidValuesSlider[0]);

    auto checkValue = [this, &initValueSelectedBorderRadius](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueSelectedBorderRadius = initValueSelectedBorderRadius;

        inputValueSelectedBorderRadius = value;
        modifier_->setSelectedBorderRadius(node_, &inputValueSelectedBorderRadius);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BORDER_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSelectedBorderRadius, attribute: selectedBorderRadius";
    };

    for (auto&& value : Fixtures::testFixtureLengthNumNonNegValidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
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
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BORDER_RADIUS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSelectedBorderRadius, attribute: selectedBorderRadius";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), std::get<1>(value));
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
        modifier_->setBlockSize(node_, &inputValueBlockSize);
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
        Converter::ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height =
        Converter::ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        modifier_->setBlockSize(node_, &inputValueBlockSize);
        inputValueBlockSize.width = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockSize, attribute: width";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Length>(std::get<1>(value)));
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
        modifier_->setBlockSize(node_, &inputValueBlockSize);
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
        Converter::ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    initValueBlockSize.height =
        Converter::ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBlockSize](const std::string& input, const Opt_Length& value) {
        Ark_SizeOptions inputValueBlockSize = initValueBlockSize;

        modifier_->setBlockSize(node_, &inputValueBlockSize);
        inputValueBlockSize.height = value;
        modifier_->setBlockSize(node_, &inputValueBlockSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultBlockSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BLOCK_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBlockSize, ATTRIBUTE_BLOCK_SIZE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BLOCK_SIZE_HEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBlockSize, attribute: height";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Length>(std::get<1>(value)));
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
    initValueBlockStyle.shape =
        Converter::ArkValue<Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute>();

    auto checkValue = [this, &initValueBlockStyle](const std::string& input, const Ark_SliderBlockType& value,
        const std::string& expectedStr) {
        Ark_SliderBlockStyle inputValueBlockStyle = initValueBlockStyle;

        inputValueBlockStyle.type = value;
        modifier_->setBlockStyle(node_, &inputValueBlockStyle);
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
        modifier_->setStepSize(node_, &inputValueStepSize);
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

        modifier_->setStepSize(node_, &inputValueStepSize);
        inputValueStepSize = value;
        modifier_->setStepSize(node_, &inputValueStepSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setStepSize, attribute: stepSize";
    };

    for (auto&& value : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(std::get<0>(value), std::get<1>(value));
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
        modifier_->setSliderInteractionMode(node_, inputValueSliderInteractionMode);
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

        modifier_->setSliderInteractionMode(node_, inputValueSliderInteractionMode);
        inputValueSliderInteractionMode = value;
        modifier_->setSliderInteractionMode(node_, inputValueSliderInteractionMode);
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
    Ark_Number initValueMinResponsiveDistance;

    // Initial setup
    initValueMinResponsiveDistance = std::get<1>(Fixtures::testFixtureNumberResponsiveDistanceValidValuesSlider[0]);

    auto checkValue = [this, &initValueMinResponsiveDistance](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueMinResponsiveDistance = initValueMinResponsiveDistance;

        inputValueMinResponsiveDistance = value;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto&& value : Fixtures::testFixtureNumberResponsiveDistanceValidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value), std::get<2>(value));
    }
}

/*
 * @tc.name: setMinResponsiveDistanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setMinResponsiveDistanceInvalidValues, TestSize.Level1)
{
    Ark_Number initValueMinResponsiveDistance;

    // Initial setup
    initValueMinResponsiveDistance = std::get<1>(Fixtures::testFixtureNumberResponsiveDistanceValidValuesSlider[0]);

    auto checkValue = [this, &initValueMinResponsiveDistance](
                          const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueMinResponsiveDistance = initValueMinResponsiveDistance;

        inputValueMinResponsiveDistance = value;
        modifier_->setMinResponsiveDistance(node_, &inputValueMinResponsiveDistance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_RESPONSIVE_DISTANCE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setMinResponsiveDistance, attribute: minResponsiveDistance";
    };

    for (auto&& value : Fixtures::testFixtureNumberValueInvalidValuesSlider) {
        checkValue(std::get<0>(value), std::get<1>(value));
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
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        inputValueSlideRange.from = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_FROM_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSlideRange, attribute: from";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeFromValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
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
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Number& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        modifier_->setSlideRange(node_, &inputValueSlideRange);
        inputValueSlideRange.from = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_FROM_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_FROM_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSlideRange, attribute: from";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeFromInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Number>());
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
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        inputValueSlideRange.to = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_TO_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSlideRange, attribute: to";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeToValidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)), std::get<2>(value));
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
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeFromValidValuesSlider[0]));
    initValueSlideRange.to =
        Converter::ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberRangeToValidValuesSlider[0]));

    auto checkValue = [this, &initValueSlideRange](const std::string& input, const Opt_Number& value) {
        Ark_SlideRange inputValueSlideRange = initValueSlideRange;

        modifier_->setSlideRange(node_, &inputValueSlideRange);
        inputValueSlideRange.to = value;
        modifier_->setSlideRange(node_, &inputValueSlideRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultSlideRange = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SLIDE_RANGE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlideRange, ATTRIBUTE_SLIDE_RANGE_TO_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SLIDE_RANGE_TO_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setSlideRange, attribute: to";
    };

    for (auto&& value : Fixtures::testFixtureNumberRangeToInvalidValuesSlider) {
        checkValue(std::get<0>(value), Converter::ArkValue<Opt_Number>(std::get<1>(value)));
    }

    // Check empty optional
    checkValue("undefined", Converter::ArkValue<Opt_Number>());
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of SliderModifier.setOnChange
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTest, setOnChangeTest, TestSize.Level1)
{
    Callback_Number_SliderChangeMode_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        float value;
        std::optional<int32_t> mode;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::sliderEventReceiver.onChange = [](Ark_Int32 nodeId, Ark_Number value, Ark_SliderChangeMode mode)
    {
        checkEvent = {
            .nodeId = nodeId,
            .value = Converter::Convert<float>(value),
            .mode = EnumToInt(Converter::OptConvert<SliderModel::SliderChangeMode>(mode)),
        };
    };

    modifier_->setOnChange(node_, &func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(10, 0);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->value, 10);
    EXPECT_EQ(checkEvent->mode.value(), 0);
    eventHub->FireChangeEvent(20, 1);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->value, 20);
    EXPECT_EQ(checkEvent->mode.value(), 1);
}
} // namespace OHOS::Ace::NG
