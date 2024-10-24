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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
// const auto ATTRIBUTE_PLACEHOLDER_FONT_NAME = "placeholderFont";
const auto ATTRIBUTE_CARET_STYLE_NAME = "caretStyle";
const auto ATTRIBUTE_PASSWORD_ICON_NAME = "passwordIcon";
const auto ATTRIBUTE_CUSTOM_KEYBOARD_OPTIONS_NAME = "customKeyboardOptions";
const auto ATTRIBUTE_SHOW_COUNTER_OPTIONS_NAME = "showCounterOptions";
const auto ATTRIBUTE_DECORATION_NAME = "decoration";
const auto ATTRIBUTE_DECORATION_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DECORATION_COLOR_NAME = ATTRIBUTE_DECORATION_NAME;
const auto ATTRIBUTE_DECORATION_STYLE_NAME = ATTRIBUTE_DECORATION_NAME;
const auto ATTRIBUTE_DECORATION_TYPE_NAME = ATTRIBUTE_DECORATION_NAME;
const auto ATTRIBUTE_DECORATION_TYPE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DECORATION_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TYPE_NAME = "type";
const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "InputType.Normal";
const auto ATTRIBUTE_CONTENT_TYPE_NAME = "contentType";
const auto ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE = "TextContentType.UNSPECIFIED";
const auto ATTRIBUTE_PLACEHOLDER_COLOR_NAME = "placeholderColor";
const auto ATTRIBUTE_PLACEHOLDER_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TEXT_OVERFLOW_NAME = "textOverflow";
const auto ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE = "TextOverflow.Clip";
const auto ATTRIBUTE_TEXT_INDENT_NAME = "textIndent";
const auto ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE = "!NOT-DEFINED!";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_SIZE_NAME = "size";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_WEIGHT_NAME = "weight";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_WEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_FAMILY_NAME = "family";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_FAMILY_DEFAULT_VALUE = "!NOT-DEFINED!";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_STYLE_NAME = "style";
// const auto ATTRIBUTE_PLACEHOLDER_FONT_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ENTER_KEY_TYPE_NAME = "enterKeyType";
const auto ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE = "EnterKeyType.Done";
const auto ATTRIBUTE_CARET_COLOR_NAME = "caretColor";
const auto ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_LENGTH_NAME = "maxLength";
const auto ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_INPUT_FILTER_NAME = "inputFilter";
const auto ATTRIBUTE_INPUT_FILTER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_INPUT_FILTER_ERROR_NAME = "inputFilterError";
const auto ATTRIBUTE_INPUT_FILTER_ERROR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_COPY_OPTION_NAME = "copyOption";
const auto ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE = "CopyOptions.Distributed";
const auto ATTRIBUTE_SHOW_PASSWORD_ICON_NAME = "showPasswordIcon";
const auto ATTRIBUTE_SHOW_PASSWORD_ICON_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_TEXT_ALIGN_NAME = "textAlign";
const auto ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE = "TextAlign.Start";
const auto ATTRIBUTE_CARET_STYLE_WIDTH_NAME = "width";
const auto ATTRIBUTE_CARET_STYLE_WIDTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_CARET_STYLE_COLOR_NAME = "color";
const auto ATTRIBUTE_CARET_STYLE_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
// const auto ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME = "selectedBackgroundColor";
// const auto ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
// const auto ATTRIBUTE_CARET_POSITION_NAME = "caretPosition";
// const auto ATTRIBUTE_CARET_POSITION_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME = "enableKeyboardOnFocus";
const auto ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_PASSWORD_ICON_ON_ICON_SRC_NAME = "onIconSrc";
const auto ATTRIBUTE_PASSWORD_ICON_ON_ICON_SRC_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PASSWORD_ICON_OFF_ICON_SRC_NAME = "offIconSrc";
const auto ATTRIBUTE_PASSWORD_ICON_OFF_ICON_SRC_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_UNIT_NAME = "showUnit";
const auto ATTRIBUTE_SHOW_UNIT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_UNDERLINE_NAME = "showUnderline";
const auto ATTRIBUTE_SHOW_UNDERLINE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_SELECTION_MENU_HIDDEN_NAME = "selectionMenuHidden";
const auto ATTRIBUTE_SELECTION_MENU_HIDDEN_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_BAR_STATE_NAME = "barState";
const auto ATTRIBUTE_BAR_STATE_DEFAULT_VALUE = "BarState.AUTO";
const auto ATTRIBUTE_MAX_LINES_NAME = "maxLines";
const auto ATTRIBUTE_MAX_LINES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_WORD_BREAK_NAME = "wordBreak";
const auto ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE = "break-word";
const auto ATTRIBUTE_LINE_BREAK_STRATEGY_STRATEGY_NAME = "lineBreakStrategy";
const auto ATTRIBUTE_LINE_BREAK_STRATEGY_STRATEGY_DEFAULT_VALUE = "greedy";
const auto ATTRIBUTE_CUSTOM_KEYBOARD_NAME = "customKeyboard";
const auto ATTRIBUTE_CUSTOM_KEYBOARD_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_CUSTOM_KEYBOARD_OPTIONS_SUPPORT_AVOIDANCE_NAME = "supportAvoidance";
const auto ATTRIBUTE_CUSTOM_KEYBOARD_OPTIONS_SUPPORT_AVOIDANCE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_COUNTER_NAME = "showCounter";
const auto ATTRIBUTE_SHOW_COUNTER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_COUNTER_OPTIONS_THRESHOLD_PERCENTAGE_NAME = "thresholdPercentage";
const auto ATTRIBUTE_SHOW_COUNTER_OPTIONS_THRESHOLD_PERCENTAGE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_COUNTER_OPTIONS_HIGHLIGHT_BORDER_NAME = "highlightBorder";
const auto ATTRIBUTE_SHOW_COUNTER_OPTIONS_HIGHLIGHT_BORDER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_CANCEL_BUTTON_NAME = "cancelButton";
const auto ATTRIBUTE_CANCEL_BUTTON_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SELECT_ALL_NAME = "selectAll";
const auto ATTRIBUTE_SELECT_ALL_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME = "heightAdaptivePolicy";
const auto ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE = "TextHeightAdaptivePolicy.MAX_LINES_FIRST";
const auto ATTRIBUTE_ENABLE_AUTO_FILL_NAME = "enableAutoFill";
const auto ATTRIBUTE_ENABLE_AUTO_FILL_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_PASSWORD_RULES_NAME = "passwordRules";
const auto ATTRIBUTE_PASSWORD_RULES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_FEATURE_NAME = "fontFeature";
const auto ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SHOW_PASSWORD_VISIBLE_NAME = "showPassword";
const auto ATTRIBUTE_SHOW_PASSWORD_VISIBLE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_EDIT_MENU_OPTIONS_EDIT_MENU_NAME = "editMenuOptionsEditMenu";
const auto ATTRIBUTE_EDIT_MENU_OPTIONS_EDIT_MENU_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ENABLE_PREVIEW_TEXT_ENABLE_NAME = "enablePreviewText";
const auto ATTRIBUTE_ENABLE_PREVIEW_TEXT_ENABLE_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_IS_ENABLED_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_IS_ENABLED_DEFAULT_VALUE = "true";
} // namespace

class TextInputModifierTest : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextInputModifier, GENERATED_ARKUI_TEXT_INPUT> {};

