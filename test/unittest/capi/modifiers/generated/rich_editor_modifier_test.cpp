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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME = "dataDetectorConfig";
const auto ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_NAME = "decoration";
const auto ATTRIBUTE_PLACEHOLDER_NAME = "placeholder";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME = "style";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME = "font";
const auto ATTRIBUTE_COPY_OPTIONS_NAME = "copyOptions";
const auto ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE = "!NOT-DEFINED!";
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
const auto ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME = "enableKeyboardOnFocus";
const auto ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_BAR_STATE_NAME = "barState";
const auto ATTRIBUTE_BAR_STATE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_LENGTH_NAME = "maxLength";
const auto ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MAX_LINES_NAME = "maxLines";
const auto ATTRIBUTE_MAX_LINES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_KEYBOARD_APPEARANCE_NAME = "keyboardAppearance";
const auto ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STOP_BACK_PRESS_NAME = "stopBackPress";
const auto ATTRIBUTE_STOP_BACK_PRESS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PLACEHOLDER_I_VALUE_NAME = "value";
const auto ATTRIBUTE_PLACEHOLDER_I_VALUE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class RichEditorModifierTest : public ModifierTestBase<GENERATED_ArkUIRichEditorModifier,
                                   &GENERATED_ArkUINodeModifiers::getRichEditorModifier, GENERATED_ARKUI_RICH_EDITOR> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<RichEditorTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setCopyOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setCopyOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE) << "Default value for attribute 'copyOptions'";
}

