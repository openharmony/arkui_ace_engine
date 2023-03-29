/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/text_field/text_editing_value_ng.h"
#include "core/components_ng/pattern/text_field/text_field_accessibility_property.h"
#include "core/components_ng/pattern/text_field/text_field_content_modifier.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_paint_method.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected
#include "core/components_ng/base/view_stack_processor.h"

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
const int32_t CARET_POSITION_2 = 12;
const int32_t DELETE_LENGTH_1 = 1;
const int32_t CARET_POSITION = 0;
const Dimension CURSOR_WIDTH_SIZE = 10.0_vp;
const Dimension DEFAULT_FONT_SIZE { 14, DimensionUnit::PX };
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
const Axis AXIS_VERTICAL = Axis::VERTICAL;
constexpr float CONTEXT_WIDTH_VALUE = 10.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 10.0f;
constexpr float CONTENT_RECT_HEIGHT = 15.0f;
constexpr float CONTENT_RECT_WIDTH = 10.0f;
constexpr float CONTENT_RECT_Y = 5.0f;
constexpr float CONTENT_RECT_Y_LARGE = 50.0f;
constexpr float TEXT_AREA_SCROLL_OFFSET = 10.0f;
constexpr float TEXT_RECT_HEIGHT = 10.0f;
constexpr float TEXT_RECT_HEIGHT_LARGE = 20.0f;
constexpr float TEXT_RECT_WIDTH = 5.0f;
constexpr float TEXT_RECT_Y = 5.0f;
constexpr float TEXT_RECT_Y_LARGE = 50.0f;
const std::string EMPTY_TEXT_VALUE;
const std::string TEXT_EDITING_VALUE("textEditingValue");
const std::string PLACEHOLDER("DEFAULT PLACEHOLDER");
} // namespace
class TextFieldPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    RefPtr<FrameNode> GetFrameNode();
    RefPtr<TextFieldPattern> GetPattern();
    RefPtr<TextFieldPaintProperty> GetPaintProperty();
    RefPtr<TextFieldLayoutProperty> GetLayoutProperty();
    RefPtr<FrameNode> CreatTextFieldNode(const std::optional<std::string>& placeholder = PLACEHOLDER,
        const std::optional<std::string>& value = EMPTY_TEXT_VALUE, bool isTextArea = false);
};

void TextFieldPatternTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void TextFieldPatternTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> TextFieldPatternTestNg::CreatTextFieldNode(
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value, bool isTextArea)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateNode(placeholder, value, isTextArea);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return frameNode;
}

RefPtr<TextFieldLayoutProperty> TextFieldPatternTestNg::GetLayoutProperty()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
}

RefPtr<TextFieldPaintProperty> TextFieldPatternTestNg::GetPaintProperty()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return frameNode->GetPaintProperty<TextFieldPaintProperty>();
}

RefPtr<TextFieldPattern> TextFieldPatternTestNg::GetPattern()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return frameNode->GetPattern<TextFieldPattern>();
}

RefPtr<FrameNode> TextFieldPatternTestNg::GetFrameNode()
{
    TextFieldModelNG textFieldModelNG;
    const std::string placeholder = "DEFAULT PLACEHOLDER";
    const std::string value;
    bool isTextArea = false;
    textFieldModelNG.CreateNode(placeholder, value, isTextArea);
    textFieldModelNG.SetCaretPosition(CARET_POSITION);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return frameNode;
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
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
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
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    textFieldModelNG.SetType(TextInputType::TEXT);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
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
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->InsertValue(TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().text, TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, static_cast<int32_t>(TEXT_VALUE.size()));
    pattern->DeleteForward(DELETE_LENGTH_1);
    EXPECT_EQ(pattern->GetEditingValue().text, TEXT_VALUE.substr(0, TEXT_VALUE.size()));
    LOGI("Lee: %{public}s", pattern->GetEditingValue().text.c_str());
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, TEXT_VALUE.size());
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
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
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
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
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
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
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
    ASSERT_NE(controller, nullptr);
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->InsertValue(TEXT_VALUE);
    EXPECT_EQ(pattern->GetEditingValue().text, TEXT_VALUE);
    controller->CaretPosition(CARET_POSITION_1);
    // inserting text value length larger than caret position
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, CARET_POSITION_2);
}

