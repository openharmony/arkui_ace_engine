/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"

#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_configuration.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_proxy.h"
#include "core/common/ime/text_input_type.h"
#include "frameworks/bridge/common/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const std::string TYPE_TEST = "type";
const std::string OBSCURE_TEXT_TEST = "obscureText";
const std::string ACTION_TEST = "action";
const std::string AUTO_CORRECT_TEST = "autoCorrect";
const std::string ACTION_LABEL_TEST = "actionLabel";
const std::string CAPITALIZATION_TEST = "capitalization";
const std::string KEYBOARD_APPEARANCE_TEST = "keyboardAppearance";
const std::string STR_ACTION_LABEL_TEST = "test_actionLabel";
const std::string STR_CAPITALIZATION_TEST = "test_capitalization";
const std::string STR_KEYBOARD_APPEARANCE_TEST = "test_keyboardAppearance";
const std::string TEXT_TEST_VALUE = "text_test_value";
const std::string HINT_TEST_VALUE = "hint_test_value";
const std::string WIDE_TEXT_TEST = "text_ttext_test_valueest_value";
constexpr int32_t LESS_THAN_TEXT_LENGTH = 6;
constexpr int32_t GREATER_THAN_TEXT_LENGTH = 20;
constexpr int32_t WIDE_TEXT_TEST_LENGTH = 30;
constexpr int32_t BEFOR_SELECTION_TEST_LENGTH = 12;
} // namespace

class ImeTest : public testing::Test {};

/**
 * @tc.name: CastToTextInputTypeTest001
 * @tc.desc: Test cast to text input type.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, CastToTextInputTypeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Value is greater than BEGIN and less than END.
     * @tc.expected: step1. The return value is the set value.
     */
    EXPECT_EQ(CastToTextInputType(1), TextInputType::MULTILINE);
    /**
     * @tc.steps: step2. Value is less than BEGIN.
     * @tc.expected: step2. The return value is set to TEXT.
     */
    EXPECT_EQ(CastToTextInputType(-2), TextInputType::TEXT);
    /**
     * @tc.steps: step3. Value is greater than END.
     * @tc.expected: step3. The return value is set to TEXT.
     */
    EXPECT_EQ(CastToTextInputType(static_cast<int32_t>(TextInputType::END) + 1), TextInputType::TEXT);
    /**
     * @tc.steps: step4. Value is set to zero.
     * @tc.expected: step4. The return value is set to TEXT.
     */
    EXPECT_EQ(CastToTextInputType(0), TextInputType::TEXT);
}

/**
 * @tc.name: CastToTextInputActionTest001
 * @tc.desc: Test convert to Text Input Operation.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, CastToTextInputActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Value is greater than BEGIN and less than END.
     * @tc.expected: step1. The return value is the set value.
     */
    EXPECT_EQ(CastToTextInputAction(1), TextInputAction::NONE);
    /**
     * @tc.steps: step2. Value is less than BEGIN.
     * @tc.expected: step2. The return value is set to UNSPECIFIED.
     */
    EXPECT_EQ(CastToTextInputAction(-2), TextInputAction::UNSPECIFIED);
    /**
     * @tc.steps: step3. Value is greater than END.
     * @tc.expected: step3. The return value is set to UNSPECIFIED.
     */
    EXPECT_EQ(CastToTextInputAction(10), TextInputAction::UNSPECIFIED);
    /**
     * @tc.steps: step4. Value is set to zero.
     * @tc.expected: step4. The return value is set to BEGIN.
     */
    EXPECT_EQ(CastToTextInputAction(0), TextInputAction::BEGIN);
}

/**
 * @tc.name: ToJsonStringTest001
 * @tc.desc: Test to json string.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, ToJsonStringTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize object, use default data.
     * @tc.expected: step1. Json data is set as default.
     */
    TextInputConfiguration textInputConfiguration;
    auto jsonString = textInputConfiguration.ToJsonString();
    auto json = JsonUtil::ParseJsonString(jsonString);
    EXPECT_EQ(json->GetValue(TYPE_TEST)->GetInt(), static_cast<int32_t>(TextInputType::TEXT));
    EXPECT_EQ(json->GetValue(OBSCURE_TEXT_TEST)->GetBool(), false);
    EXPECT_EQ(json->GetValue(ACTION_TEST)->GetInt(), static_cast<int32_t>(TextInputAction::UNSPECIFIED));
    EXPECT_EQ(json->GetValue(AUTO_CORRECT_TEST)->GetBool(), false);
}

