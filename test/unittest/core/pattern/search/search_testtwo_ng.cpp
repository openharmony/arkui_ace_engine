/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <string>

#include "gtest/gtest.h"
#include "search_base.h"

namespace OHOS::Ace::NG {

namespace {
const std::string INSPECTOR_PREFIX = "__SearchField__";
const std::vector<std::string> SPECIALIZED_INSPECTOR_INDEX = { "", "Image__", "CancelImage__", "CancelButton__",
    "Button__" };
} // namespace

class SearchTestTwoNg : public SearchBases {
public:
};

/**
 * @tc.name: testOnEditChange001
 * @tc.desc: Test Search OnEditChange
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, testOnEditChange001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    textFieldEventHub->SetOnEditChanged([](bool isChanged) {
        isChanged = true;
    });
    /**
     * @tc.expected: Check if the text patterns for the input box are compliant
     */
    EXPECT_EQ(textFieldPattern->GetTextValue().compare(DEFAULT_TEXT), 0);
}

/**
 * @tc.name: testTextIndent001
 * @tc.desc: Test Search input TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, testTextIndent001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty->UpdateTextIndent(DEFAULT_INDENT_SIZE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetTextIndent(), DEFAULT_INDENT_SIZE);
}

/**
 * @tc.name: testFontColor001
 * @tc.desc: test search fontColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, testFontColor001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    /**
     * @tc.step: step2. Set fontColor
     */
    searchModelInstance.SetTextColor(Color::BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetTextColor(), Color::BLUE);
    /**
     * @tc.step: step3. Set fontColor
     */
    searchModelInstance.SetTextColor(Color::RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetTextColor(), Color::RED);
}

/**
 * @tc.name: testTextAlign001
 * @tc.desc: test search textAlign
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, testTextAlign001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and textFieldLayoutProperty.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    /**
     * @tc.step: step2. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::LEFT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::LEFT);
    /**
     * @tc.step: step3. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::RIGHT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::RIGHT);
    /**
     * @tc.step: step4. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::CENTER);
    /**
     * @tc.step: step5. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::JUSTIFY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::JUSTIFY);
    /**
     * @tc.step: step6. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::START);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::START);
    /**
     * @tc.step: step7. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::END);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::END);
}

/**
 * @tc.name: testCancelButton001
 * @tc.desc: test search cancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, testCancelButton001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto buttonHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    auto cancelButtonRenderContext = buttonHost->GetRenderContext();
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    /**
     * @tc.step: step2. Set cancelButton
     */
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);
    EXPECT_EQ(cancelButtonRenderContext->GetOpacity(), 1.0);
    /**
     * @tc.step: step3. Set cancelButton
     */
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
    EXPECT_EQ(cancelButtonRenderContext->GetOpacity(), 0.0);
}

