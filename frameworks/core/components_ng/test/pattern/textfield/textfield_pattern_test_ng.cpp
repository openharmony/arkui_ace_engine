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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "textfield_test_ng_utils.h"
#define private public
#define protected public
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_VALUE = "DEFAULT_TEXT";
const std::string INSERT_VALUE_SINGLE_NUMBER = "1";
const std::string INSERT_VALUE_SINGLE_CHAR = "X";
const std::string LOWERCASE_FILTER = "[a-z]";
const std::string NUMBER_FILTER = "^[0-9]*$";
const int32_t CARET_POSITION_1 = 10;
const int32_t DELETE_LENGTH_1 = 1;
} // namespace
class TextFieldPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    RefPtr<TextFieldPattern> GetTextFieldPattern();
    RefPtr<TextFieldLayoutProperty> GetLayoutPropertyFromHost(const RefPtr<TextFieldPattern>& pattern);
    RefPtr<FrameNode> host_;
};

void TextFieldPatternTestNg::SetUp() {}

void TextFieldPatternTestNg::TearDown()
{
    host_ = nullptr;
}

RefPtr<TextFieldPattern> TextFieldPatternTestNg::GetTextFieldPattern()
{
    host_ = TextFieldTestNgUtils::CreatTextFieldNode();
    return host_ ? host_->GetPattern<TextFieldPattern>() : nullptr;
}