/**
 * @tc.name: ToJsonStringTest002
 * @tc.desc: Test actionLabel,capitalization and keyboardAppearance not empty.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, ToJsonStringTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. The initialization object, actionLabel, capitalization and keyboardAppearance,
     * is set to a non empty string.
     * @tc.expected: step1. Json is written to the set value.
     */
    TextInputConfiguration textInputConfiguration;
    textInputConfiguration.actionLabel = STR_ACTION_LABEL_TEST;
    textInputConfiguration.capitalization = STR_CAPITALIZATION_TEST;
    textInputConfiguration.keyboardAppearance = STR_KEYBOARD_APPEARANCE_TEST;

    auto jsonString = textInputConfiguration.ToJsonString();
    auto json = JsonUtil::ParseJsonString(jsonString);
    EXPECT_EQ(json->GetValue(ACTION_LABEL_TEST)->GetString(), STR_ACTION_LABEL_TEST);
    EXPECT_EQ(json->GetValue(CAPITALIZATION_TEST)->GetString(), STR_CAPITALIZATION_TEST);
    EXPECT_EQ(json->GetValue(KEYBOARD_APPEARANCE_TEST)->GetString(), STR_KEYBOARD_APPEARANCE_TEST);
}

/**
 * @tc.name: TextEditingValueTest001
 * @tc.desc: Test whether two textEditingValues are equal of operator.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, TextEditingValueTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize variable.
     */
    TextEditingValue textEditingValue;
    TextEditingValue textEditingValueOther;
    textEditingValue.selection.baseOffset = 10;

    /**
     * @tc.steps: step2. Initialize the property of textEditingValue.
     * @tc.expected: step2. TextEditingValue is not equal to textEditingValueOther.
     */
    EXPECT_FALSE(textEditingValue == textEditingValueOther);
    EXPECT_TRUE(textEditingValue != textEditingValueOther);

    /**
     * @tc.steps: step3. Initialize the property of textEditingValue to make baseOffset
     * equal to the baseOffset of textEditingValue.
     * @tc.expected: step3. TextEditingValue is equal to textEditingValueOther.
     */
    textEditingValueOther.selection.baseOffset = 10;
    EXPECT_TRUE(textEditingValue == textEditingValueOther);
    EXPECT_FALSE(textEditingValue != textEditingValueOther);
}

/**
 * @tc.name: MoveLeftTest001
 * @tc.desc: Test an invalid extentOffset of MoveLeft.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveLeftTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Use the default extentOffset value.
     * @tc.expected: step1. ExtentOffset and baseOffset are both set to zero.
     */
    TextEditingValue textEditingValue;
    textEditingValue.MoveLeft();
    EXPECT_EQ(textEditingValue.selection.baseOffset, 0);
    EXPECT_EQ(textEditingValue.selection.extentOffset, 0);
}

/**
 * @tc.name: MoveLeftTest002
 * @tc.desc: Test extentOffset is longer than the text of MoveLeft.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveLeftTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set the value of extentOffset, and the extentOffset is greater than the length of text.
     * @tc.expected: step1. ExtentOffset and baseOffset are both set to the length of text.
     */
    TextEditingValue textEditingValue;
    textEditingValue.selection.extentOffset = GREATER_THAN_TEXT_LENGTH;
    textEditingValue.text = "text_test";
    textEditingValue.MoveLeft();
    EXPECT_EQ(textEditingValue.selection.baseOffset, textEditingValue.text.length());
    EXPECT_EQ(textEditingValue.selection.extentOffset, textEditingValue.text.length());
}

/**
 * @tc.name: MoveLeftTest003
 * @tc.desc: Test that the length of extentOffset is less than the length of text of MoveLeft.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveLeftTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the value of extentOffset so that it is less than the length of text.
     * @tc.expected: step1. ExtentOffset and baseOffset are set to ExtentOffset minus one.
     */
    TextEditingValue textEditingValue;
    textEditingValue.selection.extentOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.MoveLeft();
    EXPECT_EQ(textEditingValue.selection.baseOffset, LESS_THAN_TEXT_LENGTH - 1);
    EXPECT_EQ(textEditingValue.selection.extentOffset, LESS_THAN_TEXT_LENGTH - 1);
}