/**
 * @tc.name: Pattern016
 * @tc.desc: test OnKeyEvent for arrow key presses and with text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern016, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue("Text", 0);
    textFieldPattern->HandleOnSelectAll(true);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.step: step4. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step5. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern017
 * @tc.desc: test OnKeyEvent for arrow key presses and without text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern017, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue("", 0);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(0, 0);
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern018
 * @tc.desc: test OnKeyEvent for Tab/Shift+Tab key presses and with text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern018, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue("Text", 0);
    TimeStamp timeStamp;
    KeyEvent keyEvent(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    KeyEvent keyEventShiftTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: step4. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step5. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern019
 * @tc.desc: test OnKeyEvent for Tab/Shift+Tab key presses and without text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern019, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue("", 0);
    TimeStamp timeStamp;
    KeyEvent keyEvent(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});
    KeyEvent keyEventShiftTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->isSearchButtonEnabled_ = true;
    pattern->cancelButtonSize_ = SizeF(0, 0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);
    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern020
 * @tc.desc: test OnKeyEvent for pressing Enter when the focus is at cancel button
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern020, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue("Text", 0);
    TimeStamp timeStamp;
    KeyEvent keyEvent(
        KeyCode::KEY_TAB, KeyAction::DOWN, { KeyCode::KEY_TAB }, 0, timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    keyEvent.code = KeyCode::KEY_ENTER, keyEvent.action = KeyAction::DOWN;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern021
 * @tc.desc: Test DragEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern021, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldEventHub = textFieldFrameNode->GetEventHub<EventHub>();
    pattern->ResetDragOption();

    /**
     * @tc.cases: case1.
     */
    eventHub->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->onDragStart_, nullptr);

    /**
     * @tc.cases: case2.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_ENTER, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragEnter_, nullptr);

    /**
     * @tc.cases: case3.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_LEAVE, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragLeave_, nullptr);

    /**
     * @tc.cases: case4.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_MOVE, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragMove_, nullptr);

    /**
     * @tc.cases: case5.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_DROP, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDrop_, nullptr);

    /**
     * @tc.cases: case6.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_END, [](const RefPtr<OHOS::Ace::DragEvent>&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragEnd_, nullptr);
}

/**
 * @tc.name: Pattern022
 * @tc.desc: Test key events with different focus
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern022, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    TimeStamp timeStamp;

    /**
     * @tc.cases: case1.
     */
    KeyEvent keyEventOne;
    keyEventOne.code = KeyCode::KEY_TAB;
    keyEventOne.action = KeyAction::UP;
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    pattern->OnKeyEvent(keyEventOne);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.cases: case2.
     */
    KeyEvent keyEventTwo(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->isSearchButtonEnabled_ = false;
    pattern->OnKeyEvent(keyEventTwo);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case3.
     */
    KeyEvent keyEventThree(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});
    pattern->cancelButtonSize_ = SizeF(100.0f, 0.0f);
    textFieldPattern->UpdateEditingValue("", 0);
    pattern->OnKeyEvent(keyEventThree);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case4.
     */
    KeyEvent keyEventFour(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN, {KeyCode::KEY_DPAD_RIGHT}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});
    textFieldPattern->UpdateEditingValue("Text", 0);
    pattern->OnKeyEvent(keyEventFour);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case5.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    pattern->cancelButtonSize_ = SizeF(100.0f, 50.0f);
    pattern->OnKeyEvent(keyEventFour);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.cases: case6.
     */
    KeyEvent keyEventFive;
    keyEventFive.code = KeyCode::KEY_DPAD_LEFT;
    keyEventFive.action = KeyAction::DOWN;
    pattern->cancelButtonSize_ = SizeF(100.0f, 50.0f);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->OnKeyEvent(keyEventFive);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern023
 * @tc.desc: Test key events with column layout
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern023, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    frameNode->onMainTree_ = true;

    /**
     * @tc.step: step2. create column layout.
     */
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;
    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    columnFrameNode->AddChild(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto parentHub = focusHub->GetParentFocusHub();
    ASSERT_NE(parentHub, nullptr);

    /**
     * @tc.cases: case1.
     */
    TimeStamp timeStamp;
    KeyEvent keyEventShiftTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    textFieldPattern->UpdateEditingValue("Text", 0);
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.cases: case2.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.cases: case3.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    pattern->cancelButtonSize_ = SizeF(100.0f, 0.0f);
    KeyEvent keyEventTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    pattern->OnKeyEvent(keyEventTab);
}