/**
 * @tc.name: FilterWithRegex001
 * @tc.desc: test FilterWithRegex
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, FilterWithRegex001, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
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
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
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
    auto layoutProperty = GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    std::string result;
    std::string valueToUpdate = "filter_value1test";
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
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
    auto layoutProperty = GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::PHONE);
    std::string result;
    std::string valueToUpdate = "filter_value\\dtest";
    layoutProperty->UpdateInputFilter("test");
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
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
    auto layoutProperty = GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    std::string result;
    std::string valueToUpdate = "filter_valuew+test";
    layoutProperty->UpdateInputFilter("test");
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
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
    auto layoutProperty = GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::URL);
    std::string result;
    std::string valueToUpdate = "filter_value//test";
    layoutProperty->UpdateInputFilter("test");
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
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
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    auto size = textFieldPattern->GetTextOrPlaceHolderFontSize();
    EXPECT_EQ(size, 0.0f);
}

/**
 * @tc.name: UpdateCaretPosition001
 * @tc.desc: test UpdateCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretPosition001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::INPUT);
    EXPECT_FALSE(textFieldPattern->UpdateCaretPosition());
}

/**
 * @tc.name: UpdateCaretPosition002
 * @tc.desc: test UpdateCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretPosition002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::NONE);
    EXPECT_TRUE(textFieldPattern->UpdateCaretPosition());
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::NONE);
    EXPECT_TRUE(textFieldPattern->UpdateCaretPosition());
}

/**
 * @tc.name: UpdateCaretPosition003
 * @tc.desc: test UpdateCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretPosition003, TestSize.Level2)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    EXPECT_TRUE(textFieldPattern->UpdateCaretPosition());
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::DEL);
    EXPECT_FALSE(textFieldPattern->UpdateCaretPosition());
}

/**
 * @tc.name: IsTextArea001
 * @tc.desc: test IsTextArea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, IsTextArea001, TestSize.Level1)
{
    auto layoutProperty = GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    EXPECT_FALSE(textFieldPattern->IsTextArea());
    layoutProperty->UpdateMaxLines(1);
    EXPECT_FALSE(textFieldPattern->IsTextArea());
    layoutProperty->UpdateMaxLines(2);
    EXPECT_TRUE(textFieldPattern->IsTextArea());
}

/**
 * @tc.name: UpdateDestinationToCaretByEvent001
 * @tc.desc: test UpdateDestinationToCaretByEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateDestinationToCaretByEvent001, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->isMousePressed_ = true;
    textFieldPattern->UpdateEditingValue(TEXT_VALUE, static_cast<int32_t>(TEXT_VALUE.size()));
    textFieldPattern->UpdateDestinationToCaretByEvent();
    EXPECT_EQ(textFieldPattern->GetSelectMode(), SelectionMode::NONE);
}

/**
 * @tc.name: UpdateCaretOffsetByLastTouchOffset001
 * @tc.desc: test UpdateCaretOffsetByLastTouchOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretOffsetByLastTouchOffset001, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    SizeF contentSize(730.0, 160.0);
    SizeF textSize(720.0, 150.0);
    textFieldPattern->contentRect_.Reset();
    textFieldPattern->textRect_.Reset();
    textFieldPattern->caretRect_.Reset();
    textFieldPattern->contentRect_.SetSize(contentSize);
    textFieldPattern->textRect_.SetSize(textSize);
    textFieldPattern->InitEditingValueText(TEXT_VALUE);
    textFieldPattern->lastTouchOffset_ = Offset(725.0, 0.0);
    textFieldPattern->UpdateCaretOffsetByLastTouchOffset();
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, 0);
    EXPECT_EQ(textFieldPattern->GetCaretOffsetX(), 0);
}

/**
 * @tc.name: UpdateCaretOffsetByLastTouchOffset002
 * @tc.desc: test UpdateCaretOffsetByLastTouchOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretOffsetByLastTouchOffset002, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    SizeF contentSize(730.0, 160.0);
    SizeF textSize(720.0, 150.0);
    OffsetF textOffset(10.0, 0.0);
    textFieldPattern->contentRect_.Reset();
    textFieldPattern->textRect_.Reset();
    textFieldPattern->caretRect_.Reset();
    textFieldPattern->contentRect_.SetSize(contentSize);
    textFieldPattern->textRect_.SetSize(textSize);
    textFieldPattern->textRect_.SetOffset(textOffset);
    textFieldPattern->InitEditingValueText(TEXT_VALUE);
    textFieldPattern->UpdateCaretOffsetByLastTouchOffset();
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, 0);
}

/**
 * @tc.name: UpdateCaretOffsetByLastTouchOffset003
 * @tc.desc: test UpdateCaretOffsetByLastTouchOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretOffsetByLastTouchOffset003, TestSize.Level2)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    SizeF contentSize(710.0, 160.0);
    SizeF textSize(720.0, 150.0);
    textFieldPattern->contentRect_.Reset();
    textFieldPattern->textRect_.Reset();
    textFieldPattern->caretRect_.Reset();
    textFieldPattern->contentRect_.SetSize(contentSize);
    textFieldPattern->textRect_.SetSize(textSize);
    textFieldPattern->InitEditingValueText(TEXT_VALUE);
    textFieldPattern->UpdateCaretOffsetByLastTouchOffset();
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, 0);
    EXPECT_EQ(textFieldPattern->GetCaretOffsetX(), 0.0);
}

/**
 * @tc.name: CursorWidth001
 * @tc.desc: Verify that the CursorWidth interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CursorWidth001, TestSize.Level1)
{
    auto frameNode = GetFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    ASSERT_NE(textFieldPattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCursorWidth(CURSOR_WIDTH_SIZE);
    textFieldPattern->OnModifyDone();
    EXPECT_EQ(paintProperty->GetCursorWidthValue(), CURSOR_WIDTH_SIZE);
}

/**
 * @tc.name: SelectedColor001
 * @tc.desc: Verify that the SelectedColor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SelectedColor001, TestSize.Level1)
{
    auto frameNode = GetFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    ASSERT_NE(textFieldPattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedBackgroundColor(Color::BLACK);
    textFieldPattern->scrollableEvent_ = nullptr;
    textFieldPattern->OnModifyDone();
    textFieldPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(AXIS_VERTICAL);
    textFieldPattern->OnModifyDone();
    EXPECT_TRUE(paintProperty->GetSelectedBackgroundColor().has_value());
}

/**
 * @tc.name: CaretPosition001
 * @tc.desc: Verify that the CursorPosition interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CaretPosition001, TestSize.Level1)
{
    auto frameNode = GetFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCaretPosition(CARET_POSITION);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    textFieldPattern->OnModifyDone();
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, CARET_POSITION);
}

/**
 * @tc.name: CaretPosition002
 * @tc.desc: Verify that the CursorPosition interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CaretPosition002, TestSize.Level1)
{
    auto frameNode = GetFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCaretPosition(CARET_POSITION);
    textFieldPattern->UpdateCaretRectByPosition(CARET_POSITION);
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, CARET_POSITION);
}

/**
 * @tc.name: CaretPosition003
 * @tc.desc: Verify that the CursorPosition interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CaretPosition003, TestSize.Level1)
{
    auto frameNode = GetFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCaretPosition(CARET_POSITION);
    textFieldPattern->UpdateCaretPositionByPressOffset();
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, CARET_POSITION);
}

/**
 * @tc.name: CaretPosition004
 * @tc.desc: Verify that the CursorPosition interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CaretPosition004, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    const std::string placeholder = "DEFAULT PLACEHOLDER";
    const std::string value;
    const std::string TEXT_VALUE = "DEFAULT_TEXT";
    bool isTextArea = false;
    textFieldModelNG.CreateNode(placeholder, value, isTextArea);
    textFieldModelNG.SetCaretPosition(CARET_POSITION);
    auto frameNode = CreatTextFieldNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCaretPosition(CARET_POSITION);
    textFieldPattern->InitEditingValueText(TEXT_VALUE);
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, TEXT_VALUE.length());
}

/**
 * @tc.name: CaretPosition005
 * @tc.desc: Verify that the CursorPosition interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CaretPosition005, TestSize.Level1)
{
    auto frameNode = GetFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCaretPosition(CARET_POSITION);
    textFieldPattern->textEditingValue_.text = "text";
    textFieldPattern->UpdateCaretPositionByPressOffset();
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, CARET_POSITION);
}

/**
 * @tc.name: ModifyTextStyle001
 * @tc.desc: Verify that the ModifyTextStyle interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ModifyTextStyle001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextFieldTheme>()));
    TextFieldContentModifier textFieldContentModifier(pattern);
    TextStyle textStyle;
    textFieldContentModifier.ModifyTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetFontSize().ConvertToPx(), DEFAULT_FONT_SIZE.ConvertToPx());
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, OnScrollCallback001, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    const float offset = 0.0;
    const int32_t source = 0;
    bool ret = false;
    ret = textFieldPattern->OnScrollCallback(offset, source);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CheckScrollable001
 * @tc.desc: Verify that the CheckScrollable interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CheckScrollable001, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textEditingValue_.text = "";
    EXPECT_TRUE(textFieldPattern->scrollable_);
    textFieldPattern->CheckScrollable();
    EXPECT_FALSE(textFieldPattern->scrollable_);
}

/**
 * @tc.name: CheckScrollable002
 * @tc.desc: Verify that the CheckScrollable interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CheckScrollable002, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textEditingValue_.text = "checkScrollable";
    textFieldPattern->textRect_.SetHeight(1.0);
    textFieldPattern->contentRect_.SetHeight(0.0);
    textFieldPattern->scrollable_ = false;
    textFieldPattern->CheckScrollable();
    EXPECT_TRUE(textFieldPattern->scrollable_);
}

/**
 * @tc.name: CheckScrollable003
 * @tc.desc: Verify that the CheckScrollable interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CheckScrollable003, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textEditingValue_.text = "checkScrollable";
    textFieldPattern->textRect_.SetHeight(0.0);
    textFieldPattern->contentRect_.SetHeight(0.0);
    EXPECT_TRUE(textFieldPattern->scrollable_);
    textFieldPattern->CheckScrollable();
    EXPECT_FALSE(textFieldPattern->scrollable_);
}

/**
 * @tc.name: CheckScrollable004
 * @tc.desc: Verify that the CheckScrollable interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CheckScrollable004, TestSize.Level1)
{
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textEditingValue_.text = "checkScrollable";
    textFieldPattern->textRect_.SetHeight(0.0);
    textFieldPattern->contentRect_.SetHeight(1.0);
    EXPECT_FALSE(textFieldPattern->scrollable_);
    textFieldPattern->CheckScrollable();
    EXPECT_FALSE(textFieldPattern->scrollable_);
}

/**
 * @tc.name: UpdateCaretRectByPosition001
 * @tc.desc: Verify that the UpdateCaretRectByPosition interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretRectByPosition001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    const int32_t position = 0;
    pattern->UpdateCaretRectByPosition(position);
    EXPECT_EQ(pattern->GetEditingValue().caretPosition, position);
}

/**
 * @tc.name: SetFrameSize001
 * @tc.desc: Verify that the SetFrameSize interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetFrameSize001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    SizeF value;
    textFieldOverlayModifier.SetFrameSize(value);
    EXPECT_EQ(textFieldOverlayModifier.frameSize_->Get(), value);
}

/**
 * @tc.name: SetCurrentOffset001
 * @tc.desc: Verify that the SetCurrentOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetCurrentOffset001, TestSize.Level1)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    float value = 1.0;
    textFieldOverlayModifier.SetCurrentOffset(value);
    EXPECT_EQ(textFieldOverlayModifier.currentOffset_->Get(), value);
}

/**
 * @tc.name: GetContentModifier001
 * @tc.desc: Verify that the GetContentModifier interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetContentModifier001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollBar, scrollEdgeEffect);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    TextFieldPaintMethod textFieldPaintMethod(pattern, textFieldOverlayModifier, textFieldContentModifier);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);
    EXPECT_NE(textFieldPaintMethod.GetContentModifier(&paintWrapper), nullptr);
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Verify that the UpdateContentModifier interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateContentModifier001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollBar, scrollEdgeEffect);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    textFieldContentModifier->contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    textFieldContentModifier->contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    textFieldContentModifier->textValue_ = AceType::MakeRefPtr<PropertyString>("");
    textFieldContentModifier->textRectY_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    textFieldContentModifier->textRectX_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    TextFieldPaintMethod textFieldPaintMethod(pattern, textFieldOverlayModifier, textFieldContentModifier);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);
    textFieldPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(textFieldContentModifier->contentOffset_->Get(), CONTENT_OFFSET);
}

/**
 * @tc.name: GetOverlayModifier001
 * @tc.desc: Verify that the GetOverlayModifier interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetOverlayModifier001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollBar, scrollEdgeEffect);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    TextFieldPaintMethod textFieldPaintMethod(pattern, textFieldOverlayModifier, textFieldContentModifier);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);
    EXPECT_NE(textFieldPaintMethod.GetOverlayModifier(&paintWrapper), nullptr);
}

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Verify that the UpdateOverlayModifier interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollBar, scrollEdgeEffect);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    TextFieldPaintMethod textFieldPaintMethod(pattern, textFieldOverlayModifier, textFieldContentModifier);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);
    textFieldPaintMethod.UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(textFieldOverlayModifier->contentSize_->Get(), CONTENT_SIZE);
}

/**
 * @tc.name: SetContentOffset002
 * @tc.desc: Verify that the SetContentOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetContentOffset002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    OffsetF value = CONTENT_OFFSET;
    textFieldContentModifier.contentOffset_ = nullptr;
    textFieldContentModifier.SetContentOffset(value);
    textFieldContentModifier.contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    textFieldContentModifier.SetContentOffset(value);
    EXPECT_EQ(textFieldContentModifier.contentOffset_->Get(), value);
}

/**
 * @tc.name: SetContentSize002
 * @tc.desc: Verify that the SetContentSize interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetContentSize002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    SizeF value = CONTENT_SIZE;
    textFieldContentModifier.contentSize_ = nullptr;
    textFieldContentModifier.SetContentSize(value);
    textFieldContentModifier.contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    textFieldContentModifier.SetContentSize(value);
    EXPECT_EQ(textFieldContentModifier.contentSize_->Get(), value);
}

/**
 * @tc.name: SetTextValue001
 * @tc.desc: Verify that the SetTextValue interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextValue001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    std::string value1 = "";
    textFieldContentModifier.textValue_ = AceType::MakeRefPtr<PropertyString>("");
    textFieldContentModifier.SetTextValue(value1);
    std::string value2 = "text";
    textFieldContentModifier.SetTextValue(value2);
    EXPECT_EQ(textFieldContentModifier.textValue_->Get(), value2);
}

/**
 * @tc.name: SetTextRectY001
 * @tc.desc: Verify that the SetTextRectY interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextRectY001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.textRectY_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    const float value = 1.0;
    textFieldContentModifier.SetTextRectY(value);
    EXPECT_EQ(textFieldContentModifier.textRectY_->Get(), value);
}

/**
 * @tc.name: TextFieldPatternUpdateScrollBarOffset001
 * @tc.desc: Verify that the UpdateScrollBarOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldPatternUpdateScrollBarOffset001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateScrollBarOffset();
    EXPECT_EQ(pattern->textEditingValue_.text, "checkScrollable");
}

/**
 * @tc.name: TextFieldPatternUpdateScrollBarOffset002
 * @tc.desc: Verify that the UpdateScrollBarOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldPatternUpdateScrollBarOffset002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textEditingValue_.Reset();
    pattern->UpdateScrollBarOffset();
    EXPECT_TRUE(pattern->textEditingValue_.text.empty());
    pattern->textEditingValue_.text = "updateScrollBarOffset";
    pattern->UpdateScrollBarOffset();
    EXPECT_EQ(pattern->GetScrollBar(), nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    pattern->scrollBar_ = scrollBar;
    auto scrollBarProxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    pattern->scrollBarProxy_ = scrollBarProxy;
    pattern->UpdateScrollBarOffset();
    ASSERT_FALSE(!pattern->GetScrollBar() && !pattern->GetScrollBarProxy());
}

/**
 * @tc.name: TextFieldPatternSearchNodeTest001
 * @tc.desc: Verify the parent search node branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldPatternSearchNodeTest001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto searchNode = AceType::MakeRefPtr<FrameNode>(V2::SEARCH_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>(), false);
    frameNode->MountToParent(searchNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->HasFocus();
    auto info = GestureEvent();
    pattern->UpdateCaretInfoToController();
    pattern->HandleClickEvent(info);
    pattern->HandleLongPress(info);
    auto mouseInfo = MouseInfo();
    pattern->HandleMouseEvent(mouseInfo);
    EXPECT_EQ(pattern->IsSearchParentNode(), true);
}

/**
 * @tc.name: TextFieldPatternOnTextAreaScroll001
 * @tc.desc: Verify that the AddScrollEvent interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldPatternOnTextAreaScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextFieldPattern.
     * @tc.expected: step1. Check the TextFieldPattern success.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call the OnTextAreaScroll.
     * @tc.expected: step2. Check the value set in OnTextAreaScroll.
     */
    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateMaxLines(5);
    // Is TextArea, textRect_.Height() < contentRect_.Height()
    pattern->textRect_.SetHeight(TEXT_RECT_HEIGHT);
    pattern->textRect_.SetWidth(TEXT_RECT_WIDTH);
    pattern->contentRect_.SetHeight(CONTENT_RECT_HEIGHT);
    pattern->contentRect_.SetWidth(CONTENT_RECT_WIDTH);
    pattern->OnTextAreaScroll(TEXT_AREA_SCROLL_OFFSET);
    // Is TextArea, textRect Height > contentRect Height, textRect Y + offset > contentRect Y.
    pattern->textRect_.SetHeight(TEXT_RECT_HEIGHT_LARGE);
    pattern->textRect_.SetWidth(TEXT_RECT_WIDTH);
    pattern->textRect_.SetTop(TEXT_RECT_Y);
    pattern->contentRect_.SetHeight(CONTENT_RECT_HEIGHT);
    pattern->contentRect_.SetWidth(CONTENT_RECT_WIDTH);
    pattern->contentRect_.SetTop(CONTENT_RECT_Y);
    pattern->OnTextAreaScroll(TEXT_AREA_SCROLL_OFFSET);
    // Is TextArea, textRect Height > contentRect Height, textRect Y + offset < contentRect Y.
    // textRect Y + offset - contentRect Heigh > textRect Height.
    pattern->contentRect_.SetTop(CONTENT_RECT_Y_LARGE);
    pattern->textRect_.SetTop(TEXT_RECT_Y_LARGE);
    pattern->OnTextAreaScroll(TEXT_AREA_SCROLL_OFFSET);
    // Is TextArea, textRect Height > contentRect Height, textRect Y + offset < contentRect Y.
    // textRect Y + offset - contentRectHeight < textRect Height.
    pattern->contentRect_.SetTop(CONTENT_RECT_Y_LARGE);
    pattern->textRect_.SetTop(TEXT_RECT_Y);
    pattern->OnTextAreaScroll(TEXT_AREA_SCROLL_OFFSET);
    pattern->isSingleHandle_ = false;
    pattern->OnTextAreaScroll(TEXT_AREA_SCROLL_OFFSET);
    pattern->isSingleHandle_ = true;
    float oldCaretRectY = pattern->caretRect_.GetY();
    pattern->OnTextAreaScroll(TEXT_AREA_SCROLL_OFFSET);
    EXPECT_EQ(pattern->caretRect_.GetY(), oldCaretRectY + TEXT_AREA_SCROLL_OFFSET);
    EXPECT_EQ(pattern->textRect_.GetOffset(), OffsetF(pattern->textRect_.GetX(), pattern->currentOffset_));
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Verify that the onDraw interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, onDraw001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(AXIS_VERTICAL);
    pattern->AddScrollEvent();
    pattern->scrollable_ = true;
    pattern->CheckScrollable();
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    scrollBar->isScrollable_ = true;
    scrollBar->displayMode_ = DisplayMode::AUTO;
    scrollBar->SetNormalWidth(CURSOR_WIDTH_SIZE);
    scrollBar->opacity_ = UINT8_MAX;
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    textFieldOverlayModifier.onDraw(context);
}

