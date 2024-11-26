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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_TEXT_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_TEXT_H
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
namespace TestConst::Text {
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_FONT_NAME = "font";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_NAME = "fontValue";
const auto ATTRIBUTE_FONT_I_OPTIONS_NAME = "options";
const auto ATTRIBUTE_TEXT_OVERFLOW_NAME = "textOverflow";
const auto ATTRIBUTE_DECORATION_NAME = "decoration";
const auto ATTRIBUTE_TEXT_SHADOW_NAME = "textShadow";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME = "dataDetectorConfig";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_NAME = "decoration";
const auto ATTRIBUTE_SELECTION_NAME = "selection";
const auto ATTRIBUTE_CONTENT_NAME = "content";
const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_CONTROLLER_NAME = "controller";
const auto ATTRIBUTE_VALUE_I_CONTROLLER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_SIZE_NAME = "size";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_WEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_FAMILY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_STYLE_NAME = "style";
const auto ATTRIBUTE_FONT_I_FONT_VALUE_I_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME = "enableVariableFontWeight";
const auto ATTRIBUTE_FONT_I_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "16.00fp";
const auto ATTRIBUTE_MIN_FONT_SIZE_NAME = "minFontSize";
const auto ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_FONT_SIZE_NAME = "maxFontSize";
const auto ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MIN_FONT_SCALE_NAME = "minFontScale";
const auto ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_FONT_SCALE_NAME = "maxFontScale";
const auto ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_LINE_SPACING_NAME = "lineSpacing";
const auto ATTRIBUTE_LINE_SPACING_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_ALIGN_NAME = "textAlign";
const auto ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE = "TextAlign.Start";
const auto ATTRIBUTE_LINE_HEIGHT_NAME = "lineHeight";
const auto ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_NAME = "overflow";
const auto ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_DEFAULT_VALUE = "TextOverflow.Clip";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "Harmony"
                                                 "OS Sans";
const auto ATTRIBUTE_MAX_LINES_NAME = "maxLines";
const auto ATTRIBUTE_MAX_LINES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DECORATION_I_TYPE_NAME = "type";
const auto ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE = "TextDecorationType.None";
const auto ATTRIBUTE_DECORATION_I_COLOR_NAME = "color";
const auto ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_DECORATION_I_STYLE_NAME = "style";
const auto ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE = "TextDecorationStyle.SOLID";
const auto ATTRIBUTE_LETTER_SPACING_NAME = "letterSpacing";
const auto ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_CASE_NAME = "textCase";
const auto ATTRIBUTE_TEXT_CASE_DEFAULT_VALUE = "TextCase.Normal";
const auto ATTRIBUTE_BASELINE_OFFSET_NAME = "baselineOffset";
const auto ATTRIBUTE_BASELINE_OFFSET_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_COPY_OPTION_NAME = "copyOption";
const auto ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME = "type";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME = "offsetX";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME = "offsetY";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME = "fill";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME = "heightAdaptivePolicy";
const auto ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE = "TextHeightAdaptivePolicy.MAX_LINES_FIRST";
const auto ATTRIBUTE_TEXT_INDENT_NAME = "textIndent";
const auto ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_WORD_BREAK_NAME = "wordBreak";
const auto ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE = "break-word";
const auto ATTRIBUTE_LINE_BREAK_STRATEGY_NAME = "lineBreakStrategy";
const auto ATTRIBUTE_LINE_BREAK_STRATEGY_DEFAULT_VALUE = "greedy";
const auto ATTRIBUTE_ELLIPSIS_MODE_NAME = "ellipsisMode";
const auto ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE = "EllipsisMode.END";
const auto ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME = "enableDataDetector";
const auto ATTRIBUTE_ENABLE_DATA_DETECTOR_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_NAME = "types";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_NAME = "color";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_NAME = "type";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_NAME = "color";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_NAME = "style";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_FEATURE_NAME = "fontFeature";
const auto ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_NAME = "privacySensitive";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_TEXT_SELECTABLE_NAME = "textSelectable";
const auto ATTRIBUTE_TEXT_SELECTABLE_DEFAULT_VALUE = "selectable-unfocusable";
const auto ATTRIBUTE_HALF_LEADING_NAME = "halfLeading";
const auto ATTRIBUTE_HALF_LEADING_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_SELECTION_I_SELECTION_START_NAME = "selectionStart";
const auto ATTRIBUTE_SELECTION_I_SELECTION_START_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SELECTION_I_SELECTION_END_NAME = "selectionEnd";
const auto ATTRIBUTE_SELECTION_I_SELECTION_END_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace TestConst::Text

class TextModifierTest : public ModifierTestBase<GENERATED_ArkUITextModifier,
                             &GENERATED_ArkUINodeModifiers::getTextModifier, GENERATED_ARKUI_TEXT> {
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

} // namespace OHOS::Ace::NG

#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_TEXT_H