/**
 * @tc.name: Pattern024
 * @tc.desc: Test key events in different scenarios
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern024, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.step: step2. create key events.
     */
    TimeStamp timeStamp;
    KeyEvent keyEventTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    KeyEvent keyEventDpadRight(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN, {KeyCode::KEY_DPAD_RIGHT}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    KeyEvent keyEventNumsEight(KeyCode::KEY_8, KeyAction::DOWN, {KeyCode::KEY_8}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.cases: case1.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->OnKeyEvent(keyEventTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.cases: case2.
     */
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    columnFrameNode->AddChild(frameNode);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventDpadRight);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.cases: case3.
     */
    pattern->OnKeyEvent(keyEventTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case4.
     */
    pattern->OnKeyEvent(keyEventNumsEight);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern025
 * @tc.desc: InitButtonTouchEvent ColorMode = DARK
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern025, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    TouchTestResult result;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    pattern->InitButtonTouchEvent(touchEvent, BUTTON_INDEX);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto gesture = buttonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_NE(events.size(), 0);
    SystemProperties::SetColorMode(ColorMode::DARK);
    for (auto event : events) {
        event->callback_(info);
    }
}

/**
 * @tc.name: Pattern026
 * @tc.desc: Test SearchController init
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern026, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue("", 0);

    pattern->InitSearchController();
    pattern->searchController_->getTextContentRect_();
    RectF textRect = textFieldPattern->GetTextRect();
    EXPECT_EQ(textRect, RectF(0, 0, 0, 0));

    pattern->searchController_->getTextContentLinesNum_();
    auto textFieldController = textFieldPattern->GetTextFieldController();
    int32_t contentLines = textFieldController->GetTextContentLinesNum();
    EXPECT_EQ(contentLines, 0);

    pattern->searchController_->getCaretIndex_();
    int32_t caretIndex = textFieldController->GetCaretIndex();
    EXPECT_EQ(caretIndex, 0);

    pattern->searchController_->getCaretPosition_();
    auto caretPosition = textFieldController->GetCaretPosition();
    EXPECT_EQ(caretPosition, OffsetF(0, 0));

    textFieldPattern->UpdateEditingValue("Text", 0);
    pattern->searchController_->stopEditing_();
    caretIndex = textFieldController->GetCaretIndex();
    EXPECT_EQ(caretIndex, 0);
}

/**
 * @tc.name: OnSubmitEvent001
 * @tc.desc: Test Search onSubmit event
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, OnSubmitEvent001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);

    int count = 0;
    TextFieldCommonEvent event2;
    auto callback = [&count, &event2](const std::u16string& title, NG::TextFieldCommonEvent& event) {
        event2 = event;
        if (count > 0) {
            event.SetKeepEditable(true);
            EXPECT_TRUE(event.keepEditable_);
        }
        count = count + 1;
    };
    eventHub->SetOnSubmit(std::move(callback));

    bool forceCloseKeyboard = true;
    TextInputAction action2 = TextInputAction::SEARCH;
    textFieldPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 1);
    action2 = TextInputAction::NEW_LINE;
    textFieldPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 2);
    action2 = TextInputAction::DONE;
    textFieldPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 3);
}

/**
 * @tc.name: OnSubmitEvent002
 * @tc.desc: Test Search onSubmit event
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, OnSubmitEvent002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);

    int count = 0;
    TextFieldCommonEvent event2;
    auto callback = [&count, &event2](const std::u16string& title, NG::TextFieldCommonEvent& event) {
        event2 = event;
        if (count > 0) {
            event.SetKeepEditable(true);
            EXPECT_TRUE(event.keepEditable_);
        }
        count = count + 1;
    };
    eventHub->SetOnSubmit(std::move(callback));

    pattern->OnClickButtonAndImage();
    EXPECT_EQ(count, 1);
    pattern->OnClickButtonAndImage();
    EXPECT_EQ(count, 2);
}

/**
 * @tc.name: UpdateChangeEvent001
 * @tc.desc: test search UpdateChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, UpdateChangeEvent001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode =AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    eventHub->onValueChangeEvent_ = [](const std::u16string str) {};
    eventHub->changeEvent_ = [](const std::u16string str) {};
    eventHub->UpdateChangeEvent(u"");
}

/**
 * @tc.name: PackInnerRecognizer001
 * @tc.desc: test search PackInnerRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, PackInnerRecognizerr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SearchGestureEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto searchgestureEventHub = AceType::MakeRefPtr<SearchGestureEventHub>(eventHub);
    EXPECT_TRUE(searchgestureEventHub);
    Offset offset;
    std::list<RefPtr<NGGestureRecognizer>> innerRecognizers;
    int32_t touchId = 0;
    RefPtr<TargetComponent> targetComponent;
    searchgestureEventHub->innerParallelRecognizer_ = nullptr;
    searchgestureEventHub->CheckClickActuator();
    auto clickEventActuator = searchgestureEventHub->GetUserClickEventActuator();
    GestureEventFunc callback = [](GestureEvent& info) {};
    clickEventActuator->SetUserCallback(std::move(callback));
    searchgestureEventHub->PackInnerRecognizer(offset, innerRecognizers, touchId, targetComponent);
    searchgestureEventHub->PackInnerRecognizer(offset, innerRecognizers, touchId, targetComponent);
}

/**
 * @tc.name: MinFontSize001
 * @tc.desc: test search minFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, MinFontSize001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2.  set minFontSize 1.0 fp.
     */
    searchModelInstance.SetAdaptMinFontSize(1.0_fp);
    frameNode->MarkModifyDone();

    /**
     * @tc.step: step3. test minFontSize
     */
    EXPECT_EQ(textFieldLayoutProperty->GetAdaptMinFontSize(), 1.0_fp);
}

/**
 * @tc.name: MaxFontSize001
 * @tc.desc: test search maxFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, MaxFontSize001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2.  set maxFontSize 2.0 fp.
     */
    searchModelInstance.SetAdaptMaxFontSize(2.0_fp);
    frameNode->MarkModifyDone();

    /**
     * @tc.step: step3. test maxFontSize
     */
    EXPECT_EQ(textFieldLayoutProperty->GetAdaptMaxFontSize(), 2.0_fp);
}