/**
 * @tc.name: PaintSelection001
 * @tc.desc: Verify that the PaintSelection interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, PaintSelection001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldOverlayModifier.PaintSelection(context);
}

/**
 * @tc.name: PaintSelection002
 * @tc.desc: Verify that the PaintSelection interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, PaintSelection002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectionMode_ = SelectionMode::SELECT;
    pattern->textSelector_.baseOffset = 1;
    pattern->textSelector_.destinationOffset = 0;
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).WillRepeatedly(Return());
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldOverlayModifier.PaintSelection(context);
}

/**
 * @tc.name: PaintSelection003
 * @tc.desc: Verify that the PaintSelection interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, PaintSelection003, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectionMode_ = SelectionMode::SELECT;
    pattern->textSelector_.baseOffset = 1;
    pattern->textSelector_.destinationOffset = 0;
    std::vector<RSTypographyProperties::TextBox> textBoxs;
    RSTypographyProperties::TextBox textBox;
    textBoxs.emplace_back(textBox);
    pattern->textBoxes_ = textBoxs;
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).WillRepeatedly(Return());
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldOverlayModifier.inputStyle_ = InputStyle::INLINE;
    textFieldOverlayModifier.PaintSelection(context);
    textFieldOverlayModifier.inputStyle_ = InputStyle::DEFAULT;
    textFieldOverlayModifier.PaintSelection(context);
}

/**
 * @tc.name: SetCursortWidth001
 * @tc.desc: Verify that the SetCursorWidth interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetCursortWidth001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    float value = 1.0;
    textFieldOverlayModifier.SetCursorWidth(value);
    EXPECT_EQ(textFieldOverlayModifier.cursorWidth_->Get(), value);
}
/**
 * @tc.name: PaintCursor001
 * @tc.desc: Verify that the PaintCursor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, PaintCursor001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectionMode_ = SelectionMode::NONE;
    pattern->paragraph_ = std::make_shared<RSParagraph>();
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldOverlayModifier.cursorVisible_ = AceType::MakeRefPtr<PropertyBool>(true);
    textFieldOverlayModifier.PaintCursor(context);
    textFieldOverlayModifier.cursorVisible_ = AceType::MakeRefPtr<PropertyBool>(true);
    textFieldOverlayModifier.PaintCursor(context);
}

/**
 * @tc.name: SetTextRectX001
 * @tc.desc: Verify that the SetTextRectX interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextRectX001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.textRectX_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    const float value = 1.0;
    textFieldContentModifier.SetTextRectX(value);
    EXPECT_EQ(textFieldContentModifier.textRectX_->Get(), value);
}

/**
 * @tc.name: TextFieldModelSetType
 * @tc.desc: Create frameNode and settype
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldModelSetType, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    textFieldModelInstance.SetType(TextInputType::TEXT);
    EXPECT_EQ(layoutProperty->GetTextInputTypeValue(), TextInputType::TEXT);
    textFieldModelInstance.SetType(TextInputType::MULTILINE);
    EXPECT_EQ(layoutProperty->GetTextInputTypeValue(), TextInputType::MULTILINE);
    EXPECT_TRUE(layoutProperty->GetTypeChangedValue());
}

/**
 * @tc.name: TextFieldModelSetPlaceholderColor
 * @tc.desc: Create frameNode and PlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldModelSetPlaceholderColor, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    textFieldModelInstance.SetPlaceholderColor(Color::WHITE);
    EXPECT_TRUE(layoutProperty->HasPlaceholderTextColor());
}

/**
 * @tc.name: TextFieldModelSetEnterKeyType
 * @tc.desc: Create frameNode and SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldModelSetEnterKeyType, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    textFieldModelInstance.SetEnterKeyType(TextInputAction::GO);
    auto textFieldPattern = GetPattern();
    EXPECT_EQ(textFieldPattern->GetTextInputActionValue(), TextInputAction::GO);
}

/**
 * @tc.name: SetOnEditChanged
 * @tc.desc: Create frameNode and SetOnEditChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextFieldModelSetOnEditChanged, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    bool callback = false;
    textFieldModelInstance.SetOnEditChanged([&callback](bool info) { callback = info; });
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    EXPECT_TRUE(eventHub);
    eventHub->FireOnEditChanged(true);
    EXPECT_TRUE(callback);
}

/**
 * @tc.name: SetTextObscured
 * @tc.desc: Verify that the SetTextObscured interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextObscured, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    bool value = true;
    textFieldContentModifier.textObscured_ = nullptr;
    textFieldContentModifier.SetTextObscured(value);
    textFieldContentModifier.textObscured_ = AceType::MakeRefPtr<PropertyBool>(value);

    /**
     * @tc.steps: step2. call SetTextObscured function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    textFieldContentModifier.SetTextObscured(value);
    EXPECT_EQ(textFieldContentModifier.textObscured_->Get(), value);
}

/**
 * @tc.name: SetTextAlign
 * @tc.desc: Verify that the SetTextAlign interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextAlign, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    const TextAlign value1 = TextAlign::START;
    textFieldContentModifier.SetTextAlign(value1);
    textFieldContentModifier.textAlign_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(value1));
    const TextAlign value2 = TextAlign::END;

    /**
     * @tc.steps: step2. call SetTextAlign function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    textFieldContentModifier.SetTextAlign(value2);
    EXPECT_EQ(textFieldContentModifier.textAlign_->Get(), static_cast<int32_t>(value2));
}

/**
 * @tc.name: NeedMeasureUpdate001
 * @tc.desc: Verify that the NeedMeasureUpdate interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, NeedMeasureUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    PropertyChangeFlag flag;

    /**
     * @tc.steps: step2. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of false.
     */
    bool ret = true;
    ret = textFieldContentModifier.NeedMeasureUpdate(flag);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedMeasureUpdate002
 * @tc.desc: Verify that the NeedMeasureUpdate interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, NeedMeasureUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    float fontSizeValue1 = 5.0;
    float fontSizeValue2 = 1.0;
    const Dimension fontSize = Dimension(5.0);
    textFieldContentModifier.SetFontSize(fontSize);
    PropertyChangeFlag flag;

    /**
     * @tc.steps: step2. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of false.
     */
    textFieldContentModifier.fontSizeFloat_ = nullptr;
    EXPECT_FALSE(textFieldContentModifier.NeedMeasureUpdate(flag));

    /**
     * @tc.steps: step3. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of false.
     */
    textFieldContentModifier.fontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue1);
    textFieldContentModifier.fontSizeFloat_->Set(fontSizeValue1);
    EXPECT_FALSE(textFieldContentModifier.NeedMeasureUpdate(flag));

    /**
     * @tc.steps: step4. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of true.
     */
    textFieldContentModifier.fontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue2);
    textFieldContentModifier.fontSizeFloat_->Set(fontSizeValue2);
    EXPECT_TRUE(textFieldContentModifier.NeedMeasureUpdate(flag));
}

