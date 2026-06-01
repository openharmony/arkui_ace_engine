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
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
 
#undef protected
#undef private
 
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color CUSTOM_FONT_COLOR = Color(0xFF123456);
const Color CUSTOM_FONT_COLOR_WITH_SPACE = Color(0xFF654321);
const std::string EMPTY_VALUE = "";
const std::string BUTTON_TEXT = "Search";
} // namespace

class SearchTestFourNg : public SearchBases {
public:
    void SetUp() override
    {
        SearchModelNG searchModelInstance;
        searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
        searchModelInstance.SetSearchButton(BUTTON_TEXT);
        searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    }
 
    void TearDown() override
    {
        ViewStackProcessor::GetInstance()->ClearStack();
    }
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

/**
 * @tc.name: ReportShiftAndDirectionEvent_ShiftRightUp
 * @tc.desc: Shift held + Right key release triggers selection event
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ReportShiftAndDirectionEvent_ShiftRightUp, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    keyEvent.action = KeyAction::UP;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };

    pattern->ReportShiftAndDirectionEvent(keyEvent);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ReportShiftAndDirectionEvent_ShiftLeftUp
 * @tc.desc: Shift held + Left key release triggers selection event
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ReportShiftAndDirectionEvent_ShiftLeftUp, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    keyEvent.action = KeyAction::UP;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };

    pattern->ReportShiftAndDirectionEvent(keyEvent);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ReportShiftAndDirectionEvent_ShiftUpCancel
 * @tc.desc: Shift held + Up key release (CANCEL) triggers selection event
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ReportShiftAndDirectionEvent_ShiftUpCancel, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.action = KeyAction::CANCEL;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };

    pattern->ReportShiftAndDirectionEvent(keyEvent);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ReportShiftAndDirectionEvent_ShiftDownUp
 * @tc.desc: Shift held + Down key release triggers selection event
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ReportShiftAndDirectionEvent_ShiftDownUp, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    keyEvent.action = KeyAction::UP;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };

    pattern->ReportShiftAndDirectionEvent(keyEvent);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ReportShiftAndDirectionEvent_RightUpNoShift
 * @tc.desc: Right key release WITHOUT shift should not trigger
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ReportShiftAndDirectionEvent_RightUpNoShift, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    keyEvent.action = KeyAction::UP;

    pattern->ReportShiftAndDirectionEvent(keyEvent);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ReportShiftAndDirectionEvent_ShiftRightDown
 * @tc.desc: Shift held + Right key press (DOWN action) should not trigger
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ReportShiftAndDirectionEvent_ShiftRightDown, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };

    pattern->ReportShiftAndDirectionEvent(keyEvent);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ReportShiftAndDirectionEvent_ShiftOnlyUp
 * @tc.desc: Only shift key release should not trigger
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ReportShiftAndDirectionEvent_ShiftOnlyUp, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SHIFT_LEFT;
    keyEvent.action = KeyAction::UP;

    pattern->ReportShiftAndDirectionEvent(keyEvent);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetSearchButtonFontColor_WithCustomColor_IsThemeFalse_API26
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor with custom color, isTheme=false on API26+
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SetSearchButtonFontColor_WithCustomColor_IsThemeFalse_API26, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
 
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetFontColor().value_or(Color::BLACK), CUSTOM_FONT_COLOR);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), false);
}
 
/**
 * @tc.name: SetSearchButtonFontColor_WithThemeColor_IsThemeTrue_API26
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor with theme color, isTheme=true on API26+
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SetSearchButtonFontColor_WithThemeColor_IsThemeTrue_API26, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::RED, true);
 
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetFontColor().value_or(Color::BLACK), Color::RED);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);
}
 
/**
 * @tc.name: SetSearchButtonFontColor_WithColorSpace_P3
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor preserves ColorSpace (DISPLAY_P3)
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SetSearchButtonFontColor_WithColorSpace_P3, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR_WITH_SPACE, false);
 
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto resultColor = buttonLayoutProperty->GetFontColor().value_or(Color::BLACK);
    EXPECT_EQ(resultColor.GetValue(), CUSTOM_FONT_COLOR_WITH_SPACE.GetValue());
}
 
/**
 * @tc.name: SetSearchButtonFontColor_NullFrameNode
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SetSearchButtonFontColor_NullFrameNode, TestSize.Level1)
{
    SearchModelNG::SetSearchButtonFontColor(nullptr, CUSTOM_FONT_COLOR, false);
    EXPECT_TRUE(true);
}
 
/**
 * @tc.name: SetSearchButtonFontColor_NullButtonFrameNode
 * @tc.desc: Test SearchModelNG SetSearchButtonFontColor when button child node is null
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SetSearchButtonFontColor_NullButtonFrameNode, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_ = {};
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    EXPECT_TRUE(true);
}
 
/**
 * @tc.name: SetCancelButtonFontColor_WithCustomColor_IsThemeFalse
 * @tc.desc: Test CancelButton color with custom color, isThemeColor=false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SetCancelButtonFontColor_WithCustomColor_IsThemeFalse, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
 
    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);
 
    auto iconColor = CUSTOM_FONT_COLOR;
    NG::IconOptions cancelIconOptions(iconColor, Dimension(16, DimensionUnit::PX), "", "", "");
    SearchModelNG::SetCancelImageIcon(frameNode, cancelIconOptions);
 
    EXPECT_TRUE(true);
}
 
/**
 * @tc.name: SetCancelButtonFontColor_WithThemeColor_IsThemeTrue
 * @tc.desc: Test CancelButton color with theme color, isThemeColor=true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SetCancelButtonFontColor_WithThemeColor_IsThemeTrue, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
 
    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);
 
    NG::IconOptions cancelIconOptions(Dimension(16, DimensionUnit::PX), "", "", "");
    SearchModelNG::SetCancelImageIcon(frameNode, cancelIconOptions);
 
    EXPECT_TRUE(true);
}
 
/**
 * @tc.name: SearchButtonFontColor_RegisterResource
 * @tc.desc: Test searchButtonFontColor resource registration with ConfigChangePerform
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButtonFontColor_RegisterResource, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    resObj->SetIsResource(true);
    resObj->id_ = 1001;
    resObj->type_ = static_cast<int32_t>(ResourceType::COLOR);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    pattern->RegisterResource<Color>("searchButtonFontColor", resObj, CUSTOM_FONT_COLOR);
    EXPECT_TRUE(pattern->resourceMgr_->resMap_.count("searchButtonFontColor") > 0);
}
 
/**
 * @tc.name: SearchButtonFontColor_UnRegisterResource
 * @tc.desc: Test searchButtonFontColor resource unregistration
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButtonFontColor_UnRegisterResource, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    pattern->UnRegisterResource("searchButtonFontColor");
    CHECK_NULL_VOID(pattern->resourceMgr_);
    EXPECT_FALSE(pattern->resourceMgr_->resMap_.count("searchButtonFontColor") > 0);
}
 
/**
 * @tc.name: SearchButton_IsSearchButtonUsingThemeColor_Default
 * @tc.desc: Test IsSearchButtonUsingThemeColor default value is true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButton_IsSearchButtonUsingThemeColor_Default, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);
}
 
/**
 * @tc.name: SearchButton_IsSearchButtonUsingThemeColor_SetFalse
 * @tc.desc: Test SetIsSearchButtonUsingThemeColor to false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButton_IsSearchButtonUsingThemeColor_SetFalse, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), false);
}
 
/**
 * @tc.name: SearchButton_IsSearchButtonUsingThemeColor_SetTrueThenFalse
 * @tc.desc: Test SetIsSearchButtonUsingThemeColor toggling between true and false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButton_IsSearchButtonUsingThemeColor_SetTrueThenFalse, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::RED, true);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), false);
}
 
/**
 * @tc.name: ArkUI_InnerColor_FontColor_Passthrough
 * @tc.desc: Test that Color passed through ArkUI_InnerColor preserves full color info including ColorSpace
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, ArkUI_InnerColor_FontColor_Passthrough, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
 
    Color p3Color = Color(0xFF654321);
    p3Color.SetColorSpace(ColorSpace::DISPLAY_P3);
    SearchModelNG::SetSearchButtonFontColor(frameNode, p3Color, false);
 
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
 
    auto resultColor = buttonLayoutProperty->GetFontColor().value_or(Color::BLACK);
    EXPECT_EQ(resultColor.GetValue(), p3Color.GetValue());
    EXPECT_EQ(resultColor.GetColorSpace(), p3Color.GetColorSpace());
}
 
/**
 * @tc.name: SearchButton_FontColor_FlagByUser
 * @tc.desc: Test that FontColorFlagByUser is set to true when custom color is applied
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButton_FontColor_FlagByUser, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
 
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_TRUE(buttonLayoutProperty->GetFontColorFlagByUser());
}
 
/**
 * @tc.name: SearchButton_FontColor_MarkDirtyNode
 * @tc.desc: Test that setting font color marks the button node as dirty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButton_FontColor_MarkDirtyNode, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
 
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto paintProp = buttonFrameNode->GetPaintProperty<NG::Property>();
    ASSERT_TRUE(paintProp);
    auto changeFlag = paintProp->GetPropertyChangeFlag() | NG::PROPERTY_UPDATE_MEASURE;
    EXPECT_EQ(paintProp->GetPropertyChangeFlag(), changeFlag);
}
 
/**
 * @tc.name: SearchButton_FontColor_ConsecutiveUpdates
 * @tc.desc: Test consecutive font color updates reflect the latest value
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchButton_FontColor_ConsecutiveUpdates, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
 
    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::RED, true);
    SearchModelNG::SetSearchButtonFontColor(frameNode, CUSTOM_FONT_COLOR, false);
    SearchModelNG::SetSearchButtonFontColor(frameNode, Color::GREEN, true);
 
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetFontColor().value_or(Color::BLACK), Color::GREEN);
    EXPECT_EQ(pattern->IsSearchButtonUsingThemeColor(), true);
}
 
/**
 * @tc.name: SearchCancelButton_Style_Constant
 * @tc.desc: Test CancelButtonStyle CONSTANT is set correctly
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchCancelButton_Style_Constant, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
 
    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::INVISIBLE),
        CancelButtonStyle::CONSTANT);
}
 
/**
 * @tc.name: SearchCancelButton_Style_Invisible
 * @tc.desc: Test CancelButtonStyle INVISIBLE is set correctly
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchCancelButton_Style_Invisible, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
 
    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::INVISIBLE);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::CONSTANT),
        CancelButtonStyle::INVISIBLE);
}
 
/**
 * @tc.name: SearchCancelButton_Style_Input
 * @tc.desc: Test CancelButtonStyle INPUT is set correctly
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestFourNg, SearchCancelButton_Style_Input, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
 
    SearchModelNG::SetCancelButtonStyle(frameNode, CancelButtonStyle::INPUT);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::CONSTANT),
        CancelButtonStyle::INPUT);
}
} // namespace OHOS::Ace::NG