/**
 * @tc.name: SetHeight001
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SetProperty001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto eventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    //test SetHeight
    searchModelInstance.SetHeight(Dimension(2.5, DimensionUnit::VP));

    //test SetOnChange
    searchModelInstance.SetOnChange([](const std::u16string str, PreviewText previewText) {});
    EXPECT_NE(eventHub->GetOnChange(), nullptr);

    //test SetOnTextSelectionChange
    searchModelInstance.SetOnTextSelectionChange([](int32_t a, int32_t b) {});
    EXPECT_NE(eventHub->onSelectionChange_, nullptr);

    //test SetOnScroll
    searchModelInstance.SetOnScroll([](float a, float b) {});
    EXPECT_NE(eventHub->onScrollChangeEvent_, nullptr);

    //test SetSelectionMenuHidden
    searchModelInstance.SetSelectionMenuHidden(true);
    EXPECT_EQ(textFieldLayoutProperty->GetSelectionMenuHidden().value(), true);

    //test SetOnCut
    searchModelInstance.SetOnCut([](const std::u16string str) {});
    EXPECT_NE(eventHub->onCut_, nullptr);

    //test SetCustomKeyboard
    searchModelInstance.SetCustomKeyboard([]() {});
    EXPECT_NE(pattern->customKeyboardBuilder_, nullptr);

    //test SetType
    searchModelInstance.SetType(TextInputType::BEGIN);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::BEGIN);
    searchModelInstance.SetType(TextInputType::TEXT);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::TEXT);
    searchModelInstance.SetType(TextInputType::TEXT);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::TEXT);
}

/**
 * @tc.name: SetHeight002
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SetProperty002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    //test RequestKeyboardOnFocus
    searchModelInstance.RequestKeyboardOnFocus(frameNode, true);
    EXPECT_EQ(pattern->needToRequestKeyboardOnFocus_, true);

    //test SetPlaceholderFont
    Font otherfont;
    searchModelInstance.SetPlaceholderFont(otherfont);
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);
    Font font;
    font.fontSize = Dimension(2);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W200;
    std::vector<std::string> families = { "cursive" };
    font.fontFamilies = families;
    searchModelInstance.SetPlaceholderFont(frameNode, font);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontWeight(), FontWeight::W200);
}

/**
 * @tc.name: SetHeight003
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SetProperty003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();

    //test SetSearchButtonFontColor
    auto buttonFNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(BUTTON_INDEX));
    auto bnLayoutProperty = buttonFNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonFontColor(frameNode, Color::RED);
    EXPECT_EQ(bnLayoutProperty->GetFontColor(), Color::RED);

    //test SetCopyOption
    searchModelInstance.SetCopyOption(frameNode, CopyOptions::Distributed);
    EXPECT_EQ(textFieldLayoutProperty->GetCopyOptions(), OHOS::Ace::CopyOptions::Distributed);

    //test SetTextFont
    Font font;
    font.fontSize = Dimension(2);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W200;
    std::vector<std::string> families = { "cursive" };
    font.fontFamilies = families;
    searchModelInstance.SetTextFont(frameNode, font);
    EXPECT_EQ(textFieldLayoutProperty->GetFontWeight(), FontWeight::W200);
}

/**
 * @tc.name: SetHeight004
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SetProperty004, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    //test SetSearchIconSize
    auto searchLayoutProperty = fNode->GetLayoutProperty<SearchLayoutProperty>();
    searchModelInstance.SetSearchIconSize(frameNode, Dimension(2.5, DimensionUnit::VP));
    EXPECT_EQ(searchLayoutProperty->GetSearchIconUDSize(), 2.5_vp);

    //test SetSearchSrcPath
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath(frameNode, EMPTY_VALUE);
    searchModelInstance.SetSearchSrcPath(frameNode, "/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");

    //test SetSearchIconColor
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    ImageSourceInfo imageSourceInfo("", Dimension(-1), Dimension(-1), InternalResource::ResourceId::CORRECT_SVG);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    searchModelInstance.SetSearchIconColor(frameNode, Color::RED);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor(), Color::RED);

    //test SetSearchButton
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto searchButtonRenderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(searchButtonRenderContext);
    searchModelInstance.SetSearchButton(frameNode, EMPTY_VALUE);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 0.0);
    searchModelInstance.SetSearchButton(frameNode, PLACEHOLDER);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 1.0);

    //test SetSearchButtonFontSize
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonFontSize(frameNode, 14.0_vp);
    EXPECT_EQ(buttonLayoutProperty->GetFontSize(), 14.0_vp);

    //test SetTextColor
    searchModelInstance.SetTextColor(frameNode, Color::RED);
    EXPECT_EQ(textFieldLayoutProperty->GetTextColor(), Color::RED);
}

/**
 * @tc.name: SetHeight005
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SetProperty005, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    //test SetPlaceholderColor
    searchModelInstance.SetPlaceholderColor(frameNode, Color::RED);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderTextColor(), Color::RED);

    //test SetSelectionMenuHidden
    searchModelInstance.SetSelectionMenuHidden(frameNode, true);
    EXPECT_EQ(textFieldLayoutProperty->GetSelectionMenuHidden(), true);

    //test SetHeight
    searchModelInstance.SetHeight(frameNode, Dimension(2.5, DimensionUnit::VP));

    //test SET
    searchModelInstance.SetAdaptMinFontSize(frameNode, Dimension(2.5, DimensionUnit::VP));
    searchModelInstance.SetAdaptMaxFontSize(frameNode, Dimension(3.5, DimensionUnit::VP));
    searchModelInstance.SetLetterSpacing(frameNode, Dimension(2.5, DimensionUnit::VP));
    searchModelInstance.SetLineHeight(frameNode, Dimension(2.5, DimensionUnit::VP));

    //test SetSearchImageIcon
    NG::IconOptions iconOptions = NG::IconOptions(Color::RED, 14.0_vp, "/common/icon.png", "", "");
    searchModelInstance.SetSearchImageIcon(frameNode, iconOptions);

    //test SetCaretWidth
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    searchModelInstance.SetCaretWidth(frameNode, Dimension(2.5, DimensionUnit::VP));
    EXPECT_EQ(paintProperty->GetCursorWidth().value().Value(), 2.5);

    //test SetCaretColor
    searchModelInstance.SetCaretColor(frameNode, Color::BLUE);
    searchModelInstance.SetTextAlign(frameNode, TextAlign::CENTER);

    //test SetCancelButtonStyle
    searchModelInstance.SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);
    fNode->MarkModifyDone();
    auto searchLayoutProperty = fNode->GetLayoutProperty<SearchLayoutProperty>();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);
    searchModelInstance.SetCancelButtonStyle(frameNode, CancelButtonStyle::INVISIBLE);
    fNode->MarkModifyDone();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);

    //test SetCancelIconSize
    searchModelInstance.SetCancelIconSize(frameNode, 14.0_vp);
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonUDSize(), 14.0_vp);

    //test SetCancelIconColor
    auto imageFNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto imageRProperty = imageFNode->GetPaintProperty<ImageRenderProperty>();
    searchModelInstance.SetCancelIconColor(frameNode, Color::RED);
    EXPECT_EQ(imageRProperty->GetSvgFillColor(), Color::RED);

    //test SetRightIconSrcPath
    auto cancelImageLayoutProperty = imageFNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetRightIconSrcPath(frameNode, "");
    ASSERT_STREQ(cancelImageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "resource:///ohos_test_image.svg");

    //test SetEnterKeyType
    searchModelInstance.SetSearchEnterKeyType(frameNode, TextInputAction::NEXT);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    EXPECT_EQ(TextInputAction::NEXT, textFieldPattern->GetTextInputActionValue(TextInputAction::UNSPECIFIED));
}
/**
 * @tc.name: SetEnterKeyType001
 * @tc.desc: test search set enterKeyType default value
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SetEnterKeyType001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    searchModelInstance.SetSearchEnterKeyType(frameNode, TextInputAction::UNSPECIFIED);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    EXPECT_EQ(TextInputAction::SEARCH, textFieldPattern->GetTextInputActionValue(TextInputAction::UNSPECIFIED));
}

/**
 * @tc.name: LetterSpacing001
 * @tc.desc: test search letterSpacing
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, LetterSpacing001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2.  set letterSpacing 1.0 fp.
     */
    searchModelInstance.SetLetterSpacing(1.0_fp);
    frameNode->MarkModifyDone();

    /**
     * @tc.step: step3. test letterSpacing
     */
    EXPECT_EQ(textFieldLayoutProperty->GetLetterSpacing(), 1.0_fp);
}

