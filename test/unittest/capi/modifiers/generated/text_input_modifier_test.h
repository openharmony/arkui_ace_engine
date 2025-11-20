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

#ifndef GENERATED_FOUNDATION_ACE_CAPI_TEST_TEXT_INPUT_H
#define GENERATED_FOUNDATION_ACE_CAPI_TEST_TEXT_INPUT_H
#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/components/text_field/textfield_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace TestConst::TextInput {
const auto ATTRIBUTE_PLACEHOLDER_FONT_NAME = "placeholderFont";
const auto ATTRIBUTE_CARET_STYLE_NAME = "caretStyle";
const auto ATTRIBUTE_PASSWORD_ICON_NAME = "passwordIcon";
const auto ATTRIBUTE_UNDERLINE_COLOR_NAME = "underlineColor";
const auto ATTRIBUTE_CANCEL_BUTTON_NAME = "cancelButton";
const auto ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME = "icon";
const auto ATTRIBUTE_DECORATION_NAME = "decoration";
const auto ATTRIBUTE_SHOW_COUNTER_NAME = "showCounter";
const auto ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME = "options";
const auto ATTRIBUTE_PLACEHOLDER_NAME = "placeholder";
const auto ATTRIBUTE_PLACEHOLDER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_NAME = "text";
const auto ATTRIBUTE_TEXT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TYPE_NAME = "type";
const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "InputType.Normal";
const auto ATTRIBUTE_CONTENT_TYPE_NAME = "contentType";
const auto ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE = "TextContentType.UNSPECIFIED";
const auto ATTRIBUTE_PLACEHOLDER_COLOR_NAME = "placeholderColor";
const auto ATTRIBUTE_PLACEHOLDER_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TEXT_OVERFLOW_NAME = "textOverflow";
const auto ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE = "TextOverflow.Clip";
const auto ATTRIBUTE_TEXT_INDENT_NAME = "textIndent";
const auto ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_FAMILY_DEFAULT_VALUE = "Harmony"
                                                               "OS Sans";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_ENTER_KEY_TYPE_NAME = "enterKeyType";
const auto ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE = "EnterKeyType.Done";
const auto ATTRIBUTE_CARET_COLOR_NAME = "caretColor";
const auto ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_MAX_LENGTH_NAME = "maxLength";
const auto ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE = "INF";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "Harmony"
                                                 "OS Sans";