/**
 * @tc.name: MoveRightTest001
 * @tc.desc: Test an invalid extentOffset of MoveRight.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveRightTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When the member text of the selection is empty.
     * @tc.expected: step1. Calling the MoveRight method, both ExtentOffset and baseOffset are negative ones.
     */
    TextEditingValue textEditingValue;
    textEditingValue.MoveRight();
    EXPECT_EQ(textEditingValue.selection.baseOffset, -1);
    EXPECT_EQ(textEditingValue.selection.extentOffset, -1);

    /**
     * @tc.steps: step2. When the length of the member text variable of TextEditingValue is greater than 0.
     * @tc.expected: step2. ExtentOffset and baseOffset are both is textEditingValue.text.length().
     */
    textEditingValue.text = "textEditingValue";
    textEditingValue.MoveRight();
    EXPECT_EQ(textEditingValue.selection.baseOffset, textEditingValue.text.length());
    EXPECT_EQ(textEditingValue.selection.extentOffset, textEditingValue.text.length());

    /**
     * @tc.steps: step3. When the length of the member text variable of TextEditingValue is greater than 0.
     *                  and textEditingValue.selection.baseOffset greater than length of text.
     * @tc.expected: step3. ExtentOffset and baseOffset are both is textEditingValue.text.length().
     */
    textEditingValue.text = "textEdit";
    textEditingValue.MoveRight();
    EXPECT_EQ(textEditingValue.selection.baseOffset, textEditingValue.text.length());
    EXPECT_EQ(textEditingValue.selection.extentOffset, textEditingValue.text.length());
}

/**
 * @tc.name: MoveRightTest002
 * @tc.desc: Test extentOffset is longer than the text of MoveRight.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveRightTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set the value of extentOffset, and the extentOffset is greater than the length of text.
     * @tc.expected: step1. ExtentOffset and baseOffset are both set to the length of text.
     */
    TextEditingValue textEditingValue;
    textEditingValue.selection.extentOffset = GREATER_THAN_TEXT_LENGTH;
    textEditingValue.text = "text_test";
    textEditingValue.MoveRight();
    EXPECT_EQ(textEditingValue.selection.baseOffset, textEditingValue.text.length());
    EXPECT_EQ(textEditingValue.selection.extentOffset, textEditingValue.text.length());
}

/**
 * @tc.name: MoveRightTest003
 * @tc.desc: Test that the length of extentOffset is less than the length of text.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveRightTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the value of extentOffset so that it is less than the length of text.
     * @tc.expected: step1. ExtentOffset and baseOffset are set to LESS_ THAN_ TEXT_ LENGTH length plus one.
     */
    TextEditingValue textEditingValue;
    textEditingValue.selection.extentOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.MoveRight();
    EXPECT_EQ(textEditingValue.selection.baseOffset, LESS_THAN_TEXT_LENGTH + 1);
    EXPECT_EQ(textEditingValue.selection.extentOffset, LESS_THAN_TEXT_LENGTH + 1);
}

/**
 * @tc.name: MoveToPositionTest001
 * @tc.desc: Test invalid position of MoveToPosition.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveToPositionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set the value of position as invalid.
     * @tc.expected: step1. ExtentOffset and baseOffset are both set to zero.
     */
    TextEditingValue textEditingValue;
    textEditingValue.MoveToPosition(-1);
    EXPECT_EQ(textEditingValue.selection.baseOffset, 0);
    EXPECT_EQ(textEditingValue.selection.extentOffset, 0);
}

/**
 * @tc.name: MoveToPositionTest002
 * @tc.desc: Test a valid Position of MoveToPosition.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, MoveToPositionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the value of extentOffset so that it is less than the length of text.
     * @tc.expected: step1. ExtentOffset and baseOffset are set to the length of text.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.MoveToPosition(LESS_THAN_TEXT_LENGTH);
    EXPECT_EQ(textEditingValue.selection.baseOffset, LESS_THAN_TEXT_LENGTH);
    EXPECT_EQ(textEditingValue.selection.extentOffset, LESS_THAN_TEXT_LENGTH);

    textEditingValue.MoveToPosition(GREATER_THAN_TEXT_LENGTH);
    EXPECT_EQ(textEditingValue.selection.baseOffset, textEditingValue.text.length());
    EXPECT_EQ(textEditingValue.selection.extentOffset, textEditingValue.text.length());
}

/**
 * @tc.name: UpdateSelectionTest001
 * @tc.desc: Test an invalid start of UpdateSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, UpdateSelectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set start as invalid value and end as zero.
     * @tc.expected: step1. ExtentOffset and baseOffset are both set to zero.
     */
    TextEditingValue textEditingValue;
    textEditingValue.UpdateSelection(-1, 0);
    EXPECT_EQ(textEditingValue.selection.baseOffset, 0);
    EXPECT_EQ(textEditingValue.selection.extentOffset, 0);
}

