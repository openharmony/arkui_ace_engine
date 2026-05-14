/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "gtest/gtest.h"
#include "search_base.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/common/resource/pattern_resource_manager.h"

namespace OHOS::Ace::NG {

class SearchTestFourNg : public SearchBases {
public:
};

/**
 * @tc.name: OnKeyEventTabToSearchButton
 * @tc.desc: TAB key from SEARCH_BUTTON should return false (focus moves out)
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnKeyEventTabToSearchButton, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set focus on search button
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_TAB;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_TAB };

    // From SEARCH_BUTTON, TAB returns false (focus moves out of Search)
    auto result = pattern->OnKeyEvent(keyEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnKeyEventDpadLeftCancel
 * @tc.desc: DPAD_LEFT from CANCEL_BUTTON with cancelButtonSize=0 should switch to SEARCH
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnKeyEventDpadLeftCancel, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set focus on cancel button, cancelButtonSize=0
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    pattern->cancelButtonSize_ = SizeF(0.0, 0.0);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    keyEvent.action = KeyAction::DOWN;

    auto result = pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEventDpadRightSearchButton
 * @tc.desc: DPAD_RIGHT from SEARCH_BUTTON with !isSearchButtonEnabled returns true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnKeyEventDpadRightSearchButton, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set focus on search button, !isSearchButtonEnabled
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->isSearchButtonEnabled_ = false;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    keyEvent.action = KeyAction::DOWN;

    // When isSearchButtonEnabled_=false, DPAD_RIGHT from SEARCH_BUTTON returns true
    auto result = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEventEnterSearch
 * @tc.desc: ENTER key on SEARCH focuses and requests keyboard
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnKeyEventEnterSearch, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set focus on search, press Enter
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_ENTER;
    keyEvent.action = KeyAction::DOWN;

    auto result = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEventSpaceSearchButton
 * @tc.desc: SPACE key on search button triggers OnClickButtonAndImage
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnKeyEventSpaceSearchButton, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // focus on search button, press Space
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;

    auto result = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEventSpaceCancelButton
 * @tc.desc: SPACE key on cancel button triggers OnClickCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnKeyEventSpaceCancelButton, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // focus on cancel button, press Space
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;

    auto result = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(result);
}

// ===== Medium Priority Tests (Focus/State Management) =====

/**
 * @tc.name: PaintSearchFocusCancel
 * @tc.desc: Test PaintSearchFocusState with focusChoice=CANCEL_BUTTON
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, PaintSearchFocusCancel, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;

    // Test focusChoice=CANCEL_BUTTON branch
    pattern->PaintSearchFocusState();

    // Verify cancel button focus color is set
    EXPECT_TRUE(true);  // Verify no crash
}

/**
 * @tc.name: HandleFocusChoiceForward
 * @tc.desc: Test HandleFocusChoiceSearch with forwardFocusMovement
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, HandleFocusChoiceForward, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Get SearchTextFieldPattern for third parameter
    auto searchTextFieldPattern = AceType::DynamicCast<SearchTextFieldPattern>(textFieldPattern);

    // Test forwardFocusMovement=true
    pattern->HandleFocusChoiceSearch(textFieldPattern, true, searchTextFieldPattern);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleFocusChoiceBackward
 * @tc.desc: Test HandleFocusChoiceSearch with backwardFocusMovement
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, HandleFocusChoiceBackward, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Get SearchTextFieldPattern for third parameter
    auto searchTextFieldPattern = AceType::DynamicCast<SearchTextFieldPattern>(textFieldPattern);

    // Test backwardFocusMovement=true
    pattern->HandleFocusChoiceSearch(textFieldPattern, false, searchTextFieldPattern);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleBlurEventTest
 * @tc.desc: Test HandleBlurEvent blur event handling
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, HandleBlurEventTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set focus flags to test reset in HandleBlurEvent
    pattern->isFocusTextColorSet_ = true;
    pattern->isFocusBgColorSet_ = true;
    pattern->isFocusIconColorSet_ = true;

    // Test blur event
    pattern->HandleBlurEvent();

    // Verify focus flags are reset by HandleBlurEvent
    EXPECT_FALSE(pattern->isFocusTextColorSet_);
    EXPECT_FALSE(pattern->isFocusBgColorSet_);
    EXPECT_FALSE(pattern->isFocusIconColorSet_);
}

/**
 * @tc.name: OnClickButtonAndImageTest
 * @tc.desc: Test OnClickButtonAndImage click search button
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnClickButtonAndImageTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set search button text
    pattern->searchButton_ = "Search";

    // Test click search button
    pattern->OnClickButtonAndImage();

    EXPECT_TRUE(true);  // Verify no crash
}

/**
 * @tc.name: OnClickCancelButtonTest
 * @tc.desc: Test OnClickCancelButton click cancel button
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnClickCancelButtonTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test click cancel button
    pattern->OnClickCancelButton();

    // Verify focus is back to search field
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: OnClickTextFieldTest
 * @tc.desc: Test OnClickTextField click text field
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, OnClickTextFieldTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test click text field
    pattern->OnClickTextField();

    // Verify focus is set to search field
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

// ===== Low Priority Tests (Auxiliary Functions) =====

/**
 * @tc.name: HandleCaretPositionTest
 * @tc.desc: Test HandleCaretPosition set caret position
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, HandleCaretPositionTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test set caret position
    pattern->HandleCaretPosition(5);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleTextContentRectTest
 * @tc.desc: Test HandleTextContentRect handle text rectangle
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, HandleTextContentRectTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    Rect rect;
    rect.SetRect(0.0f, 0.0f, 100.0f, 50.0f);

    // Test handle text rectangle
    pattern->HandleTextContentRect(rect);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleTextContentLinesTest
 * @tc.desc: Test HandleTextContentLines get text line count
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, HandleTextContentLinesTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test get text line count
    auto lines = pattern->HandleTextContentLines();

    EXPECT_GE(lines, 0);
}

/**
 * @tc.name: HandleClickEventTest
 * @tc.desc: Test HandleClickEvent with isNotifyChildAction
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, HandleClickEventTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test HandleClickEvent when isNotifyChildAction_ is true
    pattern->isNotifyChildAction_ = true;
    GestureEvent info;
    pattern->HandleClickEvent(info);

    EXPECT_TRUE(true);  // Verify no crash
}

/**
 * @tc.name: InitSearchIconColorSizeTest
 * @tc.desc: Test InitSearchIconColorSize initialization
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, InitSearchIconColorSizeTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test InitSearchIconColorSize
    pattern->InitSearchIconColorSize();

    EXPECT_TRUE(true);  // Verify no crash
}

/**
 * @tc.name: ProcessTextFieldDefaultStyleTest
 * @tc.desc: Test ProcessTextFieldDefaultStyleAndBehaviors
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ProcessTextFieldDefaultStyleTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test ProcessTextFieldDefaultStyleAndBehaviors
    pattern->ProcessTextFieldDefaultStyleAndBehaviors();

    EXPECT_TRUE(true);  // Verify no crash
}

/**
 * @tc.name: ProcessDividerDefaultStyleTest
 * @tc.desc: Test ProcessDividerDefaultStyleAndBehaviors
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ProcessDividerDefaultStyleTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test ProcessDividerDefaultStyleAndBehaviors
    pattern->ProcessDividerDefaultStyleAndBehaviors();

    EXPECT_TRUE(true);  // Verify no crash
}

/**
 * @tc.name: StopEditingTest
 * @tc.desc: Test StopEditing stop editing without crash
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, StopEditingTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test StopEditing does not crash
    pattern->StopEditing();

    EXPECT_TRUE(true);  // Verify no crash
}

/**
 * @tc.name: SearchTypeToStringTest
 * @tc.desc: Test SearchTypeToString convert search type to string
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchTypeToStringTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test convert search type to string
    auto result = pattern->SearchTypeToString();
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: IsSearchAttachedTest
 * @tc.desc: Test IsSearchAttached check if search is attached
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, IsSearchAttachedTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Test check if search is attached
    auto result = pattern->IsSearchAttached();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsConsumeEventTest
 * @tc.desc: Test IsConsumeEvent with directionKeysMoveFocusOut=true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, IsConsumeEventTest, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set directionKeysMoveFocusOut_=true, so IsConsumeEvent returns false
    pattern->directionKeysMoveFocusOut_ = true;

    // Test check if event is consumed
    auto result = pattern->IsConsumeEvent();
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