const auto ATTRIBUTE_COPY_OPTION_NAME = "copyOption";
const auto ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE = "CopyOptions.Local";
const auto ATTRIBUTE_SHOW_PASSWORD_ICON_NAME = "showPasswordIcon";
const auto ATTRIBUTE_SHOW_PASSWORD_ICON_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_TEXT_ALIGN_NAME = "textAlign";
const auto ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE = "TextAlign.Start";
const auto ATTRIBUTE_STYLE_NAME = "style";
const auto ATTRIBUTE_STYLE_DEFAULT_VALUE = "TextInputStyle.Default";
const auto ATTRIBUTE_CARET_STYLE_I_WIDTH_NAME = "width";
const auto ATTRIBUTE_CARET_STYLE_I_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_CARET_STYLE_I_COLOR_NAME = "color";
const auto ATTRIBUTE_CARET_STYLE_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME = "selectedBackgroundColor";
const auto ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_CARET_POSITION_NAME = "caretPosition";
const auto ATTRIBUTE_CARET_POSITION_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_PASSWORD_ICON_I_ON_ICON_SRC_NAME = "onIconSrc";
const auto ATTRIBUTE_PASSWORD_ICON_I_ON_ICON_SRC_DEFAULT_VALUE = "SYS_SHOW_PASSWORD_SVG";
const auto ATTRIBUTE_PASSWORD_ICON_I_OFF_ICON_SRC_NAME = "offIconSrc";
const auto ATTRIBUTE_PASSWORD_ICON_I_OFF_ICON_SRC_DEFAULT_VALUE = "SYS_HIDE_PASSWORD_SVG";
const auto ATTRIBUTE_SHOW_ERROR_NAME = "showError";
const auto ATTRIBUTE_SHOW_ERROR_DEFAULT_VALUE = "undefined";
const auto ATTRIBUTE_SHOW_UNDERLINE_NAME = "showUnderline";
const auto ATTRIBUTE_SHOW_UNDERLINE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_NAME = "typing";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_NAME = "normal";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_NAME = "error";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_NAME = "disable";
const auto ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_BAR_STATE_NAME = "barState";
const auto ATTRIBUTE_BAR_STATE_DEFAULT_VALUE = "BarState.AUTO";
const auto ATTRIBUTE_MAX_LINES_NAME = "maxLines";
const auto ATTRIBUTE_MAX_LINES_DEFAULT_VALUE = "3";
const auto ATTRIBUTE_WORD_BREAK_NAME = "wordBreak";
const auto ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE = "break-word";
const auto ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME = "style";
const auto ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE = "2";
const auto ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_NAME = "size";
const auto ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_NAME = "color";
const auto ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_NAME = "src";
const auto ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SELECT_ALL_NAME = "selectAll";
const auto ATTRIBUTE_SELECT_ALL_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_MIN_FONT_SIZE_NAME = "minFontSize";
const auto ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_MAX_FONT_SIZE_NAME = "maxFontSize";
const auto ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_MIN_FONT_SCALE_NAME = "minFontScale";
const auto ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE = "0.850000";
const auto ATTRIBUTE_MAX_FONT_SCALE_NAME = "maxFontScale";
const auto ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE = "3.200000";
const auto ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME = "heightAdaptivePolicy";
const auto ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE = "TextHeightAdaptivePolicy.MAX_LINES_FIRST";
const auto ATTRIBUTE_ENABLE_AUTO_FILL_NAME = "enableAutoFill";
const auto ATTRIBUTE_ENABLE_AUTO_FILL_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_DECORATION_I_TYPE_NAME = "type";
const auto ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE = "TextDecorationType.None";
const auto ATTRIBUTE_DECORATION_I_COLOR_NAME = "color";
const auto ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_DECORATION_I_STYLE_NAME = "style";
const auto ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE = "TextDecorationStyle.SOLID";
const auto ATTRIBUTE_LETTER_SPACING_NAME = "letterSpacing";
const auto ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_LINE_HEIGHT_NAME = "lineHeight";
const auto ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PASSWORD_RULES_NAME = "passwordRules";
const auto ATTRIBUTE_PASSWORD_RULES_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_FEATURE_NAME = "fontFeature";
const auto ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SHOW_PASSWORD_NAME = "showPassword";
const auto ATTRIBUTE_SHOW_PASSWORD_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME = "enablePreviewText";
const auto ATTRIBUTE_ENABLE_PREVIEW_TEXT_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_AUTO_CAPITALIZATION_MODE_NAME = "autoCapitalizationMode";
const auto ATTRIBUTE_AUTO_CAPITALIZATION_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HALF_LEADING_NAME = "halfLeading";
const auto ATTRIBUTE_HALF_LEADING_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ELLIPSIS_MODE_NAME = "ellipsisMode";
const auto ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE = "EllipsisMode.END";
const auto ATTRIBUTE_STOP_BACK_PRESS_NAME = "stopBackPress";
const auto ATTRIBUTE_STOP_BACK_PRESS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_KEYBOARD_APPEARANCE_NAME = "keyboardAppearance";
const auto ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME = "value";
const auto ATTRIBUTE_SHOW_COUNTER_I_VALUE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME = "thresholdPercentage";
const auto ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_DEFAULT_VALUE = "-1";
const auto ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME = "highlightBorder";
const auto ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_DEFAULT_VALUE = "true";
} // namespace TestConst::TextInput

class TextInputModifierTest : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextInputModifier, GENERATED_ARKUI_TEXT_INPUT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextFieldTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

} // namespace OHOS::Ace::NG

#endif // GENERATED_FOUNDATION_ACE_CAPI_TEST_TEXT_INPUT_H