/**
 * @tc.name: UpdateSelectionTest002
 * @tc.desc: Test end length is greater than text length of UpdateSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, UpdateSelectionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set start as a valid value, and the end value is greater than the length of text.
     * @tc.expected: step1. ExtentOffset is set to the length of text.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.UpdateSelection(LESS_THAN_TEXT_LENGTH, GREATER_THAN_TEXT_LENGTH);
    EXPECT_EQ(textEditingValue.selection.baseOffset, LESS_THAN_TEXT_LENGTH);
    EXPECT_EQ(textEditingValue.selection.extentOffset, textEditingValue.text.length());
}

/**
 * @tc.name: SelectionAwareTextManipulationTest001
 * @tc.desc: Test the basic functions of Selection Aware Text Manipulation.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, SelectionAwareTextManipulationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the baseOffset and extOffset values, and the baseOffset is less than extOffset.
     * @tc.expected: step1. Consistent with expected results.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.UpdateSelection(LESS_THAN_TEXT_LENGTH, GREATER_THAN_TEXT_LENGTH);
    textEditingValue.SelectionAwareTextManipulation(
        [](std::wstring& manipulateText) { manipulateText += manipulateText; });
    EXPECT_EQ(textEditingValue.text, WIDE_TEXT_TEST);
    EXPECT_EQ(textEditingValue.selection.baseOffset, BEFOR_SELECTION_TEST_LENGTH);
    EXPECT_EQ(textEditingValue.selection.extentOffset, WIDE_TEXT_TEST_LENGTH);
}

/**
 * @tc.name: SelectionAwareTextManipulationTest002
 * @tc.desc: Test manipulation is null of SelectionAwareTextManipulation.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, SelectionAwareTextManipulationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameter, manipulateText is set to zero.
     * @tc.expected: step1. ManipulateText is null, the function exits, and the text remains unchanged.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.UpdateSelection(LESS_THAN_TEXT_LENGTH, GREATER_THAN_TEXT_LENGTH);
    textEditingValue.SelectionAwareTextManipulation(0);
    EXPECT_EQ(textEditingValue.text, TEXT_TEST_VALUE);
}

/**
 * @tc.name: SelectionAwareTextManipulationTest003
 * @tc.desc: Test start is greater than end of SelectionAwareTextManipulation.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, SelectionAwareTextManipulationTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameter, and the value of baseOffset is greater than
     * the value of externtOffset.
     * @tc.expected: step1. The parameter is invalid, the function exits, and the parameter remains unchanged.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.selection.baseOffset = GREATER_THAN_TEXT_LENGTH;
    textEditingValue.selection.extentOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.SelectionAwareTextManipulation(
        [](std::wstring& manipulateText) { manipulateText += manipulateText; });
    EXPECT_EQ(textEditingValue.text, TEXT_TEST_VALUE);
    EXPECT_EQ(textEditingValue.selection.baseOffset, GREATER_THAN_TEXT_LENGTH);
    EXPECT_EQ(textEditingValue.selection.extentOffset, LESS_THAN_TEXT_LENGTH);
}

/**
 * @tc.name: SelectionAwareTextManipulationTest005
 * @tc.desc: Test that start and end are equal of SelectionAwareTextManipulation.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, SelectionAwareTextManipulationTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set the value of baseOffset equal to that of externtOffset.
     * @tc.expected: step1. Equal to expected results.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.selection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.selection.extentOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.SelectionAwareTextManipulation(
        [](std::wstring& manipulateText) { manipulateText += manipulateText; });
    EXPECT_EQ(textEditingValue.text, WIDE_TEXT_TEST);
    EXPECT_EQ(textEditingValue.selection.baseOffset, BEFOR_SELECTION_TEST_LENGTH);
    EXPECT_EQ(textEditingValue.selection.extentOffset, BEFOR_SELECTION_TEST_LENGTH);
}

/**
 * @tc.name: GetBeforeSelectionTest001
 * @tc.desc: Test the basic functions of GetBeforeSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, GetBeforeSelectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize baseOffset so that it is greater than the length of text.
     * @tc.expected: step1. Function exit, return empty string.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.selection.baseOffset = 20;
    auto beforeText = textEditingValue.GetBeforeSelection();
    EXPECT_EQ(beforeText, "");

    /**
     * @tc.steps: step2. Initialization parameter. The length of baseOffset is greater than zero and less than text.
     * @tc.expected: step2. Return expected results.
     */
    textEditingValue.selection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.selection.extentOffset = GREATER_THAN_TEXT_LENGTH;
    beforeText = textEditingValue.GetBeforeSelection();
    EXPECT_EQ(beforeText, "text_t");

    /**
     * @tc.steps: step3. Initialization parameter, baseOffset is less than zero.
     * @tc.expected: step3. Function exit, return empty string.
     */
    textEditingValue.selection.baseOffset = -1;
    beforeText = textEditingValue.GetBeforeSelection();
    EXPECT_EQ(beforeText, "");
}

