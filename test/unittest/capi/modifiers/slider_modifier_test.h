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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_SLIDER_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_SLIDER_H
#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components/slider/slider_theme.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/linear_gradient_peer.h"

namespace OHOS::Ace::NG {
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
const auto ATTRIBUTE_TRACK_COLOR_GRADIENT_COLOR_NAME = "color";
const auto ATTRIBUTE_TRACK_COLOR_GRADIENT_OFFSET_NAME = "offset";
#ifdef SUPPORT_DIGITAL_CROWN
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME = "digitalCrownSensitivity";
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE = "CrownSensitivity.MEDIUM";
#endif
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
const std::string EXPECTED_TRUE("true");
const std::string EXPECTED_FALSE("false");

namespace Fixtures {
std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberInitialValuesSlider = {
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
    { "100", Converter::ArkValue<Ark_Float64>(100.), "100.000000" },
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberValueValidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
    { "2.2", Converter::ArkValue<Ark_Float64>(2.2), "2.200000" },
    { "99", Converter::ArkValue<Ark_Float64>(99.), "99.000000" },
    { "100", Converter::ArkValue<Ark_Float64>(100.), "100.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberValueInvalidValuesSlider = {
    { "-100", Converter::ArkValue<Ark_Float64>(-100.), ATTRIBUTE_MIN_DEFAULT_VALUE },
    { "200", Converter::ArkValue<Ark_Float64>(200.), ATTRIBUTE_MAX_DEFAULT_VALUE },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberMinValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
    { "2.2", Converter::ArkValue<Ark_Float64>(2.2), "2.200000" },
    { "99", Converter::ArkValue<Ark_Float64>(99.), "99.000000" },
    { "-100", Converter::ArkValue<Ark_Float64>(-100.), "-100.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberMinInvalidValuesSlider = {
    { "100", Converter::ArkValue<Ark_Float64>(100.), ATTRIBUTE_MIN_DEFAULT_VALUE },
    { "200", Converter::ArkValue<Ark_Float64>(200.), ATTRIBUTE_MIN_DEFAULT_VALUE },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberMaxValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
    { "2.2", Converter::ArkValue<Ark_Float64>(2.2), "2.200000" },
    { "99", Converter::ArkValue<Ark_Float64>(99.), "99.000000" },
    { "200", Converter::ArkValue<Ark_Float64>(200.), "200.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberMaxInvalidValuesSlider = {
    { "-100", Converter::ArkValue<Ark_Float64>(-100.), ATTRIBUTE_MIN_DEFAULT_VALUE },
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberStepValidValuesSlider = {
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
    { "0.5", Converter::ArkValue<Ark_Float64>(0.5), "0.500000" },
    { "10", Converter::ArkValue<Ark_Float64>(10.), "10.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberStepInvalidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Float64>(0.), ATTRIBUTE_STEP_DEFAULT_VALUE },
    { "-1", Converter::ArkValue<Ark_Float64>(-1.), ATTRIBUTE_STEP_DEFAULT_VALUE },
    { "200", Converter::ArkValue<Ark_Float64>(200.), ATTRIBUTE_STEP_DEFAULT_VALUE },
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
    { "123", Converter::ArkValue<Ark_Length>("123px"), "123.00px" },
    { "0", Converter::ArkValue<Ark_Length>("0px"), "4.00vp" },
    { "1.23f", Converter::ArkValue<Ark_Length>(1.23f), "1.23vp" },
};
std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNumNonNegValidValuesSlider = {
    { "123", Converter::ArkValue<Ark_Length>("123px"), "123.00px" },
    { "0", Converter::ArkValue<Ark_Length>("0px"), "0.00px" },
    { "1.23f", Converter::ArkValue<Ark_Length>(1.23f), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_Length, std::string>> testFixtureLengthNumNonNegValidValuesBlockSizeSlider = {
    { "123", Converter::ArkValue<Ark_Length>("123px"), "123.00px" },
    { "0", Converter::ArkValue<Ark_Length>("0px"), ATTRIBUTE_BLOCK_SIZE_WIDTH_DEFAULT_VALUE },
    { "1.23f", Converter::ArkValue<Ark_Length>(1.23f), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_SliderBlockType,
    std::string>> testFixtureEnumSliderBlockTypeValidValuesSlider = {
    { "ARK_SLIDER_BLOCK_TYPE_DEFAULT", ARK_SLIDER_BLOCK_TYPE_DEFAULT, "BlockStyleType.DEFAULT" },
    { "ARK_SLIDER_BLOCK_TYPE_IMAGE", ARK_SLIDER_BLOCK_TYPE_IMAGE, "BlockStyleType.IMAGE" },
    { "ARK_SLIDER_BLOCK_TYPE_SHAPE", ARK_SLIDER_BLOCK_TYPE_SHAPE, "BlockStyleType.SHAPE" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberResponsiveDistanceValidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
    { "99", Converter::ArkValue<Ark_Float64>(99.), "99.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberRangeFromValidValuesSlider = {
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
    { "99", Converter::ArkValue<Ark_Float64>(99.), "99.000000" },
    { "100", Converter::ArkValue<Ark_Float64>(100.), "100.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberRangeFromInvalidValuesSlider = {
    { "-1", Converter::ArkValue<Ark_Float64>(-1.), "-1.000000" },
    { "200", Converter::ArkValue<Ark_Float64>(200.), "200.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberRangeToValidValuesSlider = {
    { "100", Converter::ArkValue<Ark_Float64>(100.), "100.000000" },
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
    { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
    { "99", Converter::ArkValue<Ark_Float64>(99.), "99.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureNumberRangeToInvalidValuesSlider = {
    { "-1", Converter::ArkValue<Ark_Float64>(-1.), "-1.000000" },
    { "200", Converter::ArkValue<Ark_Float64>(200.), "200.000000" },
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
    }
};
} // namespace OHOS::Ace::NG

#endif //GENERATED_FOUNDATION_ACE_CAPI_TEST_SLIDER_H