/*
 * @tc.name: setCopyOptionsTestCopyOptionsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setCopyOptionsTestCopyOptionsValidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOptions;

    // Initial setup
    initValueCopyOptions = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]));

    auto checkValue = [this, &initValueCopyOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_CopyOptions& value) {
        Opt_CopyOptions inputValueCopyOptions = initValueCopyOptions;

        inputValueCopyOptions = value;
        modifier_->setCopyOptions(node_, &inputValueCopyOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, expected, ArkValue<Opt_CopyOptions>(value));
    }
}

/*
 * @tc.name: setCopyOptionsTestCopyOptionsInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setCopyOptionsTestCopyOptionsInvalidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOptions;

    // Initial setup
    initValueCopyOptions = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]));

    auto checkValue = [this, &initValueCopyOptions](const std::string& input, const Opt_CopyOptions& value) {
        Opt_CopyOptions inputValueCopyOptions = initValueCopyOptions;

        modifier_->setCopyOptions(node_, &inputValueCopyOptions);
        inputValueCopyOptions = value;
        modifier_->setCopyOptions(node_, &inputValueCopyOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, ArkValue<Opt_CopyOptions>(value));
    }
}

/*
 * @tc.name: setEnableDataDetectorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableDataDetectorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_DATA_DETECTOR_DEFAULT_VALUE) <<
        "Default value for attribute 'enableDataDetector'";
}

/*
 * @tc.name: setEnableDataDetectorTestEnableDataDetectorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableDataDetectorTestEnableDataDetectorValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableDataDetector;

    // Initial setup
    initValueEnableDataDetector = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableDataDetector](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableDataDetector = initValueEnableDataDetector;

        inputValueEnableDataDetector = value;
        modifier_->setEnableDataDetector(node_, &inputValueEnableDataDetector);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableDataDetector, attribute: enableDataDetector";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableDataDetectorTestEnableDataDetectorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setEnableDataDetectorTestEnableDataDetectorInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableDataDetector;

    // Initial setup
    initValueEnableDataDetector = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableDataDetector](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableDataDetector = initValueEnableDataDetector;

        modifier_->setEnableDataDetector(node_, &inputValueEnableDataDetector);
        inputValueEnableDataDetector = value;
        modifier_->setEnableDataDetector(node_, &inputValueEnableDataDetector);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_DATA_DETECTOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableDataDetector, attribute: enableDataDetector";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEnablePreviewTextTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setEnablePreviewTextTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setDataDetectorConfigTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setDataDetectorConfigTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDataDetectorConfig =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME);
    std::unique_ptr<JsonValue> resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(
        resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.types'";

    resultStr = GetAttrValue<std::string>(resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.decoration.type'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.decoration.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.decoration.style'";
}

/*
 * @tc.name: setDataDetectorConfigTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setDataDetectorConfigTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setCaretColorTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setCaretColorTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setSelectedBackgroundColorTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setSelectedBackgroundColorTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setEnterKeyTypeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setEnterKeyTypeTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setEnableKeyboardOnFocusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableKeyboardOnFocusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE) <<
        "Default value for attribute 'enableKeyboardOnFocus'";
}

/*
 * @tc.name: setEnableKeyboardOnFocusTestEnableKeyboardOnFocusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableKeyboardOnFocusTestEnableKeyboardOnFocusValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableKeyboardOnFocus;

    // Initial setup
    initValueEnableKeyboardOnFocus = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableKeyboardOnFocus](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableKeyboardOnFocus = initValueEnableKeyboardOnFocus;

        inputValueEnableKeyboardOnFocus = value;
        modifier_->setEnableKeyboardOnFocus(node_, &inputValueEnableKeyboardOnFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableKeyboardOnFocus, attribute: enableKeyboardOnFocus";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableKeyboardOnFocusTestEnableKeyboardOnFocusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableKeyboardOnFocusTestEnableKeyboardOnFocusInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableKeyboardOnFocus;

    // Initial setup
    initValueEnableKeyboardOnFocus = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableKeyboardOnFocus](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableKeyboardOnFocus = initValueEnableKeyboardOnFocus;

        modifier_->setEnableKeyboardOnFocus(node_, &inputValueEnableKeyboardOnFocus);
        inputValueEnableKeyboardOnFocus = value;
        modifier_->setEnableKeyboardOnFocus(node_, &inputValueEnableKeyboardOnFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_KEYBOARD_ON_FOCUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableKeyboardOnFocus, attribute: enableKeyboardOnFocus";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
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
HWTEST_F(RichEditorModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
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
HWTEST_F(RichEditorModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues, TestSize.Level1)
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
 * @tc.name: setBarStateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setBarStateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE) << "Default value for attribute 'barState'";
}

/*
 * @tc.name: setBarStateTestBarStateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setBarStateTestBarStateValidValues, TestSize.Level1)
{
    Opt_BarState initValueBarState;

    // Initial setup
    initValueBarState = ArkValue<Opt_BarState>(std::get<1>(Fixtures::testFixtureEnumBarStateValidValues[0]));

    auto checkValue = [this, &initValueBarState](
                          const std::string& input, const std::string& expectedStr, const Opt_BarState& value) {
        Opt_BarState inputValueBarState = initValueBarState;

        inputValueBarState = value;
        modifier_->setBarState(node_, &inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumBarStateValidValues) {
        checkValue(input, expected, ArkValue<Opt_BarState>(value));
    }
}

/*
 * @tc.name: setBarStateTestBarStateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setBarStateTestBarStateInvalidValues, TestSize.Level1)
{
    Opt_BarState initValueBarState;

    // Initial setup
    initValueBarState = ArkValue<Opt_BarState>(std::get<1>(Fixtures::testFixtureEnumBarStateValidValues[0]));

    auto checkValue = [this, &initValueBarState](const std::string& input, const Opt_BarState& value) {
        Opt_BarState inputValueBarState = initValueBarState;

        modifier_->setBarState(node_, &inputValueBarState);
        inputValueBarState = value;
        modifier_->setBarState(node_, &inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumBarStateInvalidValues) {
        checkValue(input, ArkValue<Opt_BarState>(value));
    }
}

/*
 * @tc.name: setMaxLengthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setMaxLengthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE) << "Default value for attribute 'maxLength'";
}

/*
 * @tc.name: setMaxLengthTestMaxLengthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setMaxLengthTestMaxLengthValidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLength;

    // Initial setup
    initValueMaxLength = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMaxLength](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueMaxLength = initValueMaxLength;

        inputValueMaxLength = value;
        modifier_->setMaxLength(node_, &inputValueMaxLength);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLength, attribute: maxLength";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMaxLengthTestMaxLengthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setMaxLengthTestMaxLengthInvalidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLength;

    // Initial setup
    initValueMaxLength = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMaxLength](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueMaxLength = initValueMaxLength;

        modifier_->setMaxLength(node_, &inputValueMaxLength);
        inputValueMaxLength = value;
        modifier_->setMaxLength(node_, &inputValueMaxLength);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxLength, attribute: maxLength";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setMaxLinesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) << "Default value for attribute 'maxLines'";
}

/*
 * @tc.name: setMaxLinesTestMaxLinesValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setMaxLinesTestMaxLinesValidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMaxLines](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueMaxLines = initValueMaxLines;

        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMaxLinesTestMaxLinesInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setMaxLinesTestMaxLinesInvalidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueMaxLines](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueMaxLines = initValueMaxLines;

        modifier_->setMaxLines(node_, &inputValueMaxLines);
        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setKeyboardAppearanceTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setKeyboardAppearanceTestDefaultValues, TestSize.Level1)
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
HWTEST_F(RichEditorModifierTest, DISABLED_setKeyboardAppearanceTestKeyboardAppearanceValidValues, TestSize.Level1)
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
HWTEST_F(RichEditorModifierTest, DISABLED_setKeyboardAppearanceTestKeyboardAppearanceInvalidValues, TestSize.Level1)
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
 * @tc.name: setStopBackPressTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setStopBackPressTestDefaultValues, TestSize.Level1)
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
HWTEST_F(RichEditorModifierTest, DISABLED_setStopBackPressTestStopBackPressValidValues, TestSize.Level1)
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
HWTEST_F(RichEditorModifierTest, DISABLED_setStopBackPressTestStopBackPressInvalidValues, TestSize.Level1)
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
 * @tc.name: setPlaceholderTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPlaceholder =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
    std::unique_ptr<JsonValue> resultStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
    std::unique_ptr<JsonValue> resultFont =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_VALUE_DEFAULT_VALUE) <<
        "Default value for attribute 'placeholder.value'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'placeholder.style.font.size'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'placeholder.style.font.weight'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE) <<
        "Default value for attribute 'placeholder.style.font.family'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'placeholder.style.font.style'";

    resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'placeholder.style.fontColor'";
}

/*
 * @tc.name: setPlaceholderTestPlaceholderValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderValueValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        inputValueValue = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_VALUE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setPlaceholderTestPlaceholderValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderValueInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](const std::string& input, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        inputValueValue = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_VALUE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.value";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontSizeValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        WriteTo(WriteTo(inputValueStyle).font).size = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontSizeInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](const std::string& input, const Opt_Length& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        WriteTo(WriteTo(inputValueStyle).font).size = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontWeightValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_Number_String& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        WriteTo(WriteTo(inputValueStyle).font).weight = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontWeightInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        WriteTo(WriteTo(inputValueStyle).font).weight = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_Number_String>());
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontFamilyValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        WriteTo(WriteTo(inputValueStyle).font).family = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        WriteTo(WriteTo(inputValueStyle).font).family = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.family";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontStyleValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        WriteTo(WriteTo(inputValueStyle).font).style = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontStyleInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](const std::string& input, const Opt_FontStyle& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        WriteTo(WriteTo(inputValueStyle).font).style = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setPlaceholderTestPlaceholderStyleFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        WriteTo(inputValueStyle).fontColor = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.fontColor";
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
 * @tc.name: setPlaceholderTestPlaceholderStyleFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierTest, DISABLED_setPlaceholderTestPlaceholderStyleFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueValue;
    Opt_PlaceholderStyle initValueStyle;

    // Initial setup
    initValueValue = ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteTo(initValueStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueStyle).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueStyle](
                          const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceStr inputValueValue = initValueValue;
        Opt_PlaceholderStyle inputValueStyle = initValueStyle;

        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        WriteTo(inputValueStyle).fontColor = value;
        modifier_->setPlaceholder(node_, &inputValueValue, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholder = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        auto resultStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPlaceholder, ATTRIBUTE_PLACEHOLDER_I_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_I_STYLE_I_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholder, attribute: placeholder.style.fontColor";
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
} // namespace OHOS::Ace::NG