/**
 * @tc.name: GetSelectedTextTest001
 * @tc.desc: Test the basic functions of GetSelectedText without parameters.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, GetSelectedTextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameter, extentOffset is greater than the length of text.
     * @tc.expected: step1. Function exit, return empty string.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.selection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.selection.extentOffset = GREATER_THAN_TEXT_LENGTH;
    auto beforeText = textEditingValue.GetSelectedText();
    EXPECT_EQ(beforeText, "");

    /**
     * @tc.steps: step2. Initialization parameter, baseOffset is less than zero.
     * @tc.expected: step2. Output expected results.
     */
    textEditingValue.UpdateSelection(-1, GREATER_THAN_TEXT_LENGTH);
    beforeText = textEditingValue.GetSelectedText();
    EXPECT_EQ(beforeText, TEXT_TEST_VALUE);

    /**
     * @tc.steps: step3. Initialization parameter, baseOffset is greater than zero and less than extentOffset.
     * @tc.expected: step3. Output expected results.
     */
    textEditingValue.UpdateSelection(LESS_THAN_TEXT_LENGTH, GREATER_THAN_TEXT_LENGTH);
    beforeText = textEditingValue.GetSelectedText();
    EXPECT_EQ(beforeText, "est_value");

    /**
     * @tc.steps: step4. Initialization parameter, baseOffset is equal to extentOffset.
     * @tc.expected: step4. Function exit, return empty string.
     */
    textEditingValue.selection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.selection.extentOffset = LESS_THAN_TEXT_LENGTH;
    beforeText = textEditingValue.GetSelectedText();
    EXPECT_EQ(beforeText, "");
}

/**
 * @tc.name: GetSelectedTextTest002
 * @tc.desc: Test the basic functions of GetSelectedText with parameters.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, GetSelectedTextTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameter, extentOffset is greater than the length of text.
     * @tc.expected: step1. Output expected results.
     */
    TextEditingValue textEditingValue;
    TextSelection textSelection;
    textEditingValue.text = TEXT_TEST_VALUE;
    textSelection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textSelection.extentOffset = GREATER_THAN_TEXT_LENGTH;
    auto beforeText = textEditingValue.GetSelectedText(textSelection);
    EXPECT_EQ(beforeText, "est_value");

    /**
     * @tc.steps: step2. Initialization parameter, baseOffset is less than zero.
     * @tc.expected: step2. Output expected results.
     */
    textEditingValue.UpdateSelection(-1, GREATER_THAN_TEXT_LENGTH);
    textSelection.baseOffset = -1;
    textSelection.extentOffset = 15;
    beforeText = textEditingValue.GetSelectedText(textSelection);
    EXPECT_EQ(beforeText, "text_test_value");

    /**
     * @tc.steps: step3. Initialization parameter, baseOffset is greater than zero,
     * and extentOffset is equal to the text length.
     * @tc.expected: step3. Output expected results.
     */
    textSelection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textSelection.extentOffset = 15;
    beforeText = textEditingValue.GetSelectedText(textSelection);
    EXPECT_EQ(beforeText, "est_value");

    /**
     * @tc.steps: step4. Initialization parameter, baseOffset is equal to extentOffset.
     * @tc.expected: step4. Function exit, return empty string.
     */
    textSelection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textSelection.extentOffset = LESS_THAN_TEXT_LENGTH;
    beforeText = textEditingValue.GetSelectedText(textSelection);
    EXPECT_EQ(beforeText, "");
}

