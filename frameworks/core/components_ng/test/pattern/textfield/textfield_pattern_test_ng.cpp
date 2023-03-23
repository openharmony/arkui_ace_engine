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
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
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
const int32_t DELETE_LENGTH_1 = 1;
const int32_t CARET_POSITION = 0;
const Dimension CURSOR_WIDTH_SIZE = 10.0_vp;
const Dimension DEFAULT_FONT_SIZE { 14, DimensionUnit::PX };
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr float CONTEXT_WIDTH_VALUE = 10.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 10.0f;
const std::string EMPTY_TEXT_VALUE;
const std::string TEXT_EDITING_VALUE("textEditingValue");
constexpr int32_t ONECE_MOVE_POS = 1;
const std::string PLACEHOLDER = "DEFAULT PLACEHOLDER";
} // namespace
class TextFieldPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> GetFrameNode();
    RefPtr<TextFieldPattern> GetTextFieldPattern();
    RefPtr<TextFieldLayoutProperty> GetLayoutPropertyFromHost(const RefPtr<TextFieldPattern>& pattern);
    RefPtr<TextFieldLayoutProperty> CreateNodeAndGetLayoutProperty(TextFieldModelNG& textFieldModelInstance);
    RefPtr<TextFieldPaintProperty> CreateNodeAndGetPaintProperty(TextFieldModelNG& textFieldModelInstance);
    RefPtr<TextFieldLayoutProperty> GetTextFieldLayoutProperty();
    void CreatOnTextChangedListenerImplInstance();
    RefPtr<FrameNode> CreatTextFieldNode(const std::optional<std::string>& placeholder = PLACEHOLDER,
        const std::optional<std::string>& value = EMPTY_TEXT_VALUE, bool isTextArea = false);

    std::shared_ptr<OnTextChangedListenerImpl> textChangedListenerImpl_;
    RefPtr<FrameNode> host_;
};

void TextFieldPatternTestNg::SetUp()
{
    CreatOnTextChangedListenerImplInstance();
}

void TextFieldPatternTestNg::TearDown()
{
    host_ = nullptr;
    textChangedListenerImpl_ = nullptr;
    ViewStackProcessor::GetInstance()->Finish();
}

RefPtr<FrameNode> TextFieldPatternTestNg::CreatTextFieldNode(
    const std::optional<std::string>& placeholder, const std::optional<std::string>& value, bool isTextArea)
{
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateNode(placeholder, value, isTextArea);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

void TextFieldPatternTestNg::CreatOnTextChangedListenerImplInstance()
{
    host_ = CreatTextFieldNode();
    if (!host_) {
        GTEST_LOG_(INFO) << "create textfield node failed!";
        return;
    }
    auto pattern = host_->GetPattern<TextFieldPattern>();
    if (!pattern) {
        GTEST_LOG_(INFO) << "Get TextFieldPattern failed!";
        return;
    }
    WeakPtr<TextFieldPattern> textFieldPattern(pattern);
    textChangedListenerImpl_ = std::make_shared<OnTextChangedListenerImpl>(textFieldPattern);
}

RefPtr<TextFieldLayoutProperty> TextFieldPatternTestNg::CreateNodeAndGetLayoutProperty(
    TextFieldModelNG& textFieldModelInstance)
{
    textFieldModelInstance.CreateNode(PLACEHOLDER, EMPTY_TEXT_VALUE, false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!frameNode) {
        GTEST_LOG_(INFO) << "create textfield node failed!";
        return nullptr;
    }
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    return layoutProperty;
}

RefPtr<TextFieldPaintProperty> TextFieldPatternTestNg::CreateNodeAndGetPaintProperty(
    TextFieldModelNG& textFieldModelInstance)
{
    textFieldModelInstance.CreateNode(PLACEHOLDER, EMPTY_TEXT_VALUE, false);
    auto frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!frameNode_) {
        GTEST_LOG_(INFO) << "create textfield node failed!";
        return nullptr;
    }
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    return paintProperty;
}

RefPtr<TextFieldLayoutProperty> TextFieldPatternTestNg::GetTextFieldLayoutProperty()
{
    host_ = CreatTextFieldNode();
    return host_ ? host_->GetLayoutProperty<TextFieldLayoutProperty>() : nullptr;
}