/*
 * @tc.name: setTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE);
}

// Valid values for attribute 'type' of method 'type'
static std::vector<std::tuple<std::string, enum Ark_InputType, std::string>> typeTypeValidValues = {
    { "ARK_INPUT_TYPE_NORMAL", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_NORMAL), "InputType.Normal" },
    { "ARK_INPUT_TYPE_NUMBER", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_NUMBER), "InputType.Number" },
    { "ARK_INPUT_TYPE_PHONE_NUMBER", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_PHONE_NUMBER),
        "InputType.PhoneNumber" },
    { "ARK_INPUT_TYPE_EMAIL", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_EMAIL), "InputType.Email" },
    { "ARK_INPUT_TYPE_PASSWORD", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_PASSWORD),
        "InputType.Password" },
    { "ARK_INPUT_TYPE_NUMBER_PASSWORD", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_NUMBER_PASSWORD),
        "InputType.NUMBER_PASSWORD" },
    { "ARK_INPUT_TYPE_SCREEN_LOCK_PASSWORD",
        Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_SCREEN_LOCK_PASSWORD), "InputType.Normal" },
    { "ARK_INPUT_TYPE_USER_NAME", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_USER_NAME),
        "InputType.USER_NAME" },
    { "ARK_INPUT_TYPE_NEW_PASSWORD", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_NEW_PASSWORD),
        "InputType.NEW_PASSWORD" },
    { "ARK_INPUT_TYPE_NUMBER_DECIMAL", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_NUMBER_DECIMAL),
        "InputType.NUMBER_DECIMAL" },
    { "ARK_INPUT_TYPE_URL", Converter::ArkValue<enum Ark_InputType>(ARK_INPUT_TYPE_URL), "InputType.URL" },
};

/*
 * @tc.name: setTypeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTypeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_InputType inputValueType;
    Ark_InputType initValueType;

    // Initial setup
    initValueType = std::get<1>(typeTypeValidValues[0]);

    // Verifying attribute's  values
    inputValueType = initValueType;
    for (auto&& value : typeTypeValidValues) {
        inputValueType = std::get<1>(value);
        modifier_->setType(node_, inputValueType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'type' of method 'type'
static std::vector<std::tuple<std::string, enum Ark_InputType>> typeTypeInvalidValues = {
    { "static_cast<enum Ark_InputType>(-1)",
        Converter::ArkValue<enum Ark_InputType>(static_cast<enum Ark_InputType>(-1)) },
};

/*
 * @tc.name: setTypeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTypeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_InputType inputValueType;
    Ark_InputType initValueType;

    // Initial setup
    initValueType = std::get<1>(typeTypeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : typeTypeInvalidValues) {
        inputValueType = initValueType;
        modifier_->setType(node_, inputValueType);
        inputValueType = std::get<1>(value);
        modifier_->setType(node_, inputValueType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        expectedStr = ATTRIBUTE_TYPE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setContentTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setContentTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE);
}

// Valid values for attribute 'contentType' of method 'contentType'
static std::vector<std::tuple<std::string, enum Ark_ContentType, std::string>> contentTypeContentTypeValidValues = {
    { "ARK_CONTENT_TYPE_USER_NAME", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_USER_NAME),
        "TextContentType.USER_NAME" },
    { "ARK_CONTENT_TYPE_PASSWORD", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_PASSWORD),
        "TextContentType.VISIBLE_PASSWORD" },
    { "ARK_CONTENT_TYPE_NEW_PASSWORD", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_NEW_PASSWORD),
        "TextContentType.NEW_PASSWORD" },
    { "ARK_CONTENT_TYPE_FULL_STREET_ADDRESS",
        Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_FULL_STREET_ADDRESS),
        "TextContentType.FULL_STREET_ADDRESS" },
    { "ARK_CONTENT_TYPE_HOUSE_NUMBER", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_HOUSE_NUMBER),
        "TextContentType.HOUSE_NUMBER" },
    { "ARK_CONTENT_TYPE_DISTRICT_ADDRESS", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_DISTRICT_ADDRESS),
        "TextContentType.DISTRICT_ADDRESS" },
    { "ARK_CONTENT_TYPE_CITY_ADDRESS", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_CITY_ADDRESS),
        "TextContentType.CITY_ADDRESS" },
    { "ARK_CONTENT_TYPE_PROVINCE_ADDRESS", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_PROVINCE_ADDRESS),
        "TextContentType.PROVINCE_ADDRESS" },
    { "ARK_CONTENT_TYPE_COUNTRY_ADDRESS", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_COUNTRY_ADDRESS),
        "TextContentType.COUNTRY_ADDRESS" },
    { "ARK_CONTENT_TYPE_PERSON_FULL_NAME", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_PERSON_FULL_NAME),
        "TextContentType.PERSON_FULL_NAME" },
    { "ARK_CONTENT_TYPE_PERSON_LAST_NAME", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_PERSON_LAST_NAME),
        "TextContentType.PERSON_LAST_NAME" },
    { "ARK_CONTENT_TYPE_PERSON_FIRST_NAME",
        Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_PERSON_FIRST_NAME),
        "TextContentType.PERSON_FIRST_NAME" },
    { "ARK_CONTENT_TYPE_PHONE_NUMBER", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_PHONE_NUMBER),
        "TextContentType.PHONE_NUMBER" },
    { "ARK_CONTENT_TYPE_PHONE_COUNTRY_CODE",
        Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_PHONE_COUNTRY_CODE),
        "TextContentType.PHONE_COUNTRY_CODE" },
    { "ARK_CONTENT_TYPE_FULL_PHONE_NUMBER",
        Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_FULL_PHONE_NUMBER),
        "TextContentType.FULL_PHONE_NUMBER" },
    { "ARK_CONTENT_TYPE_EMAIL_ADDRESS", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_EMAIL_ADDRESS),
        "TextContentType.EMAIL_ADDRESS" },
    { "ARK_CONTENT_TYPE_BANK_CARD_NUMBER", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_BANK_CARD_NUMBER),
        "TextContentType.BANK_CARD_NUMBER" },
    { "ARK_CONTENT_TYPE_ID_CARD_NUMBER", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_ID_CARD_NUMBER),
        "TextContentType.ID_CARD_NUMBER" },
    { "ARK_CONTENT_TYPE_NICKNAME", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_NICKNAME),
        "TextContentType.NICKNAME" },
    { "ARK_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET",
        Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET),
        "TextContentType.DETAIL_INFO_WITHOUT_STREET" },
    { "ARK_CONTENT_TYPE_FORMAT_ADDRESS", Converter::ArkValue<enum Ark_ContentType>(ARK_CONTENT_TYPE_FORMAT_ADDRESS),
        "TextContentType.FORMAT_ADDRESS" },
};

/*
 * @tc.name: setContentTypeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setContentTypeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ContentType inputValueContentType;
    Ark_ContentType initValueContentType;

    // Initial setup
    initValueContentType = std::get<1>(contentTypeContentTypeValidValues[0]);

    // Verifying attribute's  values
    inputValueContentType = initValueContentType;
    for (auto&& value : contentTypeContentTypeValidValues) {
        inputValueContentType = std::get<1>(value);
        modifier_->setContentType(node_, inputValueContentType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'contentType' of method 'contentType'
static std::vector<std::tuple<std::string, enum Ark_ContentType>> contentTypeContentTypeInvalidValues = {
    { "static_cast<enum Ark_ContentType>(-1)",
        Converter::ArkValue<enum Ark_ContentType>(static_cast<enum Ark_ContentType>(-1)) },
};

/*
 * @tc.name: setContentTypeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setContentTypeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ContentType inputValueContentType;
    Ark_ContentType initValueContentType;

    // Initial setup
    initValueContentType = std::get<1>(contentTypeContentTypeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : contentTypeContentTypeInvalidValues) {
        inputValueContentType = initValueContentType;
        modifier_->setContentType(node_, inputValueContentType);
        inputValueContentType = std::get<1>(value);
        modifier_->setContentType(node_, inputValueContentType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
        expectedStr = ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPlaceholderColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setPlaceholderColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setTextOverflowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextOverflowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE);
}

// Valid values for attribute 'textOverflow' of method 'textOverflow'
static std::vector<std::tuple<std::string, enum Ark_TextOverflow, std::string>> textOverflowTextOverflowValidValues = {
    { "ARK_TEXT_OVERFLOW_NONE", Converter::ArkValue<enum Ark_TextOverflow>(ARK_TEXT_OVERFLOW_NONE),
        "TextOverflow.None" },
    { "ARK_TEXT_OVERFLOW_CLIP", Converter::ArkValue<enum Ark_TextOverflow>(ARK_TEXT_OVERFLOW_CLIP),
        "TextOverflow.Clip" },
    { "ARK_TEXT_OVERFLOW_ELLIPSIS", Converter::ArkValue<enum Ark_TextOverflow>(ARK_TEXT_OVERFLOW_ELLIPSIS),
        "TextOverflow.Ellipsis" },
    { "ARK_TEXT_OVERFLOW_MARQUEE", Converter::ArkValue<enum Ark_TextOverflow>(ARK_TEXT_OVERFLOW_MARQUEE),
        "TextOverflow.Marquee" },
};

/*
 * @tc.name: setTextOverflowTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextOverflowTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_TextOverflow inputValueTextOverflow;
    Ark_TextOverflow initValueTextOverflow;

    // Initial setup
    initValueTextOverflow = std::get<1>(textOverflowTextOverflowValidValues[0]);

    // Verifying attribute's  values
    inputValueTextOverflow = initValueTextOverflow;
    for (auto&& value : textOverflowTextOverflowValidValues) {
        inputValueTextOverflow = std::get<1>(value);
        modifier_->setTextOverflow(node_, inputValueTextOverflow);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'textOverflow' of method 'textOverflow'
static std::vector<std::tuple<std::string, enum Ark_TextOverflow>> textOverflowTextOverflowInvalidValues = {
    { "static_cast<enum Ark_TextOverflow>(-1)",
        Converter::ArkValue<enum Ark_TextOverflow>(static_cast<enum Ark_TextOverflow>(-1)) },
};

/*
 * Blocked by https://gitee.com/openharmony/arkui_ace_engine/issues/IAXX0N
 * @tc.name: setTextOverflowTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTextOverflowTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_TextOverflow inputValueTextOverflow;
    Ark_TextOverflow initValueTextOverflow;

    // Initial setup
    initValueTextOverflow = std::get<1>(textOverflowTextOverflowValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : textOverflowTextOverflowInvalidValues) {
        inputValueTextOverflow = initValueTextOverflow;
        modifier_->setTextOverflow(node_, inputValueTextOverflow);
        inputValueTextOverflow = std::get<1>(value);
        modifier_->setTextOverflow(node_, inputValueTextOverflow);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        expectedStr = ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTextIndentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTextIndentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE);
}

// Valid values for attribute 'textIndent' of method 'textIndent'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> textIndentTextIndentValidValues = {};

/*
 * @tc.name: setTextIndentTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTextIndentTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueTextIndent;
    Ark_Length initValueTextIndent;

    // Initial setup
    initValueTextIndent = std::get<1>(textIndentTextIndentValidValues[0]);

    // Verifying attribute's  values
    inputValueTextIndent = initValueTextIndent;
    for (auto&& value : textIndentTextIndentValidValues) {
        inputValueTextIndent = std::get<1>(value);
        modifier_->setTextIndent(node_, &inputValueTextIndent);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTextIndentTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTextIndentTestInvalidValues, TestSize.Level1)
{
    // std::unique_ptr<JsonValue> jsonValue;
    // std::string resultStr;
    // std::string expectedStr;
    // Ark_Length inputValueTextIndent;
    Ark_Length initValueTextIndent;

    // Initial setup
    initValueTextIndent = std::get<1>(textIndentTextIndentValidValues[0]);
}

/*
 * @tc.name: setEnterKeyTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnterKeyTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE);
}

// Valid values for attribute 'enterKeyType' of method 'enterKeyType'
static std::vector<std::tuple<std::string, enum Ark_EnterKeyType, std::string>> enterKeyTypeEnterKeyTypeValidValues = {
    { "ARK_ENTER_KEY_TYPE_GO", Converter::ArkValue<enum Ark_EnterKeyType>(ARK_ENTER_KEY_TYPE_GO), "EnterKeyType.Go" },
    { "ARK_ENTER_KEY_TYPE_SEARCH", Converter::ArkValue<enum Ark_EnterKeyType>(ARK_ENTER_KEY_TYPE_SEARCH),
        "EnterKeyType.Search" },
    { "ARK_ENTER_KEY_TYPE_SEND", Converter::ArkValue<enum Ark_EnterKeyType>(ARK_ENTER_KEY_TYPE_SEND),
        "EnterKeyType.Send" },
    { "ARK_ENTER_KEY_TYPE_NEXT", Converter::ArkValue<enum Ark_EnterKeyType>(ARK_ENTER_KEY_TYPE_NEXT),
        "EnterKeyType.Next" },
    { "ARK_ENTER_KEY_TYPE_DONE", Converter::ArkValue<enum Ark_EnterKeyType>(ARK_ENTER_KEY_TYPE_DONE),
        "EnterKeyType.Done" },
    { "ARK_ENTER_KEY_TYPE_PREVIOUS", Converter::ArkValue<enum Ark_EnterKeyType>(ARK_ENTER_KEY_TYPE_PREVIOUS),
        "EnterKeyType.PREVIOUS" },
    { "ARK_ENTER_KEY_TYPE_NEW_LINE", Converter::ArkValue<enum Ark_EnterKeyType>(ARK_ENTER_KEY_TYPE_NEW_LINE),
        "EnterKeyType.NEW_LINE" },
};

/*
 * @tc.name: setEnterKeyTypeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnterKeyTypeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_EnterKeyType inputValueEnterKeyType;
    Ark_EnterKeyType initValueEnterKeyType;

    // Initial setup
    initValueEnterKeyType = std::get<1>(enterKeyTypeEnterKeyTypeValidValues[0]);

    // Verifying attribute's  values
    inputValueEnterKeyType = initValueEnterKeyType;
    for (auto&& value : enterKeyTypeEnterKeyTypeValidValues) {
        inputValueEnterKeyType = std::get<1>(value);
        modifier_->setEnterKeyType(node_, inputValueEnterKeyType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'enterKeyType' of method 'enterKeyType'
static std::vector<std::tuple<std::string, enum Ark_EnterKeyType>> enterKeyTypeEnterKeyTypeInvalidValues = {
    { "static_cast<enum Ark_EnterKeyType>(-1)",
        Converter::ArkValue<enum Ark_EnterKeyType>(static_cast<enum Ark_EnterKeyType>(-1)) },
};

/*
 * @tc.name: setEnterKeyTypeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnterKeyTypeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_EnterKeyType inputValueEnterKeyType;
    Ark_EnterKeyType initValueEnterKeyType;

    // Initial setup
    initValueEnterKeyType = std::get<1>(enterKeyTypeEnterKeyTypeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : enterKeyTypeEnterKeyTypeInvalidValues) {
        inputValueEnterKeyType = initValueEnterKeyType;
        modifier_->setEnterKeyType(node_, inputValueEnterKeyType);
        inputValueEnterKeyType = std::get<1>(value);
        modifier_->setEnterKeyType(node_, inputValueEnterKeyType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
        expectedStr = ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setCaretColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCaretColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setMaxLengthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLengthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE);
}

// Valid values for attribute 'maxLength' of method 'maxLength'
static std::vector<std::tuple<std::string, Ark_Number, std::string>> maxLengthMaxLengthValidValues = {};

/*
 * @tc.name: setMaxLengthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLengthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Number inputValueMaxLength;
    Ark_Number initValueMaxLength;

    // Initial setup
    initValueMaxLength = std::get<1>(maxLengthMaxLengthValidValues[0]);

    // Verifying attribute's  values
    inputValueMaxLength = initValueMaxLength;
    for (auto&& value : maxLengthMaxLengthValidValues) {
        inputValueMaxLength = std::get<1>(value);
        modifier_->setMaxLength(node_, &inputValueMaxLength);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setMaxLengthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLengthTestInvalidValues, TestSize.Level1)
{
    // std::unique_ptr<JsonValue> jsonValue;
    // std::string resultStr;
    // std::string expectedStr;
    // Ark_Number inputValueMaxLength;
    Ark_Number initValueMaxLength;

    // Initial setup
    initValueMaxLength = std::get<1>(maxLengthMaxLengthValidValues[0]);
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
}

// Valid values for attribute 'fontSize' of method 'fontSize'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> fontSizeFontSizeValidValues = {};

/*
 * @tc.name: setFontSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueFontSize;
    Ark_Length initValueFontSize;

    // Initial setup
    initValueFontSize = std::get<1>(fontSizeFontSizeValidValues[0]);

    // Verifying attribute's  values
    inputValueFontSize = initValueFontSize;
    for (auto&& value : fontSizeFontSizeValidValues) {
        inputValueFontSize = std::get<1>(value);
        modifier_->setFontSize(node_, &inputValueFontSize);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontSizeTestInvalidValues, TestSize.Level1)
{
    // std::unique_ptr<JsonValue> jsonValue;
    // std::string resultStr;
    // std::string expectedStr;
    // Ark_Length inputValueFontSize;
    Ark_Length initValueFontSize;

    // Initial setup
    initValueFontSize = std::get<1>(fontSizeFontSizeValidValues[0]);
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
}

// Valid values for attribute 'fontStyle' of method 'fontStyle'
static std::vector<std::tuple<std::string, enum Ark_FontStyle, std::string>> fontStyleFontStyleValidValues = {
    { "ARK_FONT_STYLE_NORMAL", Converter::ArkValue<enum Ark_FontStyle>(ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { "ARK_FONT_STYLE_ITALIC", Converter::ArkValue<enum Ark_FontStyle>(ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
};

/*
 * @tc.name: setFontStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontStyleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_FontStyle inputValueFontStyle;
    Ark_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = std::get<1>(fontStyleFontStyleValidValues[0]);

    // Verifying attribute's  values
    inputValueFontStyle = initValueFontStyle;
    for (auto&& value : fontStyleFontStyleValidValues) {
        inputValueFontStyle = std::get<1>(value);
        modifier_->setFontStyle(node_, inputValueFontStyle);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'fontStyle' of method 'fontStyle'
static std::vector<std::tuple<std::string, enum Ark_FontStyle>> fontStyleFontStyleInvalidValues = {
    { "static_cast<enum Ark_FontStyle>(-1)",
        Converter::ArkValue<enum Ark_FontStyle>(static_cast<enum Ark_FontStyle>(-1)) },
};

/*
 * @tc.name: setFontStyleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontStyleTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_FontStyle inputValueFontStyle;
    Ark_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = std::get<1>(fontStyleFontStyleValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : fontStyleFontStyleInvalidValues) {
        inputValueFontStyle = initValueFontStyle;
        modifier_->setFontStyle(node_, inputValueFontStyle);
        inputValueFontStyle = std::get<1>(value);
        modifier_->setFontStyle(node_, inputValueFontStyle);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        expectedStr = ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFamilyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
}

/*
 * @tc.name: setInputFilterTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setInputFilterTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INPUT_FILTER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_INPUT_FILTER_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INPUT_FILTER_ERROR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_INPUT_FILTER_ERROR_DEFAULT_VALUE);
}

/*
 * @tc.name: setCopyOptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCopyOptionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE);
}

// Valid values for attribute 'copyOption' of method 'copyOption'
static std::vector<std::tuple<std::string, enum Ark_CopyOptions, std::string>> copyOptionCopyOptionValidValues = {
    { "ARK_COPY_OPTIONS_NONE", Converter::ArkValue<enum Ark_CopyOptions>(ARK_COPY_OPTIONS_NONE), "CopyOptions.None" },
    { "ARK_COPY_OPTIONS_IN_APP", Converter::ArkValue<enum Ark_CopyOptions>(ARK_COPY_OPTIONS_IN_APP),
        "CopyOptions.InApp" },
    { "ARK_COPY_OPTIONS_LOCAL_DEVICE", Converter::ArkValue<enum Ark_CopyOptions>(ARK_COPY_OPTIONS_LOCAL_DEVICE),
        "CopyOptions.Local" },
    { "ARK_COPY_OPTIONS_CROSS_DEVICE", Converter::ArkValue<enum Ark_CopyOptions>(ARK_COPY_OPTIONS_CROSS_DEVICE),
        "CopyOptions.Distributed" },
};

/*
 * @tc.name: setCopyOptionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCopyOptionTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_CopyOptions inputValueCopyOption;
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(copyOptionCopyOptionValidValues[0]);

    // Verifying attribute's  values
    inputValueCopyOption = initValueCopyOption;
    for (auto&& value : copyOptionCopyOptionValidValues) {
        inputValueCopyOption = std::get<1>(value);
        modifier_->setCopyOption(node_, inputValueCopyOption);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'copyOption' of method 'copyOption'
static std::vector<std::tuple<std::string, enum Ark_CopyOptions>> copyOptionCopyOptionInvalidValues = {
    { "static_cast<enum Ark_CopyOptions>(-1)",
        Converter::ArkValue<enum Ark_CopyOptions>(static_cast<enum Ark_CopyOptions>(-1)) },
};

/*
 * @tc.name: setCopyOptionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCopyOptionTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_CopyOptions inputValueCopyOption;
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(copyOptionCopyOptionValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : copyOptionCopyOptionInvalidValues) {
        inputValueCopyOption = initValueCopyOption;
        modifier_->setCopyOption(node_, inputValueCopyOption);
        inputValueCopyOption = std::get<1>(value);
        modifier_->setCopyOption(node_, inputValueCopyOption);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        expectedStr = "CopyOptions.Local";
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setShowPasswordIconTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordIconTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_ICON_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_PASSWORD_ICON_DEFAULT_VALUE);
}

// Valid values for attribute 'showPasswordIcon' of method 'showPasswordIcon'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> showPasswordIconShowPasswordIconValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

/*
 * @tc.name: setShowPasswordIconTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordIconTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueShowPasswordIcon;
    Ark_Boolean initValueShowPasswordIcon;

    // Initial setup
    initValueShowPasswordIcon = std::get<1>(showPasswordIconShowPasswordIconValidValues[0]);

    // Verifying attribute's  values
    inputValueShowPasswordIcon = initValueShowPasswordIcon;
    for (auto&& value : showPasswordIconShowPasswordIconValidValues) {
        inputValueShowPasswordIcon = std::get<1>(value);
        modifier_->setShowPasswordIcon(node_, inputValueShowPasswordIcon);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_ICON_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTextAlignTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextAlignTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE);
}

// Valid values for attribute 'textAlign' of method 'textAlign'
static std::vector<std::tuple<std::string, enum Ark_TextAlign, std::string>> textAlignTextAlignValidValues = {
    { "ARK_TEXT_ALIGN_CENTER", Converter::ArkValue<enum Ark_TextAlign>(ARK_TEXT_ALIGN_CENTER), "TextAlign.Center" },
    { "ARK_TEXT_ALIGN_START", Converter::ArkValue<enum Ark_TextAlign>(ARK_TEXT_ALIGN_START), "TextAlign.Start" },
    { "ARK_TEXT_ALIGN_END", Converter::ArkValue<enum Ark_TextAlign>(ARK_TEXT_ALIGN_END), "TextAlign.End" },
};

/*
 * @tc.name: setTextAlignTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextAlignTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_TextAlign inputValueTextAlign;
    Ark_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = std::get<1>(textAlignTextAlignValidValues[0]);

    // Verifying attribute's  values
    inputValueTextAlign = initValueTextAlign;
    for (auto&& value : textAlignTextAlignValidValues) {
        inputValueTextAlign = std::get<1>(value);
        modifier_->setTextAlign(node_, inputValueTextAlign);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'textAlign' of method 'textAlign'
static std::vector<std::tuple<std::string, enum Ark_TextAlign>> textAlignTextAlignInvalidValues = {
    { "static_cast<enum Ark_TextAlign>(-1)",
        Converter::ArkValue<enum Ark_TextAlign>(static_cast<enum Ark_TextAlign>(-1)) },
    { "ARK_TEXT_ALIGN_JUSTIFY", Converter::ArkValue<enum Ark_TextAlign>(ARK_TEXT_ALIGN_JUSTIFY) },
    { "static_cast<enum Ark_TextAlign>(100)",
        Converter::ArkValue<enum Ark_TextAlign>(static_cast<enum Ark_TextAlign>(100)) },
};

/*
 * @tc.name: setTextAlignTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextAlignTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_TextAlign inputValueTextAlign;
    Ark_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = std::get<1>(textAlignTextAlignValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : textAlignTextAlignInvalidValues) {
        inputValueTextAlign = initValueTextAlign;
        modifier_->setTextAlign(node_, inputValueTextAlign);
        inputValueTextAlign = std::get<1>(value);
        modifier_->setTextAlign(node_, inputValueTextAlign);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
        expectedStr = ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setCaretStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCaretStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCaretStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_WIDTH_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setEnableKeyboardOnFocusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableKeyboardOnFocusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE);
}

// Valid values for attribute 'enableKeyboardOnFocus' of method 'enableKeyboardOnFocus'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>>
    enableKeyboardOnFocusEnableKeyboardOnFocusValidValues = {
        { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
        { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
    };

/*
 * @tc.name: setEnableKeyboardOnFocusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableKeyboardOnFocusTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueEnableKeyboardOnFocus;
    Ark_Boolean initValueEnableKeyboardOnFocus;

    // Initial setup
    initValueEnableKeyboardOnFocus = std::get<1>(enableKeyboardOnFocusEnableKeyboardOnFocusValidValues[0]);

    // Verifying attribute's  values
    inputValueEnableKeyboardOnFocus = initValueEnableKeyboardOnFocus;
    for (auto&& value : enableKeyboardOnFocusEnableKeyboardOnFocusValidValues) {
        inputValueEnableKeyboardOnFocus = std::get<1>(value);
        modifier_->setEnableKeyboardOnFocus(node_, inputValueEnableKeyboardOnFocus);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPasswordIconTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setPasswordIconTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPasswordIcon =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_ON_ICON_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_ICON_ON_ICON_SRC_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_OFF_ICON_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_ICON_OFF_ICON_SRC_DEFAULT_VALUE);
}

// Valid values for attribute 'onIconSrc' of method 'passwordIcon'
static std::vector<std::tuple<std::string, Opt_Union_String_Resource, std::string>>
    passwordIconOnIconSrcValidValues = {};

// Valid values for attribute 'offIconSrc' of method 'passwordIcon'
static std::vector<std::tuple<std::string, Opt_Union_String_Resource, std::string>>
    passwordIconOffIconSrcValidValues = {};

/*
 * @tc.name: setPasswordIconTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setPasswordIconTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPasswordIcon;
    std::string resultStr;
    std::string expectedStr;
    Ark_PasswordIcon inputValuePasswordIcon;
    Ark_PasswordIcon initValuePasswordIcon;

    // Initial setup
    initValuePasswordIcon.onIconSrc = std::get<1>(passwordIconOnIconSrcValidValues[0]);
    initValuePasswordIcon.offIconSrc = std::get<1>(passwordIconOffIconSrcValidValues[0]);

    // Verifying attribute's 'onIconSrc'  values
    inputValuePasswordIcon = initValuePasswordIcon;
    for (auto&& value : passwordIconOnIconSrcValidValues) {
        inputValuePasswordIcon.onIconSrc = std::get<1>(value);
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        jsonValue = GetJsonValue(node_);
        resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_ON_ICON_SRC_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'offIconSrc'  values
    inputValuePasswordIcon = initValuePasswordIcon;
    for (auto&& value : passwordIconOffIconSrcValidValues) {
        inputValuePasswordIcon.offIconSrc = std::get<1>(value);
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        jsonValue = GetJsonValue(node_);
        resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_OFF_ICON_SRC_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'onIconSrc' of method 'passwordIcon'
static std::vector<std::tuple<std::string, Opt_Union_String_Resource>> passwordIconOnIconSrcInvalidValues = {
    { "Ark_Empty()", Converter::ArkUnion<Opt_Union_String_Resource>(Ark_Empty()) },
    { "nullptr", Converter::ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr) },
};

// Invalid values for attribute 'offIconSrc' of method 'passwordIcon'
static std::vector<std::tuple<std::string, Opt_Union_String_Resource>> passwordIconOffIconSrcInvalidValues = {
    { "Ark_Empty()", Converter::ArkUnion<Opt_Union_String_Resource>(Ark_Empty()) },
    { "nullptr", Converter::ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr) },
};

/*
 * @tc.name: setPasswordIconTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setPasswordIconTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPasswordIcon;
    std::string resultStr;
    std::string expectedStr;
    Ark_PasswordIcon inputValuePasswordIcon;
    Ark_PasswordIcon initValuePasswordIcon;

    // Initial setup
    initValuePasswordIcon.onIconSrc = std::get<1>(passwordIconOnIconSrcValidValues[0]);
    initValuePasswordIcon.offIconSrc = std::get<1>(passwordIconOffIconSrcValidValues[0]);

    // Verifying attribute's 'onIconSrc'  values
    for (auto&& value : passwordIconOnIconSrcInvalidValues) {
        inputValuePasswordIcon = initValuePasswordIcon;
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        inputValuePasswordIcon.onIconSrc = std::get<1>(value);
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        jsonValue = GetJsonValue(node_);
        resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_ON_ICON_SRC_NAME);
        expectedStr = ATTRIBUTE_PASSWORD_ICON_ON_ICON_SRC_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'offIconSrc'  values
    for (auto&& value : passwordIconOffIconSrcInvalidValues) {
        inputValuePasswordIcon = initValuePasswordIcon;
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        inputValuePasswordIcon.offIconSrc = std::get<1>(value);
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        jsonValue = GetJsonValue(node_);
        resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_OFF_ICON_SRC_NAME);
        expectedStr = ATTRIBUTE_PASSWORD_ICON_OFF_ICON_SRC_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setShowUnitTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setShowUnitTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_UNIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_UNIT_DEFAULT_VALUE);
}

/*
 * @tc.name: setShowUnderlineTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowUnderlineTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_UNDERLINE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_UNDERLINE_DEFAULT_VALUE);
}

// Valid values for attribute 'showUnderline' of method 'showUnderline'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> showUnderlineShowUnderlineValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

/*
 * @tc.name: setShowUnderlineTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowUnderlineTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueShowUnderline;
    Ark_Boolean initValueShowUnderline;

    // Initial setup
    initValueShowUnderline = std::get<1>(showUnderlineShowUnderlineValidValues[0]);

    // Verifying attribute's  values
    inputValueShowUnderline = initValueShowUnderline;
    for (auto&& value : showUnderlineShowUnderlineValidValues) {
        inputValueShowUnderline = std::get<1>(value);
        modifier_->setShowUnderline(node_, inputValueShowUnderline);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_UNDERLINE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setSelectionMenuHiddenTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectionMenuHiddenTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_HIDDEN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_MENU_HIDDEN_DEFAULT_VALUE);
}

// Valid values for attribute 'selectionMenuHidden' of method 'selectionMenuHidden'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>>
    selectionMenuHiddenSelectionMenuHiddenValidValues = {
        { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
        { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
    };

/*
 * @tc.name: setSelectionMenuHiddenTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectionMenuHiddenTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueSelectionMenuHidden;
    Ark_Boolean initValueSelectionMenuHidden;

    // Initial setup
    initValueSelectionMenuHidden = std::get<1>(selectionMenuHiddenSelectionMenuHiddenValidValues[0]);

    // Verifying attribute's  values
    inputValueSelectionMenuHidden = initValueSelectionMenuHidden;
    for (auto&& value : selectionMenuHiddenSelectionMenuHiddenValidValues) {
        inputValueSelectionMenuHidden = std::get<1>(value);
        modifier_->setSelectionMenuHidden(node_, inputValueSelectionMenuHidden);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_HIDDEN_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBarStateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setBarStateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE);
}

// Valid values for attribute 'barState' of method 'barState'
static std::vector<std::tuple<std::string, enum Ark_BarState, std::string>> barStateBarStateValidValues = {
    { "ARK_BAR_STATE_OFF", Converter::ArkValue<enum Ark_BarState>(ARK_BAR_STATE_OFF), "BarState.OFF" },
    { "ARK_BAR_STATE_AUTO", Converter::ArkValue<enum Ark_BarState>(ARK_BAR_STATE_AUTO), "BarState.AUTO" },
    { "ARK_BAR_STATE_ON", Converter::ArkValue<enum Ark_BarState>(ARK_BAR_STATE_ON), "BarState.ON" },
};

/*
 * @tc.name: setBarStateTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setBarStateTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_BarState inputValueBarState;
    Ark_BarState initValueBarState;

    // Initial setup
    initValueBarState = std::get<1>(barStateBarStateValidValues[0]);

    // Verifying attribute's  values
    inputValueBarState = initValueBarState;
    for (auto&& value : barStateBarStateValidValues) {
        inputValueBarState = std::get<1>(value);
        modifier_->setBarState(node_, inputValueBarState);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'barState' of method 'barState'
static std::vector<std::tuple<std::string, enum Ark_BarState>> barStateBarStateInvalidValues = {
    { "static_cast<enum Ark_BarState>(-1)",
        Converter::ArkValue<enum Ark_BarState>(static_cast<enum Ark_BarState>(-1)) },
};

/*
 * @tc.name: setBarStateTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setBarStateTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_BarState inputValueBarState;
    Ark_BarState initValueBarState;

    // Initial setup
    initValueBarState = std::get<1>(barStateBarStateValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : barStateBarStateInvalidValues) {
        inputValueBarState = initValueBarState;
        modifier_->setBarState(node_, inputValueBarState);
        inputValueBarState = std::get<1>(value);
        modifier_->setBarState(node_, inputValueBarState);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        expectedStr = ATTRIBUTE_BAR_STATE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLinesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE);
}

// Valid values for attribute 'maxLines' of method 'maxLines'
static std::vector<std::tuple<std::string, Ark_Number, std::string>> maxLinesMaxLinesValidValues = {};

/*
 * @tc.name: setMaxLinesTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLinesTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Number inputValueMaxLines;
    Ark_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(maxLinesMaxLinesValidValues[0]);

    // Verifying attribute's  values
    inputValueMaxLines = initValueMaxLines;
    for (auto&& value : maxLinesMaxLinesValidValues) {
        inputValueMaxLines = std::get<1>(value);
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setMaxLinesTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLinesTestInvalidValues, TestSize.Level1)
{
    // std::unique_ptr<JsonValue> jsonValue;
    // std::string resultStr;
    // std::string expectedStr;
    // Ark_Number inputValueMaxLines;
    Ark_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(maxLinesMaxLinesValidValues[0]);
}

/*
 * @tc.name: setWordBreakTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setWordBreakTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE);
}

// Valid values for attribute 'wordBreak' of method 'wordBreak'
static std::vector<std::tuple<std::string, enum Ark_WordBreak, std::string>> wordBreakWordBreakValidValues = {
    { "ARK_WORD_BREAK_NORMAL", Converter::ArkValue<enum Ark_WordBreak>(ARK_WORD_BREAK_NORMAL), "normal" },
    { "ARK_WORD_BREAK_BREAK_ALL", Converter::ArkValue<enum Ark_WordBreak>(ARK_WORD_BREAK_BREAK_ALL), "break-all" },
    { "ARK_WORD_BREAK_BREAK_WORD", Converter::ArkValue<enum Ark_WordBreak>(ARK_WORD_BREAK_BREAK_WORD), "break-word" },
};

/*
 * @tc.name: setWordBreakTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setWordBreakTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_WordBreak inputValueWordBreak;
    Ark_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = std::get<1>(wordBreakWordBreakValidValues[0]);

    // Verifying attribute's  values
    inputValueWordBreak = initValueWordBreak;
    for (auto&& value : wordBreakWordBreakValidValues) {
        inputValueWordBreak = std::get<1>(value);
        modifier_->setWordBreak(node_, inputValueWordBreak);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'wordBreak' of method 'wordBreak'
static std::vector<std::tuple<std::string, enum Ark_WordBreak>> wordBreakWordBreakInvalidValues = {
    { "static_cast<enum Ark_WordBreak>(-1)",
        Converter::ArkValue<enum Ark_WordBreak>(static_cast<enum Ark_WordBreak>(-1)) },
};

/*
 * @tc.name: setWordBreakTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setWordBreakTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_WordBreak inputValueWordBreak;
    Ark_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = std::get<1>(wordBreakWordBreakValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : wordBreakWordBreakInvalidValues) {
        inputValueWordBreak = initValueWordBreak;
        modifier_->setWordBreak(node_, inputValueWordBreak);
        inputValueWordBreak = std::get<1>(value);
        modifier_->setWordBreak(node_, inputValueWordBreak);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        expectedStr = ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setLineBreakStrategyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineBreakStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LINE_BREAK_STRATEGY_STRATEGY_DEFAULT_VALUE);
}

// Valid values for attribute 'lineBreakStrategyStrategy' of method 'lineBreakStrategy'
static std::vector<std::tuple<std::string, enum Ark_LineBreakStrategy, std::string>>
    lineBreakStrategyLineBreakStrategyStrategyValidValues = {
        { "ARK_LINE_BREAK_STRATEGY_GREEDY",
            Converter::ArkValue<enum Ark_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_GREEDY), "greedy" },
        { "ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY",
            Converter::ArkValue<enum Ark_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY), "high-quality" },
        { "ARK_LINE_BREAK_STRATEGY_BALANCED",
            Converter::ArkValue<enum Ark_LineBreakStrategy>(ARK_LINE_BREAK_STRATEGY_BALANCED), "balanced" },
    };

/*
 * @tc.name: setLineBreakStrategyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineBreakStrategyTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_LineBreakStrategy inputValueLineBreakStrategyStrategy;
    Ark_LineBreakStrategy initValueLineBreakStrategyStrategy;

    // Initial setup
    initValueLineBreakStrategyStrategy = std::get<1>(lineBreakStrategyLineBreakStrategyStrategyValidValues[0]);

    // Verifying attribute's  values
    inputValueLineBreakStrategyStrategy = initValueLineBreakStrategyStrategy;
    for (auto&& value : lineBreakStrategyLineBreakStrategyStrategyValidValues) {
        inputValueLineBreakStrategyStrategy = std::get<1>(value);
        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategyStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_STRATEGY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'lineBreakStrategyStrategy' of method 'lineBreakStrategy'
static std::vector<std::tuple<std::string, enum Ark_LineBreakStrategy>>
    lineBreakStrategyLineBreakStrategyStrategyInvalidValues = {
        { "static_cast<enum Ark_LineBreakStrategy>(-1)",
            Converter::ArkValue<enum Ark_LineBreakStrategy>(static_cast<enum Ark_LineBreakStrategy>(-1)) },
    };

/*
 * @tc.name: setLineBreakStrategyTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineBreakStrategyTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_LineBreakStrategy inputValueLineBreakStrategyStrategy;
    Ark_LineBreakStrategy initValueLineBreakStrategyStrategy;

    // Initial setup
    initValueLineBreakStrategyStrategy = std::get<1>(lineBreakStrategyLineBreakStrategyStrategyValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : lineBreakStrategyLineBreakStrategyStrategyInvalidValues) {
        inputValueLineBreakStrategyStrategy = initValueLineBreakStrategyStrategy;
        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategyStrategy);
        inputValueLineBreakStrategyStrategy = std::get<1>(value);
        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategyStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_STRATEGY_NAME);
        expectedStr = "line-break-strategy";
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setCustomKeyboardTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCustomKeyboardTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCustomKeyboardOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CUSTOM_KEYBOARD_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CUSTOM_KEYBOARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CUSTOM_KEYBOARD_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(
        resultCustomKeyboardOptions, ATTRIBUTE_CUSTOM_KEYBOARD_OPTIONS_SUPPORT_AVOIDANCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CUSTOM_KEYBOARD_OPTIONS_SUPPORT_AVOIDANCE_DEFAULT_VALUE);
}

// Valid values for attribute 'supportAvoidance' of method 'customKeyboard'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> customKeyboardSupportAvoidanceValidValues = {
    { "true", Converter::ArkValue<Opt_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Opt_Boolean>(false), "false" },
};

// Invalid values for attribute 'supportAvoidance' of method 'customKeyboard'
static std::vector<std::tuple<std::string, Opt_Boolean>> customKeyboardSupportAvoidanceInvalidValues = {
    { "Ark_Empty()", Converter::ArkValue<Opt_Boolean>(Ark_Empty()) },
};

/*
 * @tc.name: setShowCounterTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setShowCounterTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultShowCounterOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_DEFAULT_VALUE);

    resultStr =
        GetAttrValue<std::string>(resultShowCounterOptions, ATTRIBUTE_SHOW_COUNTER_OPTIONS_THRESHOLD_PERCENTAGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_OPTIONS_THRESHOLD_PERCENTAGE_DEFAULT_VALUE);

    resultStr =
        GetAttrValue<std::string>(resultShowCounterOptions, ATTRIBUTE_SHOW_COUNTER_OPTIONS_HIGHLIGHT_BORDER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_OPTIONS_HIGHLIGHT_BORDER_DEFAULT_VALUE);
}

// Valid values for attribute 'showCounter' of method 'showCounter'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> showCounterShowCounterValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

// Valid values for attribute 'thresholdPercentage' of method 'showCounter'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> showCounterThresholdPercentageValidValues = {};

// Valid values for attribute 'highlightBorder' of method 'showCounter'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> showCounterHighlightBorderValidValues = {
    { "true", Converter::ArkValue<Opt_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Opt_Boolean>(false), "false" },
};

/*
 * @tc.name: setShowCounterTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setShowCounterTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultShowCounterOptions;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueShowCounter;
    Ark_Boolean initValueShowCounter;
    Opt_InputCounterOptions realInputValue1 = { .tag = ARK_TAG_OBJECT, .value = {} };
    Ark_InputCounterOptions& inputValueShowCounterOptions = realInputValue1.value;
    Ark_InputCounterOptions initValueShowCounterOptions;

    // Initial setup
    initValueShowCounter = std::get<1>(showCounterShowCounterValidValues[0]);
    initValueShowCounterOptions.thresholdPercentage = std::get<1>(showCounterThresholdPercentageValidValues[0]);
    initValueShowCounterOptions.highlightBorder = std::get<1>(showCounterHighlightBorderValidValues[0]);

    // Verifying attribute's  values
    inputValueShowCounter = initValueShowCounter;
    for (auto&& value : showCounterShowCounterValidValues) {
        inputValueShowCounter = std::get<1>(value);
        modifier_->setShowCounter(node_, inputValueShowCounter, &realInputValue1);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'thresholdPercentage'  values
    inputValueShowCounterOptions = initValueShowCounterOptions;
    for (auto&& value : showCounterThresholdPercentageValidValues) {
        inputValueShowCounterOptions.thresholdPercentage = std::get<1>(value);
        modifier_->setShowCounter(node_, inputValueShowCounter, &realInputValue1);
        jsonValue = GetJsonValue(node_);
        resultShowCounterOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(
            resultShowCounterOptions, ATTRIBUTE_SHOW_COUNTER_OPTIONS_THRESHOLD_PERCENTAGE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'highlightBorder'  values
    inputValueShowCounterOptions = initValueShowCounterOptions;
    for (auto&& value : showCounterHighlightBorderValidValues) {
        inputValueShowCounterOptions.highlightBorder = std::get<1>(value);
        modifier_->setShowCounter(node_, inputValueShowCounter, &realInputValue1);
        jsonValue = GetJsonValue(node_);
        resultShowCounterOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_OPTIONS_NAME);
        resultStr =
            GetAttrValue<std::string>(resultShowCounterOptions, ATTRIBUTE_SHOW_COUNTER_OPTIONS_HIGHLIGHT_BORDER_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'thresholdPercentage' of method 'showCounter'
static std::vector<std::tuple<std::string, Opt_Number>> showCounterThresholdPercentageInvalidValues = {
    { "Ark_Empty()", Converter::ArkValue<Opt_Number>(Ark_Empty()) },
};

// Invalid values for attribute 'highlightBorder' of method 'showCounter'
static std::vector<std::tuple<std::string, Opt_Boolean>> showCounterHighlightBorderInvalidValues = {
    { "Ark_Empty()", Converter::ArkValue<Opt_Boolean>(Ark_Empty()) },
};

/*
 * @tc.name: setShowCounterTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setShowCounterTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultShowCounterOptions;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueShowCounter = 0;
    Ark_Boolean initValueShowCounter;
    Opt_InputCounterOptions realInputValue1 = { .tag = ARK_TAG_OBJECT, .value = {} };
    Ark_InputCounterOptions& inputValueShowCounterOptions = realInputValue1.value;
    Ark_InputCounterOptions initValueShowCounterOptions;

    // Initial setup
    initValueShowCounter = std::get<1>(showCounterShowCounterValidValues[0]);
    initValueShowCounterOptions.thresholdPercentage = std::get<1>(showCounterThresholdPercentageValidValues[0]);
    initValueShowCounterOptions.highlightBorder = std::get<1>(showCounterHighlightBorderValidValues[0]);

    // Verifying attribute's 'thresholdPercentage'  values
    for (auto&& value : showCounterThresholdPercentageInvalidValues) {
        inputValueShowCounterOptions = initValueShowCounterOptions;
        modifier_->setShowCounter(node_, inputValueShowCounter, &realInputValue1);
        inputValueShowCounterOptions.thresholdPercentage = std::get<1>(value);
        modifier_->setShowCounter(node_, inputValueShowCounter, &realInputValue1);
        jsonValue = GetJsonValue(node_);
        resultShowCounterOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(
            resultShowCounterOptions, ATTRIBUTE_SHOW_COUNTER_OPTIONS_THRESHOLD_PERCENTAGE_NAME);
        expectedStr = ATTRIBUTE_SHOW_COUNTER_OPTIONS_THRESHOLD_PERCENTAGE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'highlightBorder'  values
    for (auto&& value : showCounterHighlightBorderInvalidValues) {
        inputValueShowCounterOptions = initValueShowCounterOptions;
        modifier_->setShowCounter(node_, inputValueShowCounter, &realInputValue1);
        inputValueShowCounterOptions.highlightBorder = std::get<1>(value);
        modifier_->setShowCounter(node_, inputValueShowCounter, &realInputValue1);
        jsonValue = GetJsonValue(node_);
        resultShowCounterOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_OPTIONS_NAME);
        resultStr =
            GetAttrValue<std::string>(resultShowCounterOptions, ATTRIBUTE_SHOW_COUNTER_OPTIONS_HIGHLIGHT_BORDER_NAME);
        expectedStr = ATTRIBUTE_SHOW_COUNTER_OPTIONS_HIGHLIGHT_BORDER_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setCancelButtonTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCancelButtonTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectAllTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectAllTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_ALL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECT_ALL_DEFAULT_VALUE);
}

// Valid values for attribute 'selectAll' of method 'selectAll'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> selectAllSelectAllValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

/*
 * @tc.name: setSelectAllTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectAllTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueSelectAll;
    Ark_Boolean initValueSelectAll;

    // Initial setup
    initValueSelectAll = std::get<1>(selectAllSelectAllValidValues[0]);

    // Verifying attribute's  values
    inputValueSelectAll = initValueSelectAll;
    for (auto&& value : selectAllSelectAllValidValues) {
        inputValueSelectAll = std::get<1>(value);
        modifier_->setSelectAll(node_, inputValueSelectAll);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_ALL_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setHeightAdaptivePolicyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHeightAdaptivePolicyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE);
}

// Valid values for attribute 'heightAdaptivePolicy' of method 'heightAdaptivePolicy'
static std::vector<std::tuple<std::string, enum Ark_TextHeightAdaptivePolicy, std::string>>
    heightAdaptivePolicyHeightAdaptivePolicyValidValues = {
        { "ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST",
            Converter::ArkValue<enum Ark_TextHeightAdaptivePolicy>(ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST),
            "TextHeightAdaptivePolicy.MAX_LINES_FIRST" },
        { "ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST",
            Converter::ArkValue<enum Ark_TextHeightAdaptivePolicy>(ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST),
            "TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST" },
        { "ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST",
            Converter::ArkValue<enum Ark_TextHeightAdaptivePolicy>(
                ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST),
            "TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST" },
    };

/*
 * @tc.name: setHeightAdaptivePolicyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHeightAdaptivePolicyTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy;
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(heightAdaptivePolicyHeightAdaptivePolicyValidValues[0]);

    // Verifying attribute's  values
    inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;
    for (auto&& value : heightAdaptivePolicyHeightAdaptivePolicyValidValues) {
        inputValueHeightAdaptivePolicy = std::get<1>(value);
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'heightAdaptivePolicy' of method 'heightAdaptivePolicy'
static std::vector<std::tuple<std::string, enum Ark_TextHeightAdaptivePolicy>>
    heightAdaptivePolicyHeightAdaptivePolicyInvalidValues = {
        { "static_cast<enum Ark_TextHeightAdaptivePolicy>(-1)",
            Converter::ArkValue<enum Ark_TextHeightAdaptivePolicy>(
                static_cast<enum Ark_TextHeightAdaptivePolicy>(-1)) },
    };

/*
 * @tc.name: setHeightAdaptivePolicyTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHeightAdaptivePolicyTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy;
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(heightAdaptivePolicyHeightAdaptivePolicyValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value : heightAdaptivePolicyHeightAdaptivePolicyInvalidValues) {
        inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        inputValueHeightAdaptivePolicy = std::get<1>(value);
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        expectedStr = ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setEnableAutoFillTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableAutoFillTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_AUTO_FILL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_AUTO_FILL_DEFAULT_VALUE);
}

// Valid values for attribute 'enableAutoFill' of method 'enableAutoFill'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> enableAutoFillEnableAutoFillValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

/*
 * @tc.name: setEnableAutoFillTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableAutoFillTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueEnableAutoFill;
    Ark_Boolean initValueEnableAutoFill;

    // Initial setup
    initValueEnableAutoFill = std::get<1>(enableAutoFillEnableAutoFillValidValues[0]);

    // Verifying attribute's  values
    inputValueEnableAutoFill = initValueEnableAutoFill;
    for (auto&& value : enableAutoFillEnableAutoFillValidValues) {
        inputValueEnableAutoFill = std::get<1>(value);
        modifier_->setEnableAutoFill(node_, inputValueEnableAutoFill);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_AUTO_FILL_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setDecorationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDecoration =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_TYPE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_COLOR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_STYLE_DEFAULT_VALUE);
}

// Valid values for attribute 'type' of method 'decoration'
static std::vector<std::tuple<std::string, Ark_TextDecorationType, std::string>> decorationTypeValidValues = {
    { "ARK_TEXT_DECORATION_TYPE_NONE", Converter::ArkValue<Ark_TextDecorationType>(ARK_TEXT_DECORATION_TYPE_NONE),
        "TextDecorationType.NONE" },
    { "ARK_TEXT_DECORATION_TYPE_UNDERLINE",
        Converter::ArkValue<Ark_TextDecorationType>(ARK_TEXT_DECORATION_TYPE_UNDERLINE),
        "TextDecorationType.UNDERLINE" },
    { "ARK_TEXT_DECORATION_TYPE_OVERLINE",
        Converter::ArkValue<Ark_TextDecorationType>(ARK_TEXT_DECORATION_TYPE_OVERLINE), "TextDecorationType.OVERLINE" },
    { "ARK_TEXT_DECORATION_TYPE_LINE_THROUGH",
        Converter::ArkValue<Ark_TextDecorationType>(ARK_TEXT_DECORATION_TYPE_LINE_THROUGH),
        "TextDecorationType.LINE_THROUGH" },
};

// Valid values for attribute 'style' of method 'decoration'
static std::vector<std::tuple<std::string, Opt_TextDecorationStyle, std::string>> decorationStyleValidValues = {
    { "ARK_TEXT_DECORATION_STYLE_SOLID", Converter::ArkValue<Opt_TextDecorationStyle>(ARK_TEXT_DECORATION_STYLE_SOLID),
        "TextDecorationStyle.SOLID" },
    { "ARK_TEXT_DECORATION_STYLE_DOUBLE",
        Converter::ArkValue<Opt_TextDecorationStyle>(ARK_TEXT_DECORATION_STYLE_DOUBLE), "TextDecorationStyle.DOUBLE" },
    { "ARK_TEXT_DECORATION_STYLE_DOTTED",
        Converter::ArkValue<Opt_TextDecorationStyle>(ARK_TEXT_DECORATION_STYLE_DOTTED), "TextDecorationStyle.DOTTED" },
    { "ARK_TEXT_DECORATION_STYLE_DASHED",
        Converter::ArkValue<Opt_TextDecorationStyle>(ARK_TEXT_DECORATION_STYLE_DASHED), "TextDecorationStyle.DASHED" },
    { "ARK_TEXT_DECORATION_STYLE_WAVY", Converter::ArkValue<Opt_TextDecorationStyle>(ARK_TEXT_DECORATION_STYLE_WAVY),
        "TextDecorationStyle.WAVY" },
};

// Invalid values for attribute 'style' of method 'decoration'
static std::vector<std::tuple<std::string, Opt_TextDecorationStyle>> decorationStyleInvalidValues = {
    { "Ark_Empty()", Converter::ArkValue<Opt_TextDecorationStyle>(Ark_Empty()) },
    { "static_cast<Ark_TextDecorationStyle>(-1)",
        Converter::ArkValue<Opt_TextDecorationStyle>(static_cast<Ark_TextDecorationStyle>(-1)) },
};

/*
 * @tc.name: setPasswordRulesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setPasswordRulesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_RULES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_RULES_DEFAULT_VALUE);
}

// Valid values for attribute 'passwordRules' of method 'passwordRules'
static std::vector<std::tuple<std::string, Ark_String, std::string>> passwordRulesPasswordRulesValidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>(""), "" },
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc" },
};

/*
 * @tc.name: setPasswordRulesTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setPasswordRulesTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_String inputValuePasswordRules;
    Ark_String initValuePasswordRules;

    // Initial setup
    initValuePasswordRules = std::get<1>(passwordRulesPasswordRulesValidValues[0]);

    // Verifying attribute's  values
    inputValuePasswordRules = initValuePasswordRules;
    for (auto&& value : passwordRulesPasswordRulesValidValues) {
        inputValuePasswordRules = std::get<1>(value);
        modifier_->setPasswordRules(node_, &inputValuePasswordRules);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_RULES_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontFeatureTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFeatureTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE);
}

// Valid values for attribute 'fontFeature' of method 'fontFeature'
static std::vector<std::tuple<std::string, Ark_String, std::string>> fontFeatureFontFeatureValidValues = {
    { "\"\"", Converter::ArkValue<Ark_String>(""), "" },
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc" },
};

/*
 * @tc.name: setFontFeatureTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFeatureTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_String inputValueFontFeature;
    Ark_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = std::get<1>(fontFeatureFontFeatureValidValues[0]);

    // Verifying attribute's  values
    inputValueFontFeature = initValueFontFeature;
    for (auto&& value : fontFeatureFontFeatureValidValues) {
        inputValueFontFeature = std::get<1>(value);
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setShowPasswordTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_VISIBLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_PASSWORD_VISIBLE_DEFAULT_VALUE);
}

// Valid values for attribute 'showPasswordVisible' of method 'showPassword'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> showPasswordShowPasswordVisibleValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

/*
 * @tc.name: setShowPasswordTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueShowPasswordVisible;
    Ark_Boolean initValueShowPasswordVisible;

    // Initial setup
    initValueShowPasswordVisible = std::get<1>(showPasswordShowPasswordVisibleValidValues[0]);

    // Verifying attribute's  values
    inputValueShowPasswordVisible = initValueShowPasswordVisible;
    for (auto&& value : showPasswordShowPasswordVisibleValidValues) {
        inputValueShowPasswordVisible = std::get<1>(value);
        modifier_->setShowPassword(node_, inputValueShowPasswordVisible);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_VISIBLE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setEditMenuOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setEditMenuOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EDIT_MENU_OPTIONS_EDIT_MENU_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EDIT_MENU_OPTIONS_EDIT_MENU_DEFAULT_VALUE);
}

// Valid values for attribute 'editMenuOptionsEditMenu' of method 'editMenuOptions'
static std::vector<std::tuple<std::string, Ark_Materialized, std::string>>
    editMenuOptionsEditMenuOptionsEditMenuValidValues = {};

/*
 * @tc.name: setEditMenuOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setEditMenuOptionsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Materialized inputValueEditMenuOptionsEditMenu;
    Ark_Materialized initValueEditMenuOptionsEditMenu;

    // Initial setup
    initValueEditMenuOptionsEditMenu = std::get<1>(editMenuOptionsEditMenuOptionsEditMenuValidValues[0]);

    // Verifying attribute's  values
    inputValueEditMenuOptionsEditMenu = initValueEditMenuOptionsEditMenu;
    for (auto&& value : editMenuOptionsEditMenuOptionsEditMenuValidValues) {
        inputValueEditMenuOptionsEditMenu = std::get<1>(value);
        modifier_->setEditMenuOptions(node_, &inputValueEditMenuOptionsEditMenu);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EDIT_MENU_OPTIONS_EDIT_MENU_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setEditMenuOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setEditMenuOptionsTestInvalidValues, TestSize.Level1)
{
    // std::unique_ptr<JsonValue> jsonValue;
    // std::string resultStr;
    // std::string expectedStr;
    // Ark_Materialized inputValueEditMenuOptionsEditMenu;
    Ark_Materialized initValueEditMenuOptionsEditMenu;

    // Initial setup
    initValueEditMenuOptionsEditMenu = std::get<1>(editMenuOptionsEditMenuOptionsEditMenuValidValues[0]);
}

/*
 * @tc.name: setEnablePreviewTextTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnablePreviewTextTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_ENABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_PREVIEW_TEXT_ENABLE_DEFAULT_VALUE);
}

// Valid values for attribute 'enablePreviewTextEnable' of method 'enablePreviewText'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>>
    enablePreviewTextEnablePreviewTextEnableValidValues = {
        { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
        { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
    };

/*
 * @tc.name: setEnablePreviewTextTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnablePreviewTextTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueEnablePreviewTextEnable;
    Ark_Boolean initValueEnablePreviewTextEnable;

    // Initial setup
    initValueEnablePreviewTextEnable = std::get<1>(enablePreviewTextEnablePreviewTextEnableValidValues[0]);

    // Verifying attribute's  values
    inputValueEnablePreviewTextEnable = initValueEnablePreviewTextEnable;
    for (auto&& value : enablePreviewTextEnablePreviewTextEnableValidValues) {
        inputValueEnablePreviewTextEnable = std::get<1>(value);
        modifier_->setEnablePreviewText(node_, inputValueEnablePreviewTextEnable);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_ENABLE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_IS_ENABLED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_IS_ENABLED_DEFAULT_VALUE);
}

// Valid values for attribute 'enableHapticFeedbackIsEnabled' of method 'enableHapticFeedback'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>>
    enableHapticFeedbackEnableHapticFeedbackIsEnabledValidValues = {
        { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
        { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
    };

/*
 * @tc.name: setEnableHapticFeedbackTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableHapticFeedbackTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueEnableHapticFeedbackIsEnabled;
    Ark_Boolean initValueEnableHapticFeedbackIsEnabled;

    // Initial setup
    initValueEnableHapticFeedbackIsEnabled =
        std::get<1>(enableHapticFeedbackEnableHapticFeedbackIsEnabledValidValues[0]);

    // Verifying attribute's  values
    inputValueEnableHapticFeedbackIsEnabled = initValueEnableHapticFeedbackIsEnabled;
    for (auto&& value : enableHapticFeedbackEnableHapticFeedbackIsEnabledValidValues) {
        inputValueEnableHapticFeedbackIsEnabled = std::get<1>(value);
        modifier_->setEnableHapticFeedback(node_, inputValueEnableHapticFeedbackIsEnabled);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_IS_ENABLED_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
} // namespace OHOS::Ace::NG