/**
 * @tc.name: LineHeight001
 * @tc.desc: test search lineHeight
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, LineHeight001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2.  set lineHeight 2.0 fp.
     */
    searchModelInstance.SetLineHeight(2.0_fp);
    frameNode->MarkModifyDone();

    /**
     * @tc.step: step3. test lineHeight
     */
    EXPECT_EQ(textFieldLayoutProperty->GetLineHeight(), 2.0_fp);
}

/**
 * @tc.name: TextDecoration001
 * @tc.desc: test search decoration
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, TextDecoration001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    /**
     * @tc.step: step2.  set decoration Ace::TextDecoration::UNDERLINE.
     */
    searchModelInstance.SetTextDecoration(Ace::TextDecoration::UNDERLINE);
    frameNode->MarkModifyDone();
    searchModelInstance.SetTextDecorationColor(Color::BLUE);
    frameNode->MarkModifyDone();
    searchModelInstance.SetTextDecorationStyle(Ace::TextDecorationStyle::DASHED);
    frameNode->MarkModifyDone();
    /**
     * @tc.step: step3. test decoration
     */
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecoration(), Ace::TextDecoration::UNDERLINE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationColor(), Color::BLUE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationStyle(), Ace::TextDecorationStyle::DASHED);
}

/**
 * @tc.name: UpdateFontFeature001
 * @tc.desc: test fontFeature
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, UpdateFontFeature001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    SearchModelNG searchModelInstance;
    searchModelInstance.SetFontFeature(FONT_FEATURE_VALUE_1);
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_1);

    layoutProperty->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    SearchModelNG::SetFontFeature(frameNode, FONT_FEATURE_VALUE_1);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_1);
}

/**
 * @tc.name: UpdateFontFeature
 * @tc.desc: test fontFeature
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, UpdateFontFeature002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    SearchModelNG searchModelInstance;
    searchModelInstance.SetFontFeature(FONT_FEATURE_VALUE_0);
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_0);

    layoutProperty->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 1"));
    SearchModelNG::SetFontFeature(frameNode, FONT_FEATURE_VALUE_0);
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_0);
}

/**
 * @tc.name: SupportAvoidanceTest
 * @tc.desc: test whether the custom keyboard supports the collision avoidance function
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SupportAvoidanceTest, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto supportAvoidance = true;
    textFieldPattern->SetCustomKeyboardOption(supportAvoidance);
    EXPECT_TRUE(textFieldPattern->keyboardAvoidance_);
    supportAvoidance = false;
    textFieldPattern->SetCustomKeyboardOption(supportAvoidance);
    EXPECT_FALSE(textFieldPattern->keyboardAvoidance_);
}

/**
 * @tc.name: UpdateInspectorId001
 * @tc.desc: test search model UpdateInspectorId
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, UpdateInspectorId001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and ChildrenNode.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto cancelImageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelImageFrameNode, nullptr);

    /**
     * @tc.step: step2.  set different idName, test children inspectorId.
     */
    std::vector<std::string> idNames = { "", "searchTest", "searchTest_Key" };
    for (int32_t i = 0; i < idNames.size(); i++) {
        searchModelInstance.UpdateInspectorId(idNames[i]);
        auto result1 = INSPECTOR_PREFIX + SPECIALIZED_INSPECTOR_INDEX[IMAGE_INDEX] + idNames[i];
        EXPECT_TRUE(imageFrameNode->GetInspectorIdValue() == result1);
        auto result2 = INSPECTOR_PREFIX + SPECIALIZED_INSPECTOR_INDEX[BUTTON_INDEX] + idNames[i];
        EXPECT_TRUE(buttonFrameNode->GetInspectorIdValue() == result2);
        auto result3 = INSPECTOR_PREFIX + SPECIALIZED_INSPECTOR_INDEX[CANCEL_BUTTON_INDEX] + idNames[i];
        EXPECT_TRUE(cancelButtonFrameNode->GetInspectorIdValue() == result3);
        auto result4 = INSPECTOR_PREFIX + SPECIALIZED_INSPECTOR_INDEX[CANCEL_IMAGE_INDEX] + idNames[i];
        EXPECT_TRUE(cancelImageFrameNode->GetInspectorIdValue() == result4);
    }
}