/**
 * @tc.name: NeedMeasureUpdate003
 * @tc.desc: Verify that the NeedMeasureUpdate interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, NeedMeasureUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    PropertyChangeFlag flag;
    const FontWeight fontWeight = FontWeight::W100;
    textFieldContentModifier.SetFontWeight(fontWeight);
    float fontWeightValue1 = 0.0;
    float fontWeightValue2 = 1.0;

    /**
     * @tc.steps: step2. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of false.
     */
    textFieldContentModifier.fontWeightFloat_ = nullptr;
    EXPECT_FALSE(textFieldContentModifier.NeedMeasureUpdate(flag));

    /**
     * @tc.steps: step3. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of false.
     */
    textFieldContentModifier.fontWeightFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontWeightValue1);
    textFieldContentModifier.fontWeightFloat_->Set(fontWeightValue1);
    EXPECT_FALSE(textFieldContentModifier.NeedMeasureUpdate(flag));

    /**
     * @tc.steps: step4. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of true.
     */
    textFieldContentModifier.fontWeightFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontWeightValue2);
    textFieldContentModifier.fontWeightFloat_->Set(fontWeightValue2);
    EXPECT_TRUE(textFieldContentModifier.NeedMeasureUpdate(flag));
}

/**
 * @tc.name: NeedMeasureUpdate004
 * @tc.desc: Verify that the NeedMeasureUpdate interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, NeedMeasureUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    PropertyChangeFlag flag;
    const Color color1 = Color::WHITE;
    const Color color2 = Color::RED;

    /**
     * @tc.steps: step2. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of false.
     */
    textFieldContentModifier.SetTextColor(color2);
    textFieldContentModifier.animatableTextColor_ = nullptr;
    EXPECT_FALSE(textFieldContentModifier.NeedMeasureUpdate(flag));

    /**
     * @tc.steps: step3. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of false.
     */
    textFieldContentModifier.animatableTextColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(color2));
    textFieldContentModifier.animatableTextColor_->Set(LinearColor(color2));
    EXPECT_FALSE(textFieldContentModifier.NeedMeasureUpdate(flag));

    /**
     * @tc.steps: step4. call NeedMeasureUpdate function.
     * @tc.expected: The NeedMeasureUpdate function returns a value of true.
     */
    textFieldContentModifier.animatableTextColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(color1));
    textFieldContentModifier.animatableTextColor_->Set(LinearColor(color1));
    EXPECT_TRUE(textFieldContentModifier.NeedMeasureUpdate(flag));
}

