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

#include "text_input_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::TextInput;
/*
 * @tc.name: setLineHeightTestLineHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineHeightTestLineHeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](
                          const std::string& input, const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueLineHeight = initValueLineHeight;

        modifier_->setLineHeight(node_, &inputValueLineHeight);
        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String_Resource>());
}

/*
 * @tc.name: setPasswordRulesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordRulesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_RULES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_RULES_DEFAULT_VALUE) << "Default value for attribute 'passwordRules'";
}

/*
 * @tc.name: setPasswordRulesTestPasswordRulesValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordRulesTestPasswordRulesValidValues, TestSize.Level1)
{
    Opt_String initValuePasswordRules;

    // Initial setup
    initValuePasswordRules = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValuePasswordRules](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValuePasswordRules = initValuePasswordRules;

        inputValuePasswordRules = value;
        modifier_->setPasswordRules(node_, &inputValuePasswordRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_RULES_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPasswordRules, attribute: passwordRules";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setPasswordRulesTestPasswordRulesInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordRulesTestPasswordRulesInvalidValues, TestSize.Level1)
{
    Opt_String initValuePasswordRules;

    // Initial setup
    initValuePasswordRules = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValuePasswordRules](const std::string& input, const Opt_String& value) {
        Opt_String inputValuePasswordRules = initValuePasswordRules;

        modifier_->setPasswordRules(node_, &inputValuePasswordRules);
        inputValuePasswordRules = value;
        modifier_->setPasswordRules(node_, &inputValuePasswordRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_RULES_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_RULES_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPasswordRules, attribute: passwordRules";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
}

/*
 * @tc.name: setFontFeatureTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontFeatureTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE) << "Default value for attribute 'fontFeature'";
}

/*
 * @tc.name: setFontFeatureTestFontFeatureValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontFeatureTestFontFeatureValidValues, TestSize.Level1)
{
    Opt_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureFontFeatureStrValidValues[0]));

    auto checkValue = [this, &initValueFontFeature](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValueFontFeature = initValueFontFeature;

        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFeatureStrValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setFontFeatureTestFontFeatureInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFeatureTestFontFeatureInvalidValues, TestSize.Level1)
{
    Opt_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureFontFeatureStrValidValues[0]));

    auto checkValue = [this, &initValueFontFeature](const std::string& input, const Opt_String& value) {
        Opt_String inputValueFontFeature = initValueFontFeature;

        modifier_->setFontFeature(node_, &inputValueFontFeature);
        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFeatureStrInvalidValues) {
        checkValue(input, ArkValue<Opt_String>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
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

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_PASSWORD_DEFAULT_VALUE) << "Default value for attribute 'showPassword'";
}

/*
 * @tc.name: setShowPasswordTestShowPasswordValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordTestShowPasswordValidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowPassword;

    // Initial setup
    initValueShowPassword = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowPassword](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowPassword = initValueShowPassword;

        inputValueShowPassword = value;
        modifier_->setShowPassword(node_, &inputValueShowPassword);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowPassword, attribute: showPassword";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowPasswordTestShowPasswordInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordTestShowPasswordInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowPassword;

    // Initial setup
    initValueShowPassword = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowPassword](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowPassword = initValueShowPassword;

        modifier_->setShowPassword(node_, &inputValueShowPassword);
        inputValueShowPassword = value;
        modifier_->setShowPassword(node_, &inputValueShowPassword);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_PASSWORD_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowPassword, attribute: showPassword";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
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

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_PREVIEW_TEXT_DEFAULT_VALUE) <<
        "Default value for attribute 'enablePreviewText'";
}

/*
 * @tc.name: setEnablePreviewTextTestEnablePreviewTextValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnablePreviewTextTestEnablePreviewTextValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnablePreviewText;

    // Initial setup
    initValueEnablePreviewText = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnablePreviewText](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnablePreviewText = initValueEnablePreviewText;

        inputValueEnablePreviewText = value;
        modifier_->setEnablePreviewText(node_, &inputValueEnablePreviewText);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnablePreviewText, attribute: enablePreviewText";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnablePreviewTextTestEnablePreviewTextInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnablePreviewTextTestEnablePreviewTextInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnablePreviewText;

    // Initial setup
    initValueEnablePreviewText = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnablePreviewText](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnablePreviewText = initValueEnablePreviewText;

        modifier_->setEnablePreviewText(node_, &inputValueEnablePreviewText);
        inputValueEnablePreviewText = value;
        modifier_->setEnablePreviewText(node_, &inputValueEnablePreviewText);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_PREVIEW_TEXT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnablePreviewText, attribute: enablePreviewText";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
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

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE) <<
        "Default value for attribute 'enableHapticFeedback'";
}

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
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

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableHapticFeedback](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setAutoCapitalizationModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setAutoCapitalizationModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'autoCapitalizationMode'";
}

/*
 * @tc.name: setAutoCapitalizationModeTestAutoCapitalizationModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextInputModifierTest, DISABLED_setAutoCapitalizationModeTestAutoCapitalizationModeValidValues, TestSize.Level1)
{
    Opt_AutoCapitalizationMode initValueAutoCapitalizationMode;

    // Initial setup
    initValueAutoCapitalizationMode = ArkValue<Opt_AutoCapitalizationMode>(
        std::get<1>(Fixtures::testFixtureEnumAutoCapitalizationModeValidValues[0]));

    auto checkValue = [this, &initValueAutoCapitalizationMode](const std::string& input, const std::string& expectedStr,
                          const Opt_AutoCapitalizationMode& value) {
        Opt_AutoCapitalizationMode inputValueAutoCapitalizationMode = initValueAutoCapitalizationMode;

        inputValueAutoCapitalizationMode = value;
        modifier_->setAutoCapitalizationMode(node_, &inputValueAutoCapitalizationMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAutoCapitalizationMode, attribute: autoCapitalizationMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumAutoCapitalizationModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_AutoCapitalizationMode>(value));
    }
}

/*
 * @tc.name: setAutoCapitalizationModeTestAutoCapitalizationModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextInputModifierTest, DISABLED_setAutoCapitalizationModeTestAutoCapitalizationModeInvalidValues, TestSize.Level1)
{
    Opt_AutoCapitalizationMode initValueAutoCapitalizationMode;

    // Initial setup
    initValueAutoCapitalizationMode = ArkValue<Opt_AutoCapitalizationMode>(
        std::get<1>(Fixtures::testFixtureEnumAutoCapitalizationModeValidValues[0]));

    auto checkValue = [this, &initValueAutoCapitalizationMode](
                          const std::string& input, const Opt_AutoCapitalizationMode& value) {
        Opt_AutoCapitalizationMode inputValueAutoCapitalizationMode = initValueAutoCapitalizationMode;

        modifier_->setAutoCapitalizationMode(node_, &inputValueAutoCapitalizationMode);
        inputValueAutoCapitalizationMode = value;
        modifier_->setAutoCapitalizationMode(node_, &inputValueAutoCapitalizationMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAutoCapitalizationMode, attribute: autoCapitalizationMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumAutoCapitalizationModeInvalidValues) {
        checkValue(input, ArkValue<Opt_AutoCapitalizationMode>(value));
    }
}

/*
 * @tc.name: setHalfLeadingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHalfLeadingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HALF_LEADING_DEFAULT_VALUE) << "Default value for attribute 'halfLeading'";
}

/*
 * @tc.name: setHalfLeadingTestHalfLeadingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHalfLeadingTestHalfLeadingValidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;

    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueHalfLeading](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        inputValueHalfLeading = value;
        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHalfLeading, attribute: halfLeading";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setHalfLeadingTestHalfLeadingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHalfLeadingTestHalfLeadingInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;

    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueHalfLeading](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        inputValueHalfLeading = value;
        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_HALF_LEADING_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setHalfLeading, attribute: halfLeading";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEllipsisModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEllipsisModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE) << "Default value for attribute 'ellipsisMode'";
}

/*
 * @tc.name: setEllipsisModeTestEllipsisModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEllipsisModeTestEllipsisModeValidValues, TestSize.Level1)
{
    Opt_EllipsisMode initValueEllipsisMode;

    // Initial setup
    initValueEllipsisMode =
        ArkValue<Opt_EllipsisMode>(std::get<1>(Fixtures::testFixtureEnumEllipsisModeValidValues[0]));

    auto checkValue = [this, &initValueEllipsisMode](
                          const std::string& input, const std::string& expectedStr, const Opt_EllipsisMode& value) {
        Opt_EllipsisMode inputValueEllipsisMode = initValueEllipsisMode;

        inputValueEllipsisMode = value;
        modifier_->setEllipsisMode(node_, &inputValueEllipsisMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEllipsisMode, attribute: ellipsisMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumEllipsisModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_EllipsisMode>(value));
    }
}

/*
 * @tc.name: setEllipsisModeTestEllipsisModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEllipsisModeTestEllipsisModeInvalidValues, TestSize.Level1)
{
    Opt_EllipsisMode initValueEllipsisMode;

    // Initial setup
    initValueEllipsisMode =
        ArkValue<Opt_EllipsisMode>(std::get<1>(Fixtures::testFixtureEnumEllipsisModeValidValues[0]));

    auto checkValue = [this, &initValueEllipsisMode](const std::string& input, const Opt_EllipsisMode& value) {
        Opt_EllipsisMode inputValueEllipsisMode = initValueEllipsisMode;

        modifier_->setEllipsisMode(node_, &inputValueEllipsisMode);
        inputValueEllipsisMode = value;
        modifier_->setEllipsisMode(node_, &inputValueEllipsisMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEllipsisMode, attribute: ellipsisMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumEllipsisModeInvalidValues) {
        checkValue(input, ArkValue<Opt_EllipsisMode>(value));
    }
}

/*
 * @tc.name: setStopBackPressTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setStopBackPressTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STOP_BACK_PRESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STOP_BACK_PRESS_DEFAULT_VALUE) << "Default value for attribute 'stopBackPress'";
}

/*
 * @tc.name: setStopBackPressTestStopBackPressValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setStopBackPressTestStopBackPressValidValues, TestSize.Level1)
{
    Opt_Boolean initValueStopBackPress;

    // Initial setup
    initValueStopBackPress = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStopBackPress](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueStopBackPress = initValueStopBackPress;

        inputValueStopBackPress = value;
        modifier_->setStopBackPress(node_, &inputValueStopBackPress);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STOP_BACK_PRESS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStopBackPress, attribute: stopBackPress";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setStopBackPressTestStopBackPressInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setStopBackPressTestStopBackPressInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueStopBackPress;

    // Initial setup
    initValueStopBackPress = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStopBackPress](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueStopBackPress = initValueStopBackPress;

        modifier_->setStopBackPress(node_, &inputValueStopBackPress);
        inputValueStopBackPress = value;
        modifier_->setStopBackPress(node_, &inputValueStopBackPress);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STOP_BACK_PRESS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STOP_BACK_PRESS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStopBackPress, attribute: stopBackPress";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setKeyboardAppearanceTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setKeyboardAppearanceTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE) <<
        "Default value for attribute 'keyboardAppearance'";
}

/*
 * @tc.name: setKeyboardAppearanceTestKeyboardAppearanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setKeyboardAppearanceTestKeyboardAppearanceValidValues, TestSize.Level1)
{
    Opt_KeyboardAppearance initValueKeyboardAppearance;

    // Initial setup
    initValueKeyboardAppearance =
        ArkValue<Opt_KeyboardAppearance>(std::get<1>(Fixtures::testFixtureEnumKeyboardAppearanceValidValues[0]));

    auto checkValue = [this, &initValueKeyboardAppearance](const std::string& input, const std::string& expectedStr,
                          const Opt_KeyboardAppearance& value) {
        Opt_KeyboardAppearance inputValueKeyboardAppearance = initValueKeyboardAppearance;

        inputValueKeyboardAppearance = value;
        modifier_->setKeyboardAppearance(node_, &inputValueKeyboardAppearance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setKeyboardAppearance, attribute: keyboardAppearance";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumKeyboardAppearanceValidValues) {
        checkValue(input, expected, ArkValue<Opt_KeyboardAppearance>(value));
    }
}

/*
 * @tc.name: setKeyboardAppearanceTestKeyboardAppearanceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setKeyboardAppearanceTestKeyboardAppearanceInvalidValues, TestSize.Level1)
{
    Opt_KeyboardAppearance initValueKeyboardAppearance;

    // Initial setup
    initValueKeyboardAppearance =
        ArkValue<Opt_KeyboardAppearance>(std::get<1>(Fixtures::testFixtureEnumKeyboardAppearanceValidValues[0]));

    auto checkValue = [this, &initValueKeyboardAppearance](
                          const std::string& input, const Opt_KeyboardAppearance& value) {
        Opt_KeyboardAppearance inputValueKeyboardAppearance = initValueKeyboardAppearance;

        modifier_->setKeyboardAppearance(node_, &inputValueKeyboardAppearance);
        inputValueKeyboardAppearance = value;
        modifier_->setKeyboardAppearance(node_, &inputValueKeyboardAppearance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setKeyboardAppearance, attribute: keyboardAppearance";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumKeyboardAppearanceInvalidValues) {
        checkValue(input, ArkValue<Opt_KeyboardAppearance>(value));
    }
}

/*
 * @tc.name: setShowCounterTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowCounterTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultShowCounter =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_VALUE_DEFAULT_VALUE) <<
        "Default value for attribute 'showCounter.value'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_DEFAULT_VALUE) <<
        "Default value for attribute 'showCounter.options.thresholdPercentage'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_DEFAULT_VALUE) <<
        "Default value for attribute 'showCounter.options.highlightBorder'";
}

/*
 * @tc.name: setShowCounterTestShowCounterValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowCounterTestShowCounterValueValidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        inputValueValue = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowCounter, attribute: showCounter.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setShowCounterTestShowCounterValueInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        inputValueValue = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowCounter, attribute: showCounter.value";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsThresholdPercentageValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowCounterTestShowCounterOptionsThresholdPercentageValidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).thresholdPercentage = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.thresholdPercentage";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPercentageThresholdFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsThresholdPercentageInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowCounterTestShowCounterOptionsThresholdPercentageInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        WriteTo(inputValueOptions).thresholdPercentage = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.thresholdPercentage";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPercentageThresholdFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsHighlightBorderValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowCounterTestShowCounterOptionsHighlightBorderValidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).highlightBorder = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setShowCounter, attribute: showCounter.options.highlightBorder";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsHighlightBorderInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowCounterTestShowCounterOptionsHighlightBorderInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        WriteTo(inputValueOptions).highlightBorder = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.highlightBorder";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