/**
 * @tc.name: GetAfterSelectionTest001
 * @tc.desc: Test the basic functions of GetAfterSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, GetAfterSelectionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameter, the value of extentOffset is greater than the length of text.
     * @tc.expected: step1. Function exit, return empty string.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.selection.baseOffset = LESS_THAN_TEXT_LENGTH;
    textEditingValue.selection.extentOffset = GREATER_THAN_TEXT_LENGTH;
    auto beforeText = textEditingValue.GetAfterSelection();
    EXPECT_EQ(beforeText, "");

    /**
     * @tc.steps: step2. Initialization parameter, the value of extentOffset is less than zero.
     * @tc.expected: step2. Output expected results.
     */
    textEditingValue.selection.extentOffset = -1;
    beforeText = textEditingValue.GetAfterSelection();
    EXPECT_EQ(beforeText, "est_value");

    /**
     * @tc.steps: step3. Initialization parameter, the value of externtOffset is greater than zero
     * and less than the length of text.
     * @tc.expected: step3. Output expected results.
     */
    textEditingValue.selection.baseOffset = 5;
    textEditingValue.selection.extentOffset = 12;
    beforeText = textEditingValue.GetAfterSelection();
    EXPECT_EQ(beforeText, "lue");
}

/**
 * @tc.name: DeleteTest001
 * @tc.desc: Test the basic functions of Delete.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, DeleteTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameter, baseOffset is less than externtOffset.
     * @tc.expected: step1. Output expected results.
     */
    TextEditingValue textEditingValue;
    textEditingValue.text = TEXT_TEST_VALUE;
    textEditingValue.Delete(LESS_THAN_TEXT_LENGTH, GREATER_THAN_TEXT_LENGTH);
    EXPECT_EQ(textEditingValue.text, "text_t");
    EXPECT_EQ(textEditingValue.selection.baseOffset, 6);
    EXPECT_EQ(textEditingValue.selection.extentOffset, 6);

    /**
     * @tc.steps: step2. Initialization parameter, baseOffset is greater than extentOffset.
     * @tc.expected: step2. Output expected results.
     */
    textEditingValue.selection.Update(-1);
    textEditingValue.Delete(20, 25);
    EXPECT_EQ(textEditingValue.selection.baseOffset, -1);
    EXPECT_EQ(textEditingValue.selection.extentOffset, -1);
}

/**
 * @tc.name: FormatTest001
 * @tc.desc: Test invalid parameters of Format.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the parameter so that the length of the text is less than the input parameter.
     * @tc.expected: step1. Function exit, selection is the default value.
     */
    TextEditingValue newValue;
    TextEditingValue oldValue;
    LengthLimitingFormatter lengthLimitingFormatter(20);
    newValue.text = TEXT_TEST_VALUE;

    lengthLimitingFormatter.Format(oldValue, newValue);
    EXPECT_EQ(newValue.text, TEXT_TEST_VALUE);
    EXPECT_EQ(newValue.selection.baseOffset, -1);
    EXPECT_EQ(newValue.selection.extentOffset, -1);
}

/**
 * @tc.name: FormatTest002
 * @tc.desc: Test invalid parameters of text length.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameter, start is less than end, and limit is equal to start.
     * @tc.expected: step1. Output expected results.
     */
    TextEditingValue newValue;
    TextEditingValue oldValue;
    LengthLimitingFormatter lengthLimitingFormatter(LESS_THAN_TEXT_LENGTH);
    newValue.text = TEXT_TEST_VALUE;
    newValue.selection.baseOffset = LESS_THAN_TEXT_LENGTH;
    newValue.selection.extentOffset = GREATER_THAN_TEXT_LENGTH;

    lengthLimitingFormatter.Format(oldValue, newValue);
    EXPECT_EQ(newValue.text, TEXT_TEST_VALUE);
    EXPECT_EQ(newValue.selection.baseOffset, 6);
    EXPECT_EQ(newValue.selection.extentOffset, 20);
}