/**
 * @tc.name: SetFontSize
 * @tc.desc: Verify that the SetFontSize interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetFontSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    const Dimension fontSize = Dimension(5.0);

    /**
     * @tc.steps: step2. call SetFontSize function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    textFieldContentModifier.SetFontSize(fontSize);
    EXPECT_EQ(textFieldContentModifier.fontSize_, fontSize);
}

/**
 * @tc.name: UpdateContentModifier002
 * @tc.desc: Verify that the UpdateContentModifier interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateContentModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);

    /**
     * @tc.steps: step2. create textFieldOverlayModifier and textFieldContentModifier.
     */
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollBar, scrollEdgeEffect);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    textFieldContentModifier->contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    textFieldContentModifier->contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    textFieldContentModifier->textValue_ = AceType::MakeRefPtr<PropertyString>("");
    textFieldContentModifier->textRectY_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    textFieldContentModifier->textRectX_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    float fontSizeValue = 1.0;
    textFieldContentModifier->fontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    const Dimension fontSize = Dimension(5.0);
    textFieldContentModifier->SetFontSize(fontSize);
    textFieldContentModifier->fontSizeFloat_->Set(fontSizeValue);
    TextFieldPaintMethod textFieldPaintMethod(pattern, textFieldOverlayModifier, textFieldContentModifier);

    /**
     * @tc.steps: step3. create paintWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step4. call UpdateContentModifier function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    textFieldPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(textFieldContentModifier->contentOffset_->Get(), CONTENT_OFFSET);
}

/**
 * @tc.name: UpdateOverlayModifier002
 * @tc.desc: Verify that the UpdateOverlayModifier interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateOverlayModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollBar, scrollEdgeEffect);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    TextFieldPaintMethod textFieldPaintMethod(pattern, textFieldOverlayModifier, textFieldContentModifier);

    /**
     * @tc.steps: step2. create paintWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCursorWidth(CURSOR_WIDTH_SIZE);
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);

    /**
     * @tc.steps: step3. call UpdateOverlayModifier function.
     * @tc.expected: The member variable value of textFieldOverlayModifier is the value set above.
     */
    textFieldPaintMethod.UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(textFieldOverlayModifier->contentSize_->Get(), CONTENT_SIZE);
}