/**
 * @tc.name: SearchTypeToString001
 * @tc.desc: test search pattern UpdateInspectorId
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SearchTypeToString001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    /**
     * @tc.step: step2.  Call SearchTypeToString.
     */
    searchModelInstance.SetType(TextInputType::NUMBER);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    EXPECT_EQ(pattern->SearchTypeToString(), "SearchType.NUMBER");
}

HWTEST_F(SearchTestTwoNg, SearchTypeToString002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    searchModelInstance.SetType(TextInputType::EMAIL_ADDRESS);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    EXPECT_EQ(pattern->SearchTypeToString(), "SearchType.EMAIL");
}

HWTEST_F(SearchTestTwoNg, SearchTypeToString003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    searchModelInstance.SetType(TextInputType::PHONE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    EXPECT_EQ(pattern->SearchTypeToString(), "SearchType.PHONE_NUMBER");
}

HWTEST_F(SearchTestTwoNg, SearchTypeToString004, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    searchModelInstance.SetType(TextInputType::URL);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    EXPECT_EQ(pattern->SearchTypeToString(), "SearchType.URL");
}

/**
 * @tc.name: PatternOnColorConfigurationUpdate012
 * @tc.desc: Test pttern HandleTextContentLines
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, PatternOnColorConfigurationUpdate012, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);

    /**
     * @tc.step: step2. create textFieldPattern and searchPattern.
     */
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->UpdateEditingValue("", 0);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.step: step3. call HandleTextContentLines.
     * @tc.expected: cover branch IsOperation is false and call HandleTextContentLines
     */
    int32_t result = pattern->HandleTextContentLines();
    EXPECT_EQ(result, 0);

    /**
     * @tc.step: step4. call HandleTextContentLines.
     * @tc.expected: cover branch IsOperation is true and GetLineHeight value is 0.
     */
    textFieldPattern->UpdateEditingValue("aaa", 0);
    result = pattern->HandleTextContentLines();
    EXPECT_EQ(result, 0);
    pattern->HandleCaretPosition(3); // 3 is caret index
    pattern->HandleGetCaretPosition();
    auto index = pattern->HandleGetCaretIndex();
    ASSERT_EQ(index, 3); // 3 is caret index

    /**
     * @tc.step: step5. call HandleTextContentLines.
     * @tc.expected: cover branch IsOperation is true and GetLineHeight value is not 0.
     */
    textFieldPattern->UpdateEditingValue("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 45);
    pattern->HandleCaretPosition(6);
    result = pattern->HandleTextContentLines();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: UpdateChangeEvent and ToJsonValue while cancel button style is different
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);
}
    