RefPtr<TextFieldPattern> TextFieldPatternTestNg::GetTextFieldPattern()
{
    host_ = CreatTextFieldNode();
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

RefPtr<FrameNode> TextFieldPatternTestNg::GetFrameNode()
{
    TextFieldModelNG textFieldModelNG;
    const std::string placeholder = "DEFAULT PLACEHOLDER";
    const std::string value;
    bool isTextArea = false;
    textFieldModelNG.CreateNode(placeholder, value, isTextArea);
    textFieldModelNG.SetCaretPosition(CARET_POSITION);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
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

/**
 * @tc.name: UpdateCaretPosition001
 * @tc.desc: test UpdateCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretPosition001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    host_->GetOrCreateFocusHub()->currentFocus_ = true;
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
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    host_->GetOrCreateFocusHub()->currentFocus_ = true;
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::PRESSED);
    EXPECT_FALSE(textFieldPattern->UpdateCaretPosition());
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::LONG_PRESSED);
    EXPECT_FALSE(textFieldPattern->UpdateCaretPosition());
}

/**
 * @tc.name: UpdateCaretPosition003
 * @tc.desc: test UpdateCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretPosition003, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    host_->GetOrCreateFocusHub()->currentFocus_ = true;
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::NONE);
    EXPECT_TRUE(textFieldPattern->UpdateCaretPosition());
    textFieldPattern->SetCaretUpdateType(CaretUpdateType::NONE);
    EXPECT_TRUE(textFieldPattern->UpdateCaretPosition());
}

/**
 * @tc.name: UpdateCaretPosition005
 * @tc.desc: test UpdateCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretPosition005, TestSize.Level2)
{
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    EXPECT_TRUE(textFieldPattern->UpdateCaretPosition());
    host_->GetOrCreateFocusHub()->currentFocus_ = true;
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
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    textFieldPattern->isMousePressed_ = true;
    textFieldPattern->UpdateEditingValue(TEXT_VALUE, static_cast<int32_t>(TEXT_VALUE.size()));
    textFieldPattern->UpdateDestinationToCaretByEvent();
    EXPECT_EQ(textFieldPattern->GetSelectMode(), SelectionMode::SELECT);
}

/**
 * @tc.name: UpdateCaretOffsetByLastTouchOffset001
 * @tc.desc: test UpdateCaretOffsetByLastTouchOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretOffsetByLastTouchOffset001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
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
    EXPECT_EQ(textFieldPattern->GetTextEditingValue().caretPosition, TEXT_VALUE.length());
    EXPECT_EQ(textFieldPattern->GetCaretOffsetX(), textSize.Width());
}

/**
 * @tc.name: UpdateCaretOffsetByLastTouchOffset002
 * @tc.desc: test UpdateCaretOffsetByLastTouchOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretOffsetByLastTouchOffset002, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
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
    EXPECT_EQ(textFieldPattern->GetCaretOffsetX(), textOffset.GetX());
}

/**
 * @tc.name: UpdateCaretOffsetByLastTouchOffset003
 * @tc.desc: test UpdateCaretOffsetByLastTouchOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCaretOffsetByLastTouchOffset003, TestSize.Level2)
{
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
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
 * @tc.name: GetPipelineContext001
 * @tc.desc: Verify that the GetPipelineContext interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetPipelineContext001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    EXPECT_EQ(textFieldContentModifier.GetPipelineContext(), nullptr);
}

/**
 * @tc.name: SetDefaultAnimatablePropertyValue001
 * @tc.desc: Verify that the SetDefaultAnimatablePropertyValue interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetDefaultAnimatablePropertyValue001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.SetDefaultAnimatablePropertyValue();
    EXPECT_EQ(textFieldContentModifier.fontSizeFloat_, nullptr);
}

/**
 * @tc.name: SetDefaultFontSize001
 * @tc.desc: Verify that the SetDefaultFontSize interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetDefaultFontSize001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    const TextStyle textStyle;
    EXPECT_EQ(textFieldContentModifier.fontSizeFloat_, nullptr);
    textFieldContentModifier.SetDefaultFontSize(textStyle);
    EXPECT_NE(textFieldContentModifier.fontSizeFloat_, nullptr);
}

/**
 * @tc.name: SetDefaultFontWeight001
 * @tc.desc: Verify that the SetDefaultFontWeight interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetDefaultFontWeight001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    const TextStyle textStyle;
    EXPECT_EQ(textFieldContentModifier.fontWeightFloat_, nullptr);
    textFieldContentModifier.SetDefaultFontWeight(textStyle);
    EXPECT_NE(textFieldContentModifier.fontWeightFloat_, nullptr);
}

/**
 * @tc.name: SetDefaultTextColor001
 * @tc.desc: Verify that the SetDefaultTextColor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetDefaultTextColor001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    const TextStyle textStyle;
    EXPECT_EQ(textFieldContentModifier.animatableTextColor_, nullptr);
    textFieldContentModifier.SetDefaultTextColor(textStyle);
    EXPECT_NE(textFieldContentModifier.animatableTextColor_, nullptr);
}

/**
 * @tc.name: ModifyTextStyle001
 * @tc.desc: Verify that the ModifyTextStyle interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ModifyTextStyle001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    TextStyle textStyle;
    textFieldContentModifier.ModifyTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetFontSize().ConvertToPx(), DEFAULT_FONT_SIZE.ConvertToPx());
}

/**
 * @tc.name: SetFontSize001
 * @tc.desc: Verify that the SetFontSize interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetFontSize001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    const Dimension fontSize = Dimension(5.0);
    textFieldContentModifier.SetFontSize(fontSize);
    EXPECT_EQ(textFieldContentModifier.fontSize_, fontSize);
}

/**
 * @tc.name: SetFontWeight001
 * @tc.desc: Verify that the SetFontWeight interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetFontWeight001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    const FontWeight fontWeight = FontWeight::W100;
    textFieldContentModifier.SetFontWeight(fontWeight);
    EXPECT_EQ(textFieldContentModifier.fontWeight_, fontWeight);
}

/**
 * @tc.name: SetTextColor001
 * @tc.desc: Verify that the SetTextColor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextColor001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    const Color color = Color::RED;
    textFieldContentModifier.SetTextColor(color);
    EXPECT_EQ(textFieldContentModifier.textColor_.value(), color);
}

/**
 * @tc.name: NeedMeasureUpdate001
 * @tc.desc: Verify that the NeedMeasureUpdate interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, NeedMeasureUpdate001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    PropertyChangeFlag flag;
    bool ret = true;
    ret = textFieldContentModifier.NeedMeasureUpdate(flag);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetCursorColor001
 * @tc.desc: Verify that the SetCursorColor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetCursorColor001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Color value = Color::WHITE;
    textFieldOverlayModifier.SetCursorColor(value);
    EXPECT_EQ(textFieldOverlayModifier.cursorColor_->Get(), LinearColor(value));
}

/**
 * @tc.name: SetCursortWidth001
 * @tc.desc: Verify that the SetCursorWidth interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetCursortWidth001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    float value = 1.0;
    textFieldOverlayModifier.SetCursorWidth(value);
    EXPECT_EQ(textFieldOverlayModifier.cursorWidth_->Get(), value);
}

/**
 * @tc.name: SetSelectedBackGroundColor001
 * @tc.desc: Verify that the SetSelectedBackGroundColor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetSelectedBackGroundColor001, TestSize.Level1)
{
    auto pattern = GetTextFieldPattern();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Color value = Color::BLACK;
    textFieldOverlayModifier.SetSelectedBackGroundColor(value);
    EXPECT_EQ(textFieldOverlayModifier.selectedColor_->Get(), LinearColor(value));
}

/**
 * @tc.name: SetCursorVisible001
 * @tc.desc: Verify that the SetCursorVisible interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetCursorVisible001, TestSize.Level1)
{
    auto pattern = GetTextFieldPattern();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    bool value = true;
    textFieldOverlayModifier.SetCursorVisible(value);
    EXPECT_EQ(textFieldOverlayModifier.cursorVisible_->Get(), value);
}

/**
 * @tc.name: SetContentSize001
 * @tc.desc: Verify that the SetContentSize interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetContentSize001, TestSize.Level1)
{
    auto pattern = GetTextFieldPattern();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    SizeF value;
    textFieldOverlayModifier.SetContentSize(value);
    EXPECT_EQ(textFieldOverlayModifier.contentSize_->Get(), value);
}

/**
 * @tc.name: SetContentOffset001
 * @tc.desc: Verify that the SetContentOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetContentOffset001, TestSize.Level1)
{
    auto pattern = GetTextFieldPattern();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    OffsetF value;
    textFieldOverlayModifier.SetContentOffset(value);
    EXPECT_EQ(textFieldOverlayModifier.contentOffset_->Get(), value);
}

/**
 * @tc.name: SetCursorOffsetX001
 * @tc.desc: Verify that the SetCursorOffsetX interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetCursorOffsetX001, TestSize.Level1)
{
    auto pattern = GetTextFieldPattern();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    float value = 1.0;
    textFieldOverlayModifier.SetCursorOffsetX(value);
    EXPECT_EQ(textFieldOverlayModifier.cursorOffsetX_->Get(), value);
}

/**
 * @tc.name: SetInputStyle001
 * @tc.desc: Verify that the SetInputStyle interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetInputStyle001, TestSize.Level1)
{
    auto pattern = GetTextFieldPattern();
    ASSERT_NE(pattern, nullptr);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    InputStyle value = InputStyle::INLINE;
    textFieldOverlayModifier.SetInputStyle(value);
    EXPECT_EQ(textFieldOverlayModifier.inputStyle_, InputStyle::INLINE);
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Verify that the UpdateCurrentOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    const float offset = 0.0;
    const int32_t source = 0;
    bool ret = false;
    ret = textFieldPattern->UpdateCurrentOffset(offset, source);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: IsAtTop001
 * @tc.desc: Verify that the IsAtTop interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, IsAtTop001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    bool ret = false;
    ret = textFieldPattern->IsAtTop();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: IsAtBottom001
 * @tc.desc: Verify that the IsAtBottom interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, IsAtBottom001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
    bool ret = false;
    ret = textFieldPattern->IsAtBottom();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, OnScrollCallback001, TestSize.Level1)
{
    auto textFieldPattern = GetTextFieldPattern();
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
    auto textFieldPattern = GetTextFieldPattern();
    ASSERT_NE(textFieldPattern, nullptr);
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
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
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
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
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
    auto textFieldPattern = GetTextFieldPattern();
    if (!textFieldPattern) {
        EXPECT_FALSE(textFieldPattern == nullptr);
        return;
    }
    textFieldPattern->textEditingValue_.text = "checkScrollable";
    textFieldPattern->textRect_.SetHeight(0.0);
    textFieldPattern->contentRect_.SetHeight(1.0);
    EXPECT_TRUE(textFieldPattern->scrollable_);
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
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    OffsetF value = CONTENT_OFFSET;
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    SizeF value = CONTENT_SIZE;
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.textValue_ = AceType::MakeRefPtr<PropertyString>("");
    std::string value = "text";
    textFieldContentModifier.SetTextValue(value);
    EXPECT_EQ(textFieldContentModifier.textValue_->Get(), value);
}

/**
 * @tc.name: SetTextRectY001
 * @tc.desc: Verify that the SetTextRectY interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextRectY001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.textRectY_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    const float value = 1.0;
    textFieldContentModifier.SetTextRectY(value);
    EXPECT_EQ(textFieldContentModifier.textRectY_->Get(), value);
}

/**
 * @tc.name: UpdateScrollBarOffset001
 * @tc.desc: Verify that the UpdateScrollBarOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateScrollBarOffset001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->UpdateScrollBarOffset();
    EXPECT_EQ(pattern->textEditingValue_.text, "");
}

/**
 * @tc.name: UpdateScrollBarOffset002
 * @tc.desc: Verify that the UpdateScrollBarOffset interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, UpdateScrollBarOffset002, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->textEditingValue_.text = "updateScrollBarOffset";
    pattern->UpdateScrollBarOffset();
    EXPECT_EQ(pattern->GetScrollBar(), nullptr);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Verify that the onDraw interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, onDraw001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
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
 * @tc.name: PaintCursor001
 * @tc.desc: Verify that the PaintCursor interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, PaintCursor001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    TextFieldOverlayModifier textFieldOverlayModifier(pattern, scrollBar, scrollEdgeEffect);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldOverlayModifier.PaintCursor(context);
}

/**
 * @tc.name: SetTextRectX001
 * @tc.desc: Verify that the SetTextRectX interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetTextRectX001, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldContentModifier textFieldContentModifier(pattern);
    textFieldContentModifier.textRectX_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    const float value = 1.0;
    textFieldContentModifier.SetTextRectX(value);
    EXPECT_EQ(textFieldContentModifier.textRectX_->Get(), value);
}

/**
 * @tc.name: CreateNode001
 * @tc.desc: Create frameNode of empty value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CreateNode001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    textFieldModelInstance.CreateNode(PLACEHOLDER, EMPTY_TEXT_VALUE, false);
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

/**
 * @tc.name: CreateNode002
 * @tc.desc: Create frameNode of value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CreateNode002, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    textFieldModelInstance.CreateNode(PLACEHOLDER, "value", false);
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

/**
 * @tc.name: CreateTextInput001
 * @tc.desc: Create frameNode of empty value about textinput
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CreateTextInput001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto controller = textFieldModelInstance.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    EXPECT_TRUE(controller);
}

/**
 * @tc.name: CreateTextArea001
 * @tc.desc: Create frameNode of empty value about textarea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CreateTextArea001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto controller = textFieldModelInstance.CreateTextArea(PLACEHOLDER, EMPTY_TEXT_VALUE);
    EXPECT_TRUE(controller);
}

/**
 * @tc.name: SetType001
 * @tc.desc: Create frameNode and settype
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetType001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    textFieldModelInstance.SetType(TextInputType::TEXT);
    EXPECT_EQ(layoutProperty->GetTextInputTypeValue(), TextInputType::TEXT);
    textFieldModelInstance.SetType(TextInputType::MULTILINE);
    EXPECT_EQ(layoutProperty->GetTextInputTypeValue(), TextInputType::MULTILINE);
    EXPECT_TRUE(layoutProperty->GetTypeChangedValue());
}

/**
 * @tc.name: SetPlaceholderColor001
 * @tc.desc: Create frameNode and PlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetPlaceholderColor001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    textFieldModelInstance.SetPlaceholderColor(Color::WHITE);
    EXPECT_TRUE(layoutProperty->HasPlaceholderTextColor());
}

/**
 * @tc.name: SetPlaceholderFont001
 * @tc.desc: Create frameNode and SetPlaceholderFont
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetPlaceholderFont001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    std::vector<std::string> fontFamilies;
    fontFamilies.push_back("fontFamilies");
    Font font { .fontWeight = Ace::FontWeight::W200,
        .fontSize = Dimension(10.0),
        .fontStyle = Ace::FontStyle::NORMAL,
        .fontFamilies = fontFamilies };
    textFieldModelInstance.SetPlaceholderFont(font);
    EXPECT_EQ(layoutProperty->GetPlaceholderFontSize().value().Value(), 10.0);
    EXPECT_EQ(layoutProperty->GetPlaceholderItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    EXPECT_EQ(layoutProperty->GetPlaceholderFontWeight().value(), Ace::FontWeight::W200);
    EXPECT_EQ(layoutProperty->GetPlaceholderFontFamily().value().size(), fontFamilies.size());
    EXPECT_TRUE(layoutProperty->GetPreferredTextLineHeightNeedToUpdate().value());
}

/**
 * @tc.name: SetEnterKeyType001
 * @tc.desc: Create frameNode and SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetEnterKeyType001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    textFieldModelInstance.SetEnterKeyType(TextInputAction::GO);
    auto textFieldPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    EXPECT_TRUE(textFieldPattern);
}

/**
 * @tc.name: SetOnEditChanged001
 * @tc.desc: Create frameNode and SetOnEditChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetOnEditChanged001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    bool callback = false;
    textFieldModelInstance.SetOnEditChanged([&callback](bool info) { callback = info; });
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    if (!eventHub) {
        EXPECT_TRUE(eventHub);
        return;
    }
    eventHub->FireOnEditChanged(true);
    EXPECT_TRUE(callback);
}

/**
 * @tc.name: TextInputType001
 * @tc.desc: Update TextInputType layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextInputType001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasTextInputType());
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::MULTILINE);
    EXPECT_TRUE(textFieldLayoutProperty->HasTextInputType());
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputTypeValue(), TextInputType::MULTILINE);

    textFieldLayoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    EXPECT_TRUE(textFieldLayoutProperty->HasTextInputType());
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputTypeValue(), TextInputType::EMAIL_ADDRESS);
}

/**
 * @tc.name: TypeChanged001
 * @tc.desc: Update TypeChanged layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TypeChanged001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasTypeChanged());
    textFieldLayoutProperty->UpdateTypeChanged(true);
    EXPECT_TRUE(textFieldLayoutProperty->HasTypeChanged());
    EXPECT_TRUE(textFieldLayoutProperty->GetTypeChangedValue());

    textFieldLayoutProperty->UpdateTypeChanged(false);
    EXPECT_TRUE(textFieldLayoutProperty->HasTypeChanged());
    EXPECT_FALSE(textFieldLayoutProperty->GetTypeChangedValue());
}

/**
 * @tc.name: PlaceholderTextColor001
 * @tc.desc: Update PlaceholderTextColor layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, PlaceholderTextColor001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderTextColor());
    textFieldLayoutProperty->UpdatePlaceholderTextColor(Color::RED);
    EXPECT_TRUE(textFieldLayoutProperty->HasPlaceholderTextColor());
}

/**
 * @tc.name: Font001
 * @tc.desc: Update Font structure layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, Font001, TestSize.Level1)
{
    std::vector<std::string> fontFamilies;
    Font font { .fontWeight = Ace::FontWeight::W200,
        .fontSize = Dimension(10.0),
        .fontStyle = Ace::FontStyle::NORMAL,
        .fontFamilies = fontFamilies };
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderFontSize());
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderItalicFontStyle());
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderFontWeight());
    EXPECT_FALSE(textFieldLayoutProperty->HasPlaceholderFontFamily());

    textFieldLayoutProperty->UpdatePlaceholderFontSize(font.fontSize.value());
    if (textFieldLayoutProperty->HasPlaceholderFontSize()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontSize().value().Value(), 10.0);
    }

    textFieldLayoutProperty->UpdatePlaceholderItalicFontStyle(font.fontStyle.value());
    if (textFieldLayoutProperty->HasPlaceholderItalicFontStyle()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    }

    textFieldLayoutProperty->UpdatePlaceholderFontWeight(font.fontWeight.value());
    if (textFieldLayoutProperty->HasPlaceholderFontWeight()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontWeight().value(), Ace::FontWeight::W200);
    }

    textFieldLayoutProperty->UpdatePlaceholderFontFamily(font.fontFamilies);
    if (textFieldLayoutProperty->HasPlaceholderFontFamily()) {
        EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontFamily().value().size(), fontFamilies.size());
    }
}

/**
 * @tc.name: TextAlign001
 * @tc.desc: Update TextAlign layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextAlign001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }

    EXPECT_FALSE(textFieldLayoutProperty->HasTextAlign());
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    if (textFieldLayoutProperty->HasTextAlign()) {
        EXPECT_EQ(textFieldLayoutProperty->GetTextAlign().value(), TextAlign::CENTER);
    }
}

/**
 * @tc.name: MaxLength001
 * @tc.desc: Update MaxLength layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, MaxLength001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    uint32_t length = 32;
    EXPECT_FALSE(textFieldLayoutProperty->HasMaxLength());
    textFieldLayoutProperty->UpdateMaxLength(length);
    if (textFieldLayoutProperty->HasMaxLength()) {
        EXPECT_EQ(textFieldLayoutProperty->GetMaxLength().value(), length);
    }
}

/**
 * @tc.name: MaxLines001
 * @tc.desc: Update MaxLines layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, MaxLines001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    uint32_t lines = 32;
    textFieldLayoutProperty->UpdateMaxLines(lines);
    if (textFieldLayoutProperty->HasMaxLines()) {
        EXPECT_EQ(textFieldLayoutProperty->GetMaxLines().value(), lines);
    }
}

/**
 * @tc.name: FontSize001
 * @tc.desc: Update FontSize layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, FontSize001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasFontSize());
    textFieldLayoutProperty->UpdateFontSize(Dimension(10.0));
    if (textFieldLayoutProperty->HasFontSize()) {
        EXPECT_EQ(textFieldLayoutProperty->GetFontSize().value().Value(), 10.0);
    }
}

/**
 * @tc.name: PreferredTextLineHeightNeedToUpdate001
 * @tc.desc: Update PreferredTextLineHeightNeedToUpdate layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, PreferredTextLineHeightNeedToUpdate001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasPreferredTextLineHeightNeedToUpdate());
    textFieldLayoutProperty->UpdatePreferredTextLineHeightNeedToUpdate(true);
    if (textFieldLayoutProperty->HasPreferredTextLineHeightNeedToUpdate()) {
        EXPECT_TRUE(textFieldLayoutProperty->GetPreferredTextLineHeightNeedToUpdate().value());
    }
}

/**
 * @tc.name: TextColor001
 * @tc.desc: Update TextColor layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, TextColor001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasTextColor());
    textFieldLayoutProperty->UpdateTextColor(Color::RED);
    if (textFieldLayoutProperty->HasTextColor()) {
        EXPECT_EQ(textFieldLayoutProperty->GetTextColor().value(), Color::RED);
    }
}

/**
 * @tc.name: ItalicFontStyle001
 * @tc.desc: Update ItalicFontStyle layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ItalicFontStyle001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasItalicFontStyle());
    textFieldLayoutProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    if (textFieldLayoutProperty->HasItalicFontStyle()) {
        EXPECT_EQ(textFieldLayoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    }
}

/**
 * @tc.name: FontFamily001
 * @tc.desc: Update FontFamily layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, FontFamily001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    std::vector<std::string> fontFamilies;
    EXPECT_FALSE(textFieldLayoutProperty->HasFontFamily());
    textFieldLayoutProperty->UpdateFontFamily(fontFamilies);
    if (textFieldLayoutProperty->HasFontFamily()) {
        EXPECT_EQ(textFieldLayoutProperty->GetFontFamily().value().size(), fontFamilies.size());
    }
}

/**
 * @tc.name: InputFilter001
 * @tc.desc: Update InputFilter layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, InputFilter001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    std::string filterTest = "filterTest";
    EXPECT_FALSE(textFieldLayoutProperty->HasInputFilter());
    textFieldLayoutProperty->UpdateInputFilter(filterTest);
    if (textFieldLayoutProperty->HasInputFilter()) {
        EXPECT_EQ(textFieldLayoutProperty->GetInputFilterValue(), filterTest);
    }
}

/**
 * @tc.name: ShowPasswordIcon001
 * @tc.desc: Update ShowPasswordIcon layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ShowPasswordIcon001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasShowPasswordIcon());
    textFieldLayoutProperty->UpdateShowPasswordIcon(true);
    if (textFieldLayoutProperty->HasShowPasswordIcon()) {
        EXPECT_TRUE(textFieldLayoutProperty->GetShowPasswordIcon().value());
    }
}

/**
 * @tc.name: CopyOptions001
 * @tc.desc: Update CopyOptions layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CopyOptions001, TestSize.Level1)
{
    auto textFieldLayoutProperty = GetTextFieldLayoutProperty();
    EXPECT_TRUE(textFieldLayoutProperty);
    if (!textFieldLayoutProperty) {
        return;
    }
    EXPECT_FALSE(textFieldLayoutProperty->HasCopyOptions());
    textFieldLayoutProperty->UpdateCopyOptions(CopyOptions::Local);
    if (textFieldLayoutProperty->HasCopyOptions()) {
        EXPECT_EQ(textFieldLayoutProperty->GetCopyOptions().value(), CopyOptions::Local);
    }
}

/**
 * @tc.name: GetWideText001
 * @tc.desc: test GetWideText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetWideText001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(StringUtils::ToString(textEditingStructure.GetWideText()), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    EXPECT_EQ(StringUtils::ToString(textEditingStructure.GetWideText()), TEXT_EDITING_VALUE);
}

/**
 * @tc.name: CursorMoveLeft001
 * @tc.desc: test CursorMoveLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CursorMoveLeft001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    textEditingStructure.CursorMoveLeft();
    EXPECT_EQ(textEditingStructure.caretPosition, 0);
    textEditingStructure.caretPosition = textLength;
    textEditingStructure.CursorMoveLeft();
    EXPECT_EQ(textEditingStructure.caretPosition, textLength - ONECE_MOVE_POS);
}

/**
 * @tc.name: CursorMoveRight001
 * @tc.desc: test CursorMoveRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CursorMoveRight001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.caretPosition, ONECE_MOVE_POS);
    textEditingStructure.caretPosition = textLength;
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.caretPosition, textLength);
}

/**
 * @tc.name: CursorMoveToPosition001
 * @tc.desc: test CursorMoveToPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, CursorMoveToPosition001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    textEditingStructure.CursorMoveToPosition(-1);
    EXPECT_EQ(textEditingStructure.caretPosition, 0);
    textEditingStructure.CursorMoveToPosition(textLength + ONECE_MOVE_POS);
    EXPECT_EQ(textEditingStructure.caretPosition, textLength);
    textEditingStructure.CursorMoveToPosition(textLength - ONECE_MOVE_POS);
    EXPECT_EQ(textEditingStructure.caretPosition, textLength - ONECE_MOVE_POS);
}

/**
 * @tc.name: GetValueBeforeCursor_GetValueAfterCursor001
 * @tc.desc: test GetValueBeforeCursor and GetValueAfterCursor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetValueBeforeCursor_GetValueAfterCursor001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(textEditingStructure.GetValueBeforeCursor(), EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.GetValueAfterCursor(), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.GetValueBeforeCursor(), "t");
    EXPECT_EQ(textEditingStructure.GetValueAfterCursor(), "extEditingValue");
}

/**
 * @tc.name: GetValueBeforePosition_GetValueAfterPosition001
 * @tc.desc: test GetValueBeforePosition and GetValueAfterPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetValueBeforePosition_GetValueAfterPosition001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(textEditingStructure.GetValueBeforePosition(ONECE_MOVE_POS), EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.GetValueAfterPosition(ONECE_MOVE_POS), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    EXPECT_EQ(textEditingStructure.GetValueBeforePosition(ONECE_MOVE_POS), "t");
    EXPECT_EQ(textEditingStructure.GetValueAfterPosition(ONECE_MOVE_POS), "extEditingValue");
}

/**
 * @tc.name: GetSelectedText001
 * @tc.desc: test GetSelectedText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, GetSelectedText001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    EXPECT_EQ(textEditingStructure.GetSelectedText(ONECE_MOVE_POS, ONECE_MOVE_POS * 2), EMPTY_TEXT_VALUE);
    textEditingStructure.text = TEXT_EDITING_VALUE;
    auto textLength = static_cast<int32_t>(textEditingStructure.text.size());
    EXPECT_GT(textLength, 0);
    EXPECT_EQ(textEditingStructure.GetSelectedText(textLength, 0), EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.GetSelectedText(0, textLength), "textEditingValue");
}

/**
 * @tc.name: ToString001
 * @tc.desc: test ToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, ToString001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    textEditingStructure.CursorMoveRight();
    EXPECT_EQ(textEditingStructure.ToString(), "t|extEditingValue");
}

/**
 * @tc.name: Reset001
 * @tc.desc: test Reset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, Reset001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure;
    textEditingStructure.text = TEXT_EDITING_VALUE;
    textEditingStructure.CursorMoveRight();
    textEditingStructure.Reset();
    EXPECT_EQ(textEditingStructure.text, EMPTY_TEXT_VALUE);
    EXPECT_EQ(textEditingStructure.caretPosition, 0);
}

/**
 * @tc.name: operator001
 * @tc.desc: test operator
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, operator001, TestSize.Level1)
{
    struct TextEditingValueNG textEditingStructure1;
    struct TextEditingValueNG textEditingStructure2;
    textEditingStructure1.text = TEXT_EDITING_VALUE;
    textEditingStructure1.caretPosition = 1;
    textEditingStructure2.text = TEXT_EDITING_VALUE;
    textEditingStructure2.caretPosition = 2;
    EXPECT_EQ(textEditingStructure1, textEditingStructure2);
}

/**
 * @tc.name: InsertText001
 * @tc.desc: Test insert Text Field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, InsertText001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    const std::string default_text = "X";
    textChangedListenerImpl_->InsertText(to_utf16(default_text));
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: InsertText002
 * @tc.desc: Test to insert an empty text field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, InsertText002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    std::string emptyString;
    textChangedListenerImpl_->InsertText(to_utf16(emptyString));
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteBackward001
 * @tc.desc: Test to delete 8 length text fields backward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, DeleteBackward001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t length = 8;
    textChangedListenerImpl_->DeleteBackward(length);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteBackward002
 * @tc.desc: Test to delete a text field with illegal length backwards
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, DeleteBackward002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t errLength = -1;
    textChangedListenerImpl_->DeleteBackward(errLength);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteForward001
 * @tc.desc: Test to delete a text field with a length of 8 forward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, DeleteForward001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t length = 8;
    textChangedListenerImpl_->DeleteForward(length);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteForward002
 * @tc.desc: Test to delete the text field with illegal length forward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, DeleteForward002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t errLength = -1;
    textChangedListenerImpl_->DeleteForward(errLength);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: SetKeyboardStatus001
 * @tc.desc: test set KeyboardStatus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SetKeyboardStatus001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->SetKeyboardStatus(true);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: SendKeyboardInfo001
 * @tc.desc: Test the valid FunctionKey parameter of send
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SendKeyboardInfo001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    MiscServices::KeyboardInfo info;
    int32_t index = 1;
    info.SetFunctionKey(index);
    textChangedListenerImpl_->SendKeyboardInfo(info);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: SendKeyboardInfo002
 * @tc.desc: Test the invalid FunctionKey parameter of send
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, SendKeyboardInfo002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    MiscServices::KeyboardInfo info;
    int32_t index = -1;
    info.SetFunctionKey(index);
    textChangedListenerImpl_->SendKeyboardInfo(info);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor001
 * @tc.desc: Test moving the cursor up
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, MoveCursor001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::UP);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor002
 * @tc.desc: Test moving the cursor up
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, MoveCursor002, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::DOWN);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor003
 * @tc.desc: Test moving the cursor left
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, MoveCursor003, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::LEFT);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor004
 * @tc.desc: Test moving the cursor right
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNg, MoveCursor004, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::RIGHT);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}
} // namespace OHOS::Ace::NG