/**
 * @tc.name: SetFontWeight
 * @tc.desc: Verify that the SetFontWeight interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetFontWeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    const FontWeight fontWeight = FontWeight::W100;

    /**
     * @tc.steps: step2. call SetFontWeight function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    textFieldContentModifier.SetFontWeight(fontWeight);
    EXPECT_EQ(textFieldContentModifier.fontWeight_, fontWeight);
}

/**
 * @tc.name: SetTextColor
 * @tc.desc: Verify that the SetTextColor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    const Color color = Color::RED;

    /**
     * @tc.steps: step2. call SetTextColor function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    textFieldContentModifier.SetTextColor(color);
    EXPECT_EQ(textFieldContentModifier.textColor_.value(), color);
}

/**
 * @tc.name: ModifyTextStyle002
 * @tc.desc: Verify that the ModifyTextStyle interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ModifyTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    float fontSizeValue;
    textFieldContentModifier.fontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    const Dimension fontSize = Dimension(2.0);
    textFieldContentModifier.SetFontSize(fontSize);
    float fontWeightValue;
    textFieldContentModifier.fontWeightFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontWeightValue);
    const FontWeight fontWeight = FontWeight::W100;
    textFieldContentModifier.SetFontWeight(fontWeight);
    const Color color = Color::WHITE;
    textFieldContentModifier.animatableTextColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(color));
    textFieldContentModifier.SetTextColor(color);

    /**
     * @tc.steps: step2. call ModifyTextStyle function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    TextStyle textStyle;
    textFieldContentModifier.ModifyTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetFontSize().ConvertToPx(), fontSize.ConvertToPx());
    EXPECT_EQ(textStyle.GetFontWeight(), fontWeight);
    EXPECT_EQ(textStyle.GetTextColor(), color);
}

/**
 * @tc.name: ModifyTextStyle003
 * @tc.desc: Verify that the ModifyTextStyle interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ModifyTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    const Dimension fontSize = Dimension(2.0);
    textFieldContentModifier.SetFontSize(fontSize);
    textFieldContentModifier.fontSizeFloat_ = nullptr;
    const FontWeight fontWeight = FontWeight::W100;
    textFieldContentModifier.SetFontWeight(fontWeight);
    textFieldContentModifier.fontWeightFloat_ = nullptr;
    const Color color = Color::WHITE;
    textFieldContentModifier.SetTextColor(color);
    textFieldContentModifier.animatableTextColor_ = nullptr;

    /**
     * @tc.steps: step2. call ModifyTextStyle function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    TextStyle textStyle;
    textFieldContentModifier.ModifyTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetFontSize().ConvertToPx(), DEFAULT_FONT_SIZE.ConvertToPx());
}

/**
 * @tc.name: ModifyTextStyle004
 * @tc.desc: Verify that the ModifyTextStyle interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ModifyTextStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldContentModifier textFieldContentModifier(pattern);
    float fontSizeValue;
    textFieldContentModifier.fontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontSizeValue);
    float fontWeightValue;
    textFieldContentModifier.fontWeightFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(fontWeightValue);
    const Color color = Color::WHITE;
    textFieldContentModifier.animatableTextColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(color));

    /**
     * @tc.steps: step2. call ModifyTextStyle function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    TextStyle textStyle;
    textFieldContentModifier.ModifyTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetFontSize().ConvertToPx(), DEFAULT_FONT_SIZE.ConvertToPx());
}

/**
 * @tc.name: onDraw002
 * @tc.desc: Verify that the onDraw interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, onDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    textFieldContentModifier->contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    textFieldContentModifier->contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    textFieldContentModifier->textValue_ = AceType::MakeRefPtr<PropertyString>("");
    textFieldContentModifier->textRectY_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    textFieldContentModifier->textRectX_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    textFieldContentModifier->textObscured_ = AceType::MakeRefPtr<PropertyBool>(true);

    /**
     * @tc.steps: step2. call onDraw function.
     * @tc.expected: The onDraw interface calls normally and exits without exception.
     */
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    textFieldContentModifier->onDraw(context);
}

