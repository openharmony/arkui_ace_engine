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

#include "text_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Text;
/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableHapticFeedback](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSelectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSelection =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_I_SELECTION_START_DEFAULT_VALUE) <<
        "Default value for attribute 'selection.selectionStart'";

    resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_END_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_I_SELECTION_END_DEFAULT_VALUE) <<
        "Default value for attribute 'selection.selectionEnd'";
}

/*
 * @tc.name: setSelectionTestSelectionSelectionStartValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTestSelectionSelectionStartValidValues, TestSize.Level1)
{
    Ark_Number initValueSelectionStart;
    Ark_Number initValueSelectionEnd;

    // Initial setup
    initValueSelectionStart = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSelectionEnd = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSelectionStart, &initValueSelectionEnd](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueSelectionStart = initValueSelectionStart;
        Ark_Number inputValueSelectionEnd = initValueSelectionEnd;

        inputValueSelectionStart = value;
        modifier_->setSelection(node_, &inputValueSelectionStart, &inputValueSelectionEnd);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelection = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_START_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelection, attribute: selection.selectionStart";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSelectionTestSelectionSelectionEndValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTestSelectionSelectionEndValidValues, TestSize.Level1)
{
    Ark_Number initValueSelectionStart;
    Ark_Number initValueSelectionEnd;

    // Initial setup
    initValueSelectionStart = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSelectionEnd = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSelectionStart, &initValueSelectionEnd](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueSelectionStart = initValueSelectionStart;
        Ark_Number inputValueSelectionEnd = initValueSelectionEnd;

        inputValueSelectionEnd = value;
        modifier_->setSelection(node_, &inputValueSelectionStart, &inputValueSelectionEnd);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelection = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_END_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelection, attribute: selection.selectionEnd";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