/**
 * @tc.name: Pattern004
 * @tc.desc: UpdateChangeEvent and ToJsonValue while cancel button style is different
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, Pattern004, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateChangeEvent(u"");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
}

/**
 * @tc.name: PatternHandleFocusEvent001
 * @tc.desc: Test HandleFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, PatternHandleFocusEvent001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    bool backwardFocusMovement = true;
    bool forwardFocusMovement = true;
    pattern -> HandleFocusEvent(forwardFocusMovement, backwardFocusMovement);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: SetTextFont(FrameNode* frameNode, const Font& font)
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SetTextFont, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    Font otherfont;
    searchModelInstance.SetTextFont(otherfont);
    Font font;
    font.fontSize = Dimension(2);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W200;
    std::vector<std::string> families = { "cursive" };
    font.fontFamilies = families;
    searchModelInstance.SetTextFont(frameNode, font);
    EXPECT_EQ(textFieldLayoutProperty->GetFontWeight(), FontWeight::W200);
    const std::string str = "DEFAULT";
    searchModelInstance.SetTextValue(frameNode, str);
    searchModelInstance.SetIcon(frameNode, "");
    searchModelInstance.SetMaxLength(frameNode, 19);
    searchModelInstance.SetOnSubmit(frameNode, [](const std::u16string& title, NG::TextFieldCommonEvent& event) {});
    searchModelInstance.SetOnChange(frameNode, [](const std::u16string str, PreviewText previewText) {});
    searchModelInstance.SetType(frameNode, TextInputType::BEGIN);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::BEGIN);
    searchModelInstance.SetType(frameNode, TextInputType::TEXT);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::TEXT);
    searchModelInstance.SetType(frameNode, TextInputType::TEXT);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::TEXT);
    searchModelInstance.SetOnTextSelectionChange(frameNode, [](int32_t a, int32_t b) {});
    searchModelInstance.SetOnCopy(frameNode, [](const std::u16string& title) {});
    searchModelInstance.SetOnCut(frameNode, [](const std::u16string str) {});
    searchModelInstance.SetOnPasteWithEvent(frameNode, [](const std::u16string& title, NG::TextCommonEvent& event) {});
    searchModelInstance.SetPlaceholder(frameNode, PLACEHOLDER);
    searchModelInstance.SetTextDecoration(frameNode, Ace::TextDecoration::UNDERLINE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecoration(), Ace::TextDecoration::UNDERLINE);
    searchModelInstance.SetTextDecorationColor(frameNode, Color::BLUE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationColor(), Color::BLUE);
    searchModelInstance.SetTextDecorationStyle(frameNode, Ace::TextDecorationStyle::DASHED);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationStyle(), Ace::TextDecorationStyle::DASHED);
    searchModelInstance.SetEnablePreviewText(frameNode, true);
}
/**
 * @tc.name: CreateSearchNode
 * @tc.desc: CreateSearchNode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, CreateSearchNode, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    searchModelInstance.SetSearchDefaultIcon();
    searchModelInstance.CreateSearchNode(nodeId, u"", u"", "");
}

/**
 * @tc.name: SymbolColorToString001
 * @tc.desc: SymbolColorToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SymbolColorToString001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(V2::SEARCH_ETS_TAG, nodeId, AceType::MakeRefPtr<SearchPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto searchPattern = AceType::DynamicCast<SearchPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    std::vector<Color> colors;
    colors.push_back(Color::BLUE);
    auto result = searchPattern->SymbolColorToString(colors);
    EXPECT_NE(result, "");
}

/**
 * @tc.name: SymbolColorToString002
 * @tc.desc: SymbolColorToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestTwoNg, SymbolColorToString002, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(V2::SEARCH_ETS_TAG, nodeId, AceType::MakeRefPtr<SearchPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto searchPattern = AceType::DynamicCast<SearchPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    std::vector<Color> colors;
    auto result = searchPattern->SymbolColorToString(colors);
    EXPECT_EQ(result, "");
}
} // namespace OHOS::Ace::NG