/**
 * @tc.name: onDraw003
 * @tc.desc: Verify that the onDraw interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, onDraw003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. paragraph_ Pointer instantiation.
     */
    pattern->paragraph_ = std::make_shared<RSParagraph>();
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);
    textFieldContentModifier->contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    textFieldContentModifier->contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    textFieldContentModifier->textValue_ = AceType::MakeRefPtr<PropertyString>("");
    textFieldContentModifier->textRectY_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    textFieldContentModifier->textRectX_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    textFieldContentModifier->textObscured_ = AceType::MakeRefPtr<PropertyBool>(true);

    /**
     * @tc.steps: step3. call onDraw function.
     * @tc.expected: The onDraw interface calls normally and exits without exception.
     */
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    textFieldContentModifier->onDraw(context);
}

/**
 * @tc.name: SetPropertyToModifier
 * @tc.desc: Verify that the SetPropertyToModifier interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetPropertyToModifier, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    TextFieldLayoutAlgorithm textFieldLayoutAlgorithm;
    TextStyle textStyle;
    const Color color = Color::RED;
    textStyle.SetTextColor(color);
    auto textFieldContentModifier = AceType::MakeRefPtr<TextFieldContentModifier>(pattern);

    /**
     * @tc.steps: step2. call SetPropertyToModifier function.
     * @tc.expected: The member variable value of textFieldContentModifier is the value set above.
     */
    textFieldLayoutAlgorithm.SetPropertyToModifier(textStyle, textFieldContentModifier);
    EXPECT_EQ(textFieldContentModifier->textColor_.value(), color);
}