/**
 * @tc.name: FormatTest003
 * @tc.desc: Test basic functions of Format.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize parameters to make removeBeforeExtent and removeAfterExtent greater than zero.
     * @tc.expected: step1. Output expected results.
     */
    TextEditingValue newValue;
    TextEditingValue oldValue;
    LengthLimitingFormatter lengthLimitingFormatter(1);
    newValue.text = TEXT_TEST_VALUE;
    newValue.selection.baseOffset = LESS_THAN_TEXT_LENGTH;
    newValue.selection.extentOffset = 10;

    lengthLimitingFormatter.Format(oldValue, newValue);
    EXPECT_EQ(newValue.text, "v");
    EXPECT_EQ(newValue.selection.baseOffset, 0);
    EXPECT_EQ(newValue.selection.extentOffset, 0);
}

/**
 * @tc.name: FormatTest004
 * @tc.desc: Test remove after extent of format.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the parameter to make removeAfterExtent less than or equal to zero.
     * @tc.expected: step1. Output expected results.
     */
    TextEditingValue newValue;
    TextEditingValue oldValue;
    LengthLimitingFormatter lengthLimitingFormatter(14);
    newValue.text = TEXT_TEST_VALUE;
    newValue.selection.extentOffset = 10;

    lengthLimitingFormatter.Format(oldValue, newValue);
    EXPECT_EQ(newValue.text, "text_testvalue");
    EXPECT_EQ(newValue.selection.baseOffset, 9);
    EXPECT_EQ(newValue.selection.extentOffset, 9);
}

/**
 * @tc.name: FormatTest005
 * @tc.desc: Test invalid parameters of removeBeforeExtent.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize parameters to make removeBeforeExtent less than or equal to zero.
     * @tc.expected: step1. Output expected results.
     */
    TextEditingValue newValue;
    TextEditingValue oldValue;
    LengthLimitingFormatter lengthLimitingFormatter(14);
    newValue.text = TEXT_TEST_VALUE;
    newValue.selection.extentOffset = 0;

    lengthLimitingFormatter.Format(oldValue, newValue);
    EXPECT_EQ(newValue.text, "text_test_valu");
    EXPECT_EQ(newValue.selection.baseOffset, -1);
}

/**
 * @tc.name: FormatTest006
 * @tc.desc: Test blackListCharsFormatter.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest006, TestSize.Level1)
{
    TextEditingValue newValue;
    TextEditingValue oldValue;
    std::wregex regex(L"[^\\d]");
    BlackListCharsFormatter blackListCharsFormatter(std::move(regex));

    newValue.text = "abc123";
    newValue.selection.extentOffset = 0;

    blackListCharsFormatter.Format(oldValue, newValue);

    EXPECT_EQ(newValue.text, "123");
    EXPECT_EQ(newValue.selection.baseOffset, -1);
}

/**
 * @tc.name: FormatTest007
 * @tc.desc: Test numberFormatter.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest007, TestSize.Level1)
{
    TextEditingValue newValue;
    TextEditingValue oldValue;
    NumberFormatter numberFormatter;

    newValue.text = "123abc456def";
    newValue.selection.extentOffset = 0;

    numberFormatter.Format(oldValue, newValue);

    EXPECT_EQ(newValue.text, "123456e");
    EXPECT_EQ(newValue.selection.baseOffset, -1);
}

/**
 * @tc.name: FormatTest008
 * @tc.desc: Test phoneNumberFormatter.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest008, TestSize.Level1)
{
    TextEditingValue newValue;
    TextEditingValue oldValue;
    PhoneNumberFormatter phoneNumberFormatter;

    newValue.text = "123-456-7890";
    newValue.selection.extentOffset = 0;

    phoneNumberFormatter.Format(oldValue, newValue);

    EXPECT_EQ(newValue.text, "123-456-7890");
    EXPECT_EQ(newValue.selection.baseOffset, -1);

    newValue.text = "abc123";
    phoneNumberFormatter.Format(oldValue, newValue);

    EXPECT_EQ(newValue.text, "123");
    EXPECT_EQ(newValue.selection.baseOffset, -1);
}

/**
 * @tc.name: FormatTest009
 * @tc.desc: Test emailFormatter.
 * @tc.type: FUNC
 */
HWTEST_F(ImeTest, FormatTest009, TestSize.Level1)
{
    TextEditingValue newValue;
    TextEditingValue oldValue;
    EmailFormatter emailFormatter;

    newValue.text = "test@example";
    emailFormatter.Format(oldValue, newValue);

    EXPECT_EQ(newValue.text, "test@example");
    EXPECT_EQ(newValue.selection.baseOffset, -1);
}
} // namespace OHOS::Ace
