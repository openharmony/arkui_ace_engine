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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_SLIDER_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_SLIDER_H
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
namespace TestConst::Slider {
const auto ATTRIBUTE_BLOCK_SIZE_NAME = "blockSize";
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
const auto ATTRIBUTE_TRACK_COLOR_NAME = "trackColor";
const auto ATTRIBUTE_TRACK_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "#FF000000";
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
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_NAME = "digitalCrownSensitivity";
const auto ATTRIBUTE_DIGITAL_CROWN_SENSITIVITY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_SHOW_TIPS_NAME = "showTips";
const auto ATTRIBUTE_SHOW_TIPS_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_CONTENT_NAME = "content";
const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "";
} // namespace TestConst::Slider

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

} // namespace OHOS::Ace::NG

#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_SLIDER_H