/**
 * @tc.name: SetCaretStyle
 * @tc.desc: Create frameNode and SetCaretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetCaretStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFieldModelInstance.
     */
    TextFieldModelNG textFieldModelInstance;
    const CaretStyle value1 = {};
    textFieldModelInstance.SetCaretStyle(value1);
    const CaretStyle value2 = { CURSOR_WIDTH_SIZE };
    textFieldModelInstance.SetCaretStyle(value2);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. call GetCursorWidthValue function.
     * @tc.expected: The GetCursorWidthValue function returns the value set above.
     */
    EXPECT_EQ(paintProperty->GetCursorWidthValue(), CURSOR_WIDTH_SIZE);
}

/**
 * @tc.name: SetSelectedBackgroundColor
 * @tc.desc: Verify that the SetSelectedBackgroundColor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetSelectedBackgroundColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFieldModelInstance.
     */
    TextFieldModelNG textFieldModelInstance;
    const Color value = Color::BLACK;
    textFieldModelInstance.SetSelectedBackgroundColor(value);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. call GetSelectedBackgroundColor function.
     * @tc.expected: The GetSelectedBackgroundColor function returns the value set above.
     */
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), value);
}

/**
 * @tc.name: OnScrollCallback002
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, OnScrollCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFieldPattern.
     */
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    const float offset = 0.0;
    const int32_t source = 0;
    bool ret = false;
    textFieldPattern->scrollBar_ = AccessibilityManager::MakeRefPtr<ScrollBar>();
    textFieldPattern->scrollBar_->SetDriving(true);

    /**
     * @tc.steps: step2. call OnScrollCallback function.
     * @tc.expected: The OnScrollCallback function returns a value of true.
     */
    ret = textFieldPattern->OnScrollCallback(offset, source);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnScrollCallback003
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, OnScrollCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFieldPattern.
     */
    auto textFieldPattern = GetPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    const float offset = 0.0;
    const int32_t source = 0;
    bool ret = false;
    textFieldPattern->scrollBar_ = AccessibilityManager::MakeRefPtr<ScrollBar>();
    textFieldPattern->scrollBar_->SetDriving(false);

    /**
     * @tc.steps: step2. call OnScrollCallback function.
     * @tc.expected: The OnScrollCallback function returns a value of true.
     */
    ret = textFieldPattern->OnScrollCallback(offset, source);
    EXPECT_TRUE(ret);
}
} // namespace OHOS::Ace::NG