RefPtr<TextFieldLayoutProperty> TextFieldPatternTestNg::GetLayoutPropertyFromHost(
    const RefPtr<TextFieldPattern>& pattern)
{
    if (pattern && pattern->GetHost()) {
        return pattern->GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    }
    GetTextFieldPattern();
    return host_ ? host_->GetLayoutProperty<TextFieldLayoutProperty>() : nullptr;
}
/**
 * @tc.name: TextFieldInsertValue001
 * @tc.desc: Test inserting value of textfield.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldInsertValue001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->InsertValue(INSERT_VALUE_SINGLE_CHAR);
    EXPECT_EQ(pattern->GetEditingValue().text, INSERT_VALUE_SINGLE_CHAR);
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, INSERT_VALUE_SINGLE_CHAR.size());
}

/**
 * @tc.name: TextFieldInsertValue002
 * @tc.desc: Test textfield insert a value and clear it when type changed.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldInsertValue002, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    textFieldModelNG.SetType(TextInputType::TEXT);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->InsertValue(INSERT_VALUE_SINGLE_CHAR);
    EXPECT_EQ(pattern->GetEditingValue().text, INSERT_VALUE_SINGLE_CHAR);
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, INSERT_VALUE_SINGLE_CHAR.size());
    auto secNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    textFieldModelNG.SetType(TextInputType::NUMBER);
    pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->ClearEditingValue();
    EXPECT_EQ(pattern->GetEditingValue().text.length(), 0);
}

/**
 * @tc.name: TextFieldDeleteForwardValue001
 * @tc.desc: Test deleting value of textfield.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldDeleteForwardValue001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->InsertValue(TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().text, TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, static_cast<int32_t>(TEXT_VALUE.size()));
    pattern->DeleteForward(DELETE_LENGTH_1);
    EXPECT_EQ(pattern->GetEditingValue().text, TEXT_VALUE.substr(0, TEXT_VALUE.size() - DELETE_LENGTH_1));
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, TEXT_VALUE.size() - DELETE_LENGTH_1);
}

/**
 * @tc.name: TextFieldMoveCaret001
 * @tc.desc: Test textfield move caret.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldMoveCaret001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->InsertValue(TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().text, TEXT_VALUE);
    pattern->SetCaretPosition(CARET_POSITION_1);
    // inserting text value length larger than caret position
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, CARET_POSITION_1);
}

/**
 * @tc.name: TextFieldFilter001
 * @tc.desc: Test textfield filter.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldFilter001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateInputFilter(LOWERCASE_FILTER);
    pattern->InsertValue(INSERT_VALUE_SINGLE_CHAR);
    EXPECT_EQ(pattern->GetEditingValue().text, EMPTY_TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, EMPTY_TEXT_VALUE.size());
}

/**
 * @tc.name: TextFieldFilter002
 * @tc.desc: Test textfield filter.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldFilter002, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateInputFilter(NUMBER_FILTER);
    pattern->InsertValue(INSERT_VALUE_SINGLE_NUMBER);
    EXPECT_EQ(pattern->GetEditingValue().text, INSERT_VALUE_SINGLE_NUMBER);
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, INSERT_VALUE_SINGLE_NUMBER.size());
}

/**
 * @tc.name: TextareaMoveCaret001
 * @tc.desc: Test textarea move caret.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextareaMoveCaret001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    auto controller = AccessibilityManager::DynamicCast<TextFieldController>(
        textFieldModelNG.CreateTextArea(PLACEHOLDER, EMPTY_TEXT_VALUE));
    EXPECT_FALSE(controller == nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->InsertValue(TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().text, TEXT_VALUE);
    controller->CaretPosition(CARET_POSITION_1);
    // inserting text value length larger than caret position
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, CARET_POSITION_1);
}

/**
 * @tc.name: FilterWithRegex001
 * @tc.desc: test FilterWithRegex
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, FilterWithRegex001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    std::string result;
    auto funcReturn = textFieldPattern->FilterWithRegex("test", "filter_valuetest", result, true);
    EXPECT_TRUE(funcReturn);
    EXPECT_EQ("test", result);
}

/**
 * @tc.name: FilterWithRegex002
 * @tc.desc: test FilterWithRegex
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, FilterWithRegex002, TestSize.Level2)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    std::string result;
    auto funcReturn = textFieldPattern->FilterWithRegex("filter_value", "", result, true);
    EXPECT_FALSE(funcReturn);
    funcReturn = textFieldPattern->FilterWithRegex("filter_value", "", result);
    EXPECT_FALSE(funcReturn);
    EXPECT_TRUE(result.empty());
    funcReturn = textFieldPattern->FilterWithRegex("", "", result);
    EXPECT_FALSE(funcReturn);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: EditingValueFilter001
 * @tc.desc: test EditingValueFilter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, EditingValueFilter001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    auto layoutProperty = GetLayoutPropertyFromHost(textFieldPattern);
    if (!layoutProperty) {
        EXPECT_FALSE(layoutProperty == nullptr);
        return;
    }
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    std::string result;
    std::string valueToUpdate = "filter_value1test";
    textFieldPattern->EditingValueFilter(valueToUpdate, result);
    EXPECT_EQ(valueToUpdate, "filter_value1test");
    layoutProperty->UpdateInputFilter("test");
    textFieldPattern->EditingValueFilter(valueToUpdate, result);
    EXPECT_EQ(valueToUpdate, "test");
}

/**
 * @tc.name: EditingValueFilter002
 * @tc.desc: test EditingValueFilter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, EditingValueFilter002, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    auto layoutProperty = GetLayoutPropertyFromHost(textFieldPattern);
    if (!layoutProperty) {
        EXPECT_FALSE(layoutProperty == nullptr);
        return;
    }
    layoutProperty->UpdateTextInputType(TextInputType::PHONE);
    std::string result;
    std::string valueToUpdate = "filter_value\\dtest";
    layoutProperty->UpdateInputFilter("test");
    textFieldPattern->EditingValueFilter(valueToUpdate, result);
    EXPECT_EQ(valueToUpdate, "test");
}

/**
 * @tc.name: EditingValueFilter003
 * @tc.desc: test EditingValueFilter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, EditingValueFilter003, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    auto layoutProperty = GetLayoutPropertyFromHost(textFieldPattern);
    if (!layoutProperty) {
        EXPECT_FALSE(layoutProperty == nullptr);
        return;
    }
    layoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    std::string result;
    std::string valueToUpdate = "filter_valuew+test";
    layoutProperty->UpdateInputFilter("test");
    textFieldPattern->EditingValueFilter(valueToUpdate, result);
    EXPECT_EQ(valueToUpdate, "test");
}

/**
 * @tc.name: EditingValueFilter004
 * @tc.desc: test EditingValueFilter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, EditingValueFilter004, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    auto layoutProperty = GetLayoutPropertyFromHost(textFieldPattern);
    if (!layoutProperty) {
        EXPECT_FALSE(layoutProperty == nullptr);
        return;
    }
    layoutProperty->UpdateTextInputType(TextInputType::URL);
    std::string result;
    std::string valueToUpdate = "filter_value//test";
    layoutProperty->UpdateInputFilter("test");
    textFieldPattern->EditingValueFilter(valueToUpdate, result);
    EXPECT_EQ(valueToUpdate, "test");
}

/**
 * @tc.name: GetTextOrPlaceHolderFontSize001
 * @tc.desc: test GetTextOrPlaceHolderFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetTextOrPlaceHolderFontSize001, TestSize.Level2)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    auto size = textFieldPattern->GetTextOrPlaceHolderFontSize();
    EXPECT_EQ(size, 0.0f);
}
} // namespace OHOS::Ace::NG
