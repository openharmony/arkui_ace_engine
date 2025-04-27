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

#include "text_input_base.h"

#include "test/mock/core/render/mock_paragraph.h"

#include "core/text/text_emoji_processor.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestFive : public TextInputBases {
public:
};

/**
 * @tc.name: UpdateInputFilterErrorText001
 * @tc.desc: test testInput text UpdateInputFilterErrorText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, UpdateInputFilterErrorText001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();

    textFieldEventHub->SetOnInputFilterError([](std::u16string errorText) { ASSERT_TRUE(errorText.empty()); });
    pattern_->UpdateInputFilterErrorText(u"");

    textFieldEventHub->SetOnInputFilterError([](std::u16string errorText) { ASSERT_FALSE(errorText.empty()); });
    pattern_->UpdateInputFilterErrorText(u"hasErrorText");
}

/**
 * @tc.name: RequestFocusReasonToString001
 * @tc.desc: test testInput text RequestFocusReasonToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, RequestFocusReasonToString001, TestSize.Level0)
{
    CreateTextField();
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::DRAG_END), "DragEnd");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::DRAG_MOVE), "DragMove");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::CLICK), "Click");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::LONG_PRESS), "LongPress");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::AUTO_FILL), "AutoFill");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::CLEAN_NODE), "CleanNode");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::UNKNOWN), "Unknown");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(static_cast<RequestFocusReason>(999)), "Unknown");
}

/**
 * @tc.name: RequestKeyboardReasonToString001
 * @tc.desc: test testInput text RequestKeyboardReasonToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, RequestKeyboardReasonToString001, TestSize.Level0)
{
    CreateTextField();
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::ON_KEY_EVENT), "KeyEvent");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SINGLE_CLICK), "SingleClick");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::DOUBLE_CLICK), "DoubleClick");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::LONG_PRESS), "LongPress");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::RESET_KEYBOARD), "ResetKeyboard");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SET_SELECTION), "SetSelection");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SEARCH_REQUEST), "SearchRequest");
    ASSERT_EQ(
        pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::AUTO_FILL_REQUEST_FAIL), "AutoFillRequestFail");
    ASSERT_EQ(
        pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SHOW_KEYBOARD_ON_FOCUS), "ShowKeyboardOnFocus");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::STYLUS_DETECTOR), "StylusDetector");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::CUSTOM_KEYBOARD), "CustomKeyboard");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::UNKNOWN), "Unknown");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(static_cast<RequestKeyboardReason>(999)), "Unknown");
}

/**
 * @tc.name: TextInputTypeToString001
 * @tc.desc: test testInput text TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextInputTypeToString001, TestSize.Level0)
{
    CreateTextField();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.NUMBER");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Number");
    layoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.EMAIL");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Email");
    layoutProperty->UpdateTextInputType(TextInputType::PHONE);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.PHONE_NUMBER");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.PhoneNumber");
    layoutProperty->UpdateTextInputType(TextInputType::URL);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.URL");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.URL");
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Password");
    layoutProperty->UpdateTextInputType(TextInputType::USER_NAME);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.USER_NAME");
    layoutProperty->UpdateTextInputType(TextInputType::NEW_PASSWORD);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.NEW_PASSWORD");
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER_PASSWORD);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.NUMBER_PASSWORD");
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER_DECIMAL);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.NUMBER_DECIMAL");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.NUMBER_DECIMAL");
    layoutProperty->UpdateTextInputType(static_cast<TextInputType>(999));
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.NORMAL");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Normal");
}

/**
 * @tc.name: GetInputStyleString001
 * @tc.desc: test testInput text GetInputStyleString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, GetInputStyleString001, TestSize.Level0)
{
    CreateTextField();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextContentStyle.INLINE");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextInputStyle.Inline");
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextContentStyle.DEFAULT");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextInputStyle.Default");
    paintProperty->UpdateInputStyle(static_cast<InputStyle>(999));
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextContentStyle.DEFAULT");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextInputStyle.Default");
}


/**
 * @tc.name: SetShowError001
 * @tc.desc: test testInput text SetShowError
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, SetShowError001, TestSize.Level0)
{
    CreateTextField();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();

    pattern_->SetShowError();
    ASSERT_EQ(pattern_->underlineWidth_, Dimension(1.0_px));

    layoutProperty->UpdateErrorText(u"This is Error Text");
    layoutProperty->UpdateShowErrorText(true);
    layoutProperty->UpdateShowUnderline(true);
    pattern_->SetShowError();
    ASSERT_EQ(pattern_->underlineWidth_, Dimension(2.0_px));

    layoutProperty->UpdateShowUnderline(false);
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    BorderWidthProperty borderWidthProperty;
    paintProperty->UpdateBorderWidthFlagByUser(borderWidthProperty);
    pattern_->SetShowError();
    ASSERT_FALSE(paintProperty->HasInnerBorderWidth());

    paintProperty->ResetBorderWidthFlagByUser();
    pattern_->SetShowError();
    ASSERT_EQ(paintProperty->GetInnerBorderWidthValue(), Dimension(1.0_vp));
}

/**
 * @tc.name: GetPaddingByUserValue001
 * @tc.desc: test testInput text GetPaddingByUserValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, GetPaddingByUserValue001, TestSize.Level0)
{
    CreateTextField();
    auto theme = pattern_->GetTheme();
    CHECK_NULL_VOID(theme);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    PaddingProperty padding;
    paintProperty->UpdatePaddingByUser(padding);
    theme->padding_ = Edge(1, 3, 2, 4);
    PaddingProperty paddingWhenEmpty = pattern_->GetPaddingByUserValue();
    ASSERT_EQ(paddingWhenEmpty.left, CalcLength(1));
    ASSERT_EQ(paddingWhenEmpty.right, CalcLength(2));
    ASSERT_EQ(paddingWhenEmpty.top, CalcLength(3));
    ASSERT_EQ(paddingWhenEmpty.bottom, CalcLength(4));

    padding.SetEdges(CalcLength(1), CalcLength(2), CalcLength(3), CalcLength(4));
    paintProperty->UpdatePaddingByUser(padding);
    theme->padding_ = Edge(5, 7, 6, 8);
    PaddingProperty paddingWhenHasValue = pattern_->GetPaddingByUserValue();
    ASSERT_EQ(paddingWhenEmpty.left, CalcLength(1));
    ASSERT_EQ(paddingWhenEmpty.right, CalcLength(2));
    ASSERT_EQ(paddingWhenEmpty.top, CalcLength(3));
    ASSERT_EQ(paddingWhenEmpty.bottom, CalcLength(4));
}

/**
 * @tc.name: AdjustTextRectByCleanNode001
 * @tc.desc: test testInput text AdjustTextRectByCleanNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, AdjustTextRectByCleanNode001, TestSize.Level0)
{
    CreateTextField();
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    auto theme = pattern_->GetTheme();
    pattern_->cleanNodeResponseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    RectF rect;
    layoutProperty->layoutDirection_ = TextDirection::LTR;
    pattern_->AdjustTextRectByCleanNode(rect);
    ASSERT_EQ(rect.Left(), 0);
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    layoutProperty->UpdateCleanNodeStyle(CleanNodeStyle::CONSTANT);
    theme->padding_ = Edge(1,3,2,4);
    pattern_->AdjustTextRectByCleanNode(rect);
    ASSERT_EQ(rect.Left(), 1);
    layoutProperty->UpdateCleanNodeStyle(CleanNodeStyle::INPUT);
    pattern_->AdjustTextRectByCleanNode(rect);
    ASSERT_EQ(rect.Left(), 1);
    pattern_->contentController_->content_ = u"hhh";
    pattern_->AdjustTextRectByCleanNode(rect);
    ASSERT_EQ(rect.Left(), 2);
    layoutProperty->UpdateCleanNodeStyle(CleanNodeStyle::INVISIBLE);
    pattern_->contentController_->content_ = u"hhh";
    pattern_->AdjustTextRectByCleanNode(rect);
    ASSERT_EQ(rect.Left(), 2);
}

/**
 * @tc.name: InsertOrDeleteSpace001
 * @tc.desc: test testInput text InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, InsertOrDeleteSpace001, TestSize.Level0)
{
    CreateTextField();
    ASSERT_EQ(pattern_->InsertOrDeleteSpace(-1), false);

    pattern_->contentController_->content_ = u"123 456 abc def";
    ASSERT_EQ(pattern_->InsertOrDeleteSpace(3), true);

    pattern_->contentController_->content_ = u"123 456 abc def";
    ASSERT_EQ(pattern_->InsertOrDeleteSpace(4), true);

    pattern_->contentController_->content_ = u"123 456 abc def";
    ASSERT_EQ(pattern_->InsertOrDeleteSpace(5), true);

    ASSERT_EQ(pattern_->InsertOrDeleteSpace(999), false);
}

/**
 * @tc.name: IsTextEditableForStylus001
 * @tc.desc: test testInput text IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, IsTextEditableForStylus001, TestSize.Level0)
{
    CreateTextField();
    auto focusHub = frameNode_->GetFocusHub();
    auto renderContext = frameNode_->GetRenderContext();
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    focusHub->focusType_ = FocusType::DISABLE;
    ASSERT_EQ(pattern_->IsTextEditableForStylus(), false);

    focusHub->focusType_ = FocusType::NODE;
    renderContext->UpdateOpacity(0);
    ASSERT_EQ(pattern_->IsTextEditableForStylus(), false);

    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    renderContext->UpdateOpacity(10);
    ASSERT_EQ(pattern_->IsTextEditableForStylus(), true);
}

/**
 * @tc.name: UpdateContentScroller001
 * @tc.desc: test testInput text UpdateContentScroller
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, UpdateContentScroller001, TestSize.Level0)
{
    CreateTextField();
    Offset offset(1, 1);
    pattern_->UpdateContentScroller(offset);
    ASSERT_EQ(pattern_->contentScroller_.stepOffset, 0);

    pattern_->contentRect_ = RectF(0, 0, 600, 900);
    pattern_->UpdateContentScroller(offset);
    ASSERT_EQ(pattern_->contentScroller_.stepOffset, 0);

    pattern_->moveCaretState_.isMoveCaret = true;
    pattern_->UpdateContentScroller(offset);
    ASSERT_TRUE(NearEqual(pattern_->contentScroller_.stepOffset, 35.8395));

    pattern_->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(pattern_->axis_);
    pattern_->SetScrollEnabled(true);
    pattern_->UpdateContentScroller(offset);
    ASSERT_TRUE(NearEqual(pattern_->contentScroller_.stepOffset, 35.8395));

    pattern_->contentScroller_.isScrolling = true;
    pattern_->UpdateContentScroller(offset);
    ASSERT_TRUE(NearEqual(pattern_->contentScroller_.stepOffset, 35.8395));

    pattern_->contentScroller_.isScrolling = false;
    pattern_->UpdateContentScroller(offset);
    ASSERT_TRUE(NearEqual(pattern_->contentScroller_.stepOffset, 35.8395));

    offset = Offset(7, 0);
    pattern_->UpdateContentScroller(offset);
    ASSERT_TRUE(NearEqual(pattern_->contentScroller_.stepOffset, 29.5639));
}

/**
 * @tc.name: GetAcceptedTouchLocationInfo001
 * @tc.desc: test testInput text GetAcceptedTouchLocationInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, GetAcceptedTouchLocationInfo001, TestSize.Level0)
{
    CreateTextField();
    TouchEventInfo touchEventInfo = TouchEventInfo("type");
    ASSERT_EQ(pattern_->GetAcceptedTouchLocationInfo(touchEventInfo), std::nullopt);
    std::list<TouchLocationInfo> changedTouches;
    TouchLocationInfo touchLocationInfo(100);
    changedTouches.emplace_back(touchLocationInfo);
    touchEventInfo.changedTouches_ = changedTouches;
    ASSERT_EQ(pattern_->GetAcceptedTouchLocationInfo(touchEventInfo)->GetFingerId(), 100);
    pattern_->moveCaretState_.isMoveCaret = true;
    ASSERT_EQ(pattern_->GetAcceptedTouchLocationInfo(touchEventInfo), std::nullopt);
    pattern_->moveCaretState_.touchFingerId = 100;
    ASSERT_EQ(pattern_->GetAcceptedTouchLocationInfo(touchEventInfo)->GetFingerId(), 100);
}

/**
 * @tc.name: GetPaddingRight001
 * @tc.desc: test testInput text GetPaddingRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, GetPaddingRight001, TestSize.Level0)
{
    CreateTextField();
    ASSERT_TRUE(NearEqual(pattern_->GetPaddingRight(), 2.0));
    PaddingPropertyF padding;
    padding.right = 10.0;
    pattern_->utilPadding_ = padding;
    ASSERT_EQ(pattern_->GetPaddingRight(), 10.0);
    pattern_->utilPadding_.reset();
    ASSERT_TRUE(NearEqual(pattern_->GetPaddingRight(), 2.0));
}

/**
 * @tc.name: GetBorder001
 * @tc.desc: test testInput text GetBorder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, GetBorder001, TestSize.Level0)
{
    CreateTextField();
    BorderWidthProperty border;
    Dimension borderDimenPx(1.0, DimensionUnit::PX);
    border.leftDimen = borderDimenPx;
    border.rightDimen = borderDimenPx;
    border.topDimen = borderDimenPx;
    border.bottomDimen = borderDimenPx;
    ASSERT_EQ(pattern_->GetBorderLeft(border), 1.0);
    ASSERT_EQ(pattern_->GetBorderRight(border), 1.0);
    ASSERT_EQ(pattern_->GetBorderTop(border), 1.0);
    ASSERT_EQ(pattern_->GetBorderBottom(border), 1.0);
    Dimension borderDimenPe(1.0, DimensionUnit::PERCENT);
    border.leftDimen = borderDimenPe;
    border.rightDimen = borderDimenPe;
    border.topDimen = borderDimenPe;
    border.bottomDimen = borderDimenPe;
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.percentReference.width_ = 0;
    frameNode_->geometryNode_->parentLayoutConstraint_ = layoutConstraintF;
    ASSERT_EQ(pattern_->GetBorderLeft(border), 0.0);
    ASSERT_EQ(pattern_->GetBorderRight(border), 0.0);
    ASSERT_EQ(pattern_->GetBorderTop(border), 0.0);
    ASSERT_EQ(pattern_->GetBorderBottom(border), 0.0);
    frameNode_->geometryNode_->parentLayoutConstraint_->percentReference.width_ = 10.0;
    ASSERT_EQ(pattern_->GetBorderLeft(border), 10.0);
    ASSERT_EQ(pattern_->GetBorderRight(border), 10.0);
    ASSERT_EQ(pattern_->GetBorderTop(border), 10.0);
    ASSERT_EQ(pattern_->GetBorderBottom(border), 10.0);
}

/**
 * @tc.name: DeleteWord001
 * @tc.desc: test testInput delete word function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, DeleteWord001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField("hello world", "", [](TextFieldModelNG model) {});
    auto paragraph = AceType::MakeRefPtr<MockParagraph>();
    pattern_->paragraph_ = paragraph;

    /**
     * @tc.steps: step2. set caret pos
     */
    pattern_->SetCaretPosition(5);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);

    /**
     * @tc.steps: step3. delete left word
     */
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _)).WillRepeatedly(
        [] (int32_t offset, int32_t& start, int32_t& end) {
            offset = 5;
            start = 0;
            end = 5;
            return true;
    });
    pattern_->HandleOnDeleteComb(true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), " world");

    /**
     * @tc.steps: step4. delete right word
     */
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _)).WillRepeatedly(
        [] (int32_t offset, int32_t& start, int32_t& end) {
            offset = 1;
            start = 1;
            end = 6;
            return true;
    });
    pattern_->SetCaretPosition(0);
    pattern_->HandleOnDeleteComb(false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), " world");

    /**
     * @tc.steps: step5. undo to begining
     */
    pattern_->HandleOnUndoAction();
    pattern_->HandleOnUndoAction();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "hello world");

    /**
     * @tc.steps: step6. set RTL
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step7. delete left word
     */
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _)).WillRepeatedly(
        [] (int32_t offset, int32_t& start, int32_t& end) {
            offset = 0;
            start = 0;
            end = 0;
            return true;
    });
    pattern_->SetCaretPosition(0);
    pattern_->HandleOnDeleteComb(true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "hello world");

    /**
     * @tc.steps: step8. delete right word
     */
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _)).WillRepeatedly(
        [] (int32_t offset, int32_t& start, int32_t& end) {
            offset = 0;
            start = 0;
            end = 5;
            return true;
    });
    pattern_->SetCaretPosition(0);
    pattern_->HandleOnDeleteComb(false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "hello world");

    /**
     * @tc.steps: step9. test Chinese
     */
    CreateTextField("你好世界", "", [](TextFieldModelNG model) {});
    paragraph = AceType::MakeRefPtr<MockParagraph>();
    pattern_->paragraph_ = paragraph;

    /**
     * @tc.steps: step10. set caret pos
     */
    pattern_->SetCaretPosition(2);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 2);

    /**
     * @tc.steps: step11. delete left word
     */
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _)).WillRepeatedly(
        [] (int32_t offset, int32_t& start, int32_t& end) {
            offset = 2;
            start = 0;
            end = 2;
            return true;
    });
    pattern_->HandleOnDeleteComb(true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "世界");

    /**
     * @tc.steps: step12. delete right word
     */
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _)).WillRepeatedly(
        [] (int32_t offset, int32_t& start, int32_t& end) {
            offset = 0;
            start = 0;
            end = 2;
            return true;
    });
    pattern_->SetCaretPosition(0);
    pattern_->HandleOnDeleteComb(false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "世界");
}

/**
 * @tc.name: PageUpOrDown001
 * @tc.desc: test testInput page up/down function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, PageUpOrDown001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField("hello world", "", [](TextFieldModelNG model) {});

    /**
     * @tc.steps: step2. set caret pos
     */
    pattern_->SetCaretPosition(5);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);

    /**
     * @tc.steps: step3. page up
     */
    pattern_->HandleOnPageUp();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);

    /**
     * @tc.steps: step4. page down
     */
    pattern_->HandleOnPageDown();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
}

/**
 * @tc.name: IssueFixTest001
 * @tc.desc: test be fixed issue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, IssueFixTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField("hello world", "", [](TextFieldModelNG model) {});

    /**
     * Use the tab key to focus and do not display dual handles
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    event.pressedCodes = { KeyCode::KEY_TAB };
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->SelectOverlayIsOn(), false);

    /**
     * The content is empty, use ctrl+a to select all, the cursor should not disappear
     */
    pattern_->contentController_->content_ = u"";
    GetFocus();
    pattern_->SetCaretPosition(0);
    pattern_->HandleOnSelectAll();
    EXPECT_EQ(pattern_->isCaretTwinkling_, true);
    EXPECT_EQ(pattern_->cursorVisible_, true);

    /**
     * press tab, HandleOnEscape should return false
     */
    GetFocus();
    EXPECT_EQ(pattern_->HandleOnEscape(), false);

    /**
     * password focus box rect is diffent between LRT and RTL
     */
    CreateTextField("hello world", "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    pattern_->contentController_->content_ = u"hello world";
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(10);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(0);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetWidth(100);
    layoutConstraint.selfIdealSize.SetHeight(100);
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle,
        pattern_->contentController_->content_, 1.0_px, layoutConstraint, &layoutWrapper);
    FlushLayoutTask(frameNode_);
    RoundRect ltrFocusRect;
    pattern_->GetInnerFocusPaintRect(ltrFocusRect);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    RoundRect rtlFocusRect;
    pattern_->GetInnerFocusPaintRect(rtlFocusRect);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_NE(ltrFocusRect.GetRect().GetX(), rtlFocusRect.GetRect().GetX());

    /**
     * password mode can enter special characters
     */
    CreateTextField("hello world £¥$€", "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    EXPECT_EQ(pattern_->GetTextValue(), "hello world £¥$€");
    CreateTextField("hello world £¥$€", "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::NEW_PASSWORD);
    });
    EXPECT_EQ(pattern_->GetTextValue(), "hello world £¥$€");
    // reset
    CreateTextField("hello world", "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    EXPECT_EQ(pattern_->GetTextValue(), "hello world");
}

/**
 * @tc.name: TextEmojiInputTest001
 * @tc.desc: test text emoji processor function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextEmojiInputTest001, TestSize.Level0)
{
    /**
     * normal text
     */
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    std::u16string test1 = u"ABCD";
    EmojiRelation result =  TextEmojiProcessor::GetIndexRelationToEmoji(0, test1, startIndex, endIndex);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 0);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(0, test1), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(0, test1), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(0, test1, startIndex, endIndex), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(0, test1, startIndex, endIndex), false);

    /**
     * emoji text
     */
    std::u16string test2 = u"😅";
    result =  TextEmojiProcessor::GetIndexRelationToEmoji(0, test2, startIndex, endIndex);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 0);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(0, test2), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(0, test2), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(0, test2, startIndex, endIndex), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(0, test2, startIndex, endIndex), false);

    result =  TextEmojiProcessor::GetIndexRelationToEmoji(1, test2, startIndex, endIndex);
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 1);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(1, test2), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(1, test2), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(1, test2, startIndex, endIndex), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(1, test2, startIndex, endIndex), false);

    result =  TextEmojiProcessor::GetIndexRelationToEmoji(2, test2, startIndex, endIndex);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(2, test2), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(2, test2), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(2, test2, startIndex, endIndex), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(2, test2, startIndex, endIndex), false);

    EXPECT_EQ(TextEmojiProcessor::SubU16string(0, 1, test2, false), u"\xD83D");
    EXPECT_EQ(TextEmojiProcessor::SubU16string(0, 1, test2, true), u"\xD83D");

    /**
     * long emoji text
     */
    std::u16string test3 = u"😅😅😅😅😅😅😅";
    result =  TextEmojiProcessor::GetIndexRelationToEmoji(0, test3, startIndex, endIndex);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 0);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(0, test3), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(0, test3), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(0, test3, startIndex, endIndex), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(0, test3, startIndex, endIndex), false);

    result =  TextEmojiProcessor::GetIndexRelationToEmoji(3, test3, startIndex, endIndex);
    EXPECT_EQ(startIndex, 3);
    EXPECT_EQ(endIndex, 3);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(3, test3), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(3, test3), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(3, test3, startIndex, endIndex), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(3, test3, startIndex, endIndex), false);

    result =  TextEmojiProcessor::GetIndexRelationToEmoji(14, test3, startIndex, endIndex);
    EXPECT_EQ(startIndex, 14);
    EXPECT_EQ(endIndex, 14);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(14, test3), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(14, test3), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexBeforeOrInEmoji(14, test3, startIndex, endIndex), false);
    EXPECT_EQ(TextEmojiProcessor::IsIndexAfterOrInEmoji(14, test3, startIndex, endIndex), false);

    EXPECT_EQ(TextEmojiProcessor::SubU16string(0, 3, test3, false), u"😅\xD83D");
    EXPECT_EQ(TextEmojiProcessor::SubU16string(0, 3, test3, true), u"😅\xD83D");
}

/**
 * @tc.name: TextFieldControllerAddTextTest
 * @tc.desc: test textfield controller AddText function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldControllerAddTextTest, TestSize.Level0)
{
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    pattern_->textFieldController_->AddText(u"123", -1);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "123");

    pattern_->textFieldController_->AddText(u"A", 1);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "1A23");
}

/**
 * @tc.name: TextFieldControllerRemoveTextTest
 * @tc.desc: test textfield controller RemoveText function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldControllerRemoveTextTest, TestSize.Level0)
{
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    pattern_->textFieldController_->DeleteText(0, 1);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "23");

    pattern_->textFieldController_->DeleteText(-1, -1);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "");
}

/**
 * @tc.name: TextFieldControllerGetSelectionTest
 * @tc.desc: test textfield controller GetSelection function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldControllerGetSelectionTest, TestSize.Level0)
{
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    SelectionInfo info = pattern_->textFieldController_->GetSelection();
    auto selectionStart = info.GetSelection().selection[0];
    auto selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 3);
    EXPECT_EQ(selectionEnd, 3);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    FlushLayoutTask(frameNode_);
    info = pattern_->textFieldController_->GetSelection();
    selectionStart = info.GetSelection().selection[0];
    selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 2);
    EXPECT_EQ(selectionEnd, 2);
}

/**
 * @tc.name: EmojiCalSubU16stringRange
 * @tc.desc: test CalSubU16stringRange function
 * @tc.type: FUNC
 */
 HWTEST_F(TextFieldPatternTestFive, EmojiCalSubU16stringRange, TestSize.Level0)
 {
    // cases 1
    // test CalSubU16stringRange function - normal
    int32_t index = 0;
    int32_t length = 5;
    std::u16string content = u"Hello";
    bool includeStartHalf = true;
    bool includeEndHalf = true;
    TextEmojiSubStringRange expected_1 = {0, 5};

    TextEmojiSubStringRange result_1 =
        TextEmojiProcessor::CalSubU16stringRange(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected_1.startIndex, result_1.startIndex);
    EXPECT_EQ(expected_1.endIndex, result_1.endIndex);

    // case 2
    // test CalSubU16stringRange function - boundary
    index = 0;
    length = 0;
    content = u"";
    includeStartHalf = false;
    includeEndHalf = false;
    TextEmojiSubStringRange expected_2 = {0, 0};

    TextEmojiSubStringRange result_2 =
        TextEmojiProcessor::CalSubU16stringRange(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected_2.startIndex, result_2.startIndex);
    EXPECT_EQ(expected_2.endIndex, result_2.endIndex);

    // case 3
    // test CalSubU16stringRange function - include emoji
    index = 0;
    length = 2;
    content = u"😊Hello";
    includeStartHalf = true;
    includeEndHalf = true;
    TextEmojiSubStringRange expected_3 = {0, 2};

    TextEmojiSubStringRange result_3 =
        TextEmojiProcessor::CalSubU16stringRange(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected_3.startIndex, result_3.startIndex);
    EXPECT_EQ(expected_3.endIndex, result_3.endIndex);

    // case 4
    // test CalSubU16stringRange function - no include emoji
    index = 2;
    length = 3;
    content = u"Hello😊";
    includeStartHalf = false;
    includeEndHalf = false;
    TextEmojiSubStringRange expected_4 = {2, 5};

    TextEmojiSubStringRange result_4 =
        TextEmojiProcessor::CalSubU16stringRange(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected_4.startIndex, result_4.startIndex);
    EXPECT_EQ(expected_4.endIndex, result_4.endIndex);

    // case 5
    // test CalSubU16stringRange function - length is INT32_MAX
    index = 2;
    length = INT32_MAX;
    content = u"Hello😊";
    includeStartHalf = false;
    includeEndHalf = false;
    TextEmojiSubStringRange expected_5;
    if (std::numeric_limits<long>::max() == INT32_MAX) {
        expected_5 = {2, -2147483647};
    } else {
        expected_5 = {2, 2147483647};
    }

    TextEmojiSubStringRange result_5 =
        TextEmojiProcessor::CalSubU16stringRange(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected_5.startIndex, result_5.startIndex);
    EXPECT_EQ(expected_5.endIndex, result_5.endIndex);
}

/**
 * @tc.name: EmojiSubU16string
 * @tc.desc: test SubU16string function
 * @tc.type: FUNC
 */
 HWTEST_F(TextFieldPatternTestFive, EmojiSubU16string, TestSize.Level0)
 {
    // case 1
    // test SubU16string function - normal
    std::u16string content = u"🐶Hello, 🐱world!";
    int32_t index = 0;
    int32_t length = 11;
    bool includeStartHalf = true;
    bool includeEndHalf = true;

    std::u16string expected = u"🐶Hello, 🐱";
    std::u16string result =
        TextEmojiProcessor::SubU16string(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected, result);

    // case 2
    // test SubU16string function - empty
    content = u"";
    index = 0;
    length = 0;
    includeStartHalf = false;
    includeEndHalf = false;

    expected = u"";
    result = TextEmojiProcessor::SubU16string(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected, result);

    // case 3
    // test SubU16string function - includeStartHalf is true
    content = u"Hello, 🐱world!";
    index = 0;
    length = 5;
    includeStartHalf = true;
    includeEndHalf = false;

    expected = u"Hello";
    result = TextEmojiProcessor::SubU16string(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected, result);

    // case 4
    // test SubU16string function - includeEndHalf is true
    content = u"Hello, 🐱world!";
    index = 7;
    length = 5;
    includeStartHalf = false;
    includeEndHalf = true;

    expected = u"🐱wor";
    result = TextEmojiProcessor::SubU16string(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected, result);

    // case 5
    // test SubU16string function - length is 0
    content = u"Hello, 🐱world!";
    index = 0;
    length = 0;
    includeStartHalf = false;
    includeEndHalf = false;

    expected = u"";
    result = TextEmojiProcessor::SubU16string(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected, result);

    // case 6
    // test SubU16string function - length is INT_MAX
    content = u"Hello, 🐱world!";
    index = 0;
    length = INT_MAX;
    includeStartHalf = false;
    includeEndHalf = false;

    expected = u"Hello, 🐱world!";
    result = TextEmojiProcessor::SubU16string(index, length, content, includeStartHalf, includeEndHalf);

    EXPECT_EQ(expected, result);
}

/**
 * @tc.name: EmojiConvertU8stringUnpairedSurrogates
 * @tc.desc: test ConvertU8stringUnpairedSurrogates function
 * @tc.type: FUNC
 */
 HWTEST_F(TextFieldPatternTestFive, EmojiConvertU8stringUnpairedSurrogates, TestSize.Level0)
 {
    // case 1
    // test ConvertU8stringUnpairedSurrogates function - normal
    std::string input = std::string("😓").substr(0, 1);
    std::string expected = "�";

    std::string result = TextEmojiProcessor::ConvertU8stringUnpairedSurrogates(input);

    EXPECT_EQ(expected, result);

    // case 2
    // test ConvertU8stringUnpairedSurrogates function - empty
    input = "";
    expected = "";

    result = TextEmojiProcessor::ConvertU8stringUnpairedSurrogates(input);

    EXPECT_EQ(expected, result);

    // case 3
    // test ConvertU8stringUnpairedSurrogates function - no unpaired surrogates
    input = "Hello, World!";
    expected = "Hello, World!";

    result = TextEmojiProcessor::ConvertU8stringUnpairedSurrogates(input);

    EXPECT_EQ(expected, result);

    // case 3
    // test ConvertU8stringUnpairedSurrogates function - multiple unpaired surrogates
    input = std::string("😓").substr(0, 1) + std::string("😓").substr(0, 1) + std::string("😓").substr(0, 1);
    expected = "���";

    result = TextEmojiProcessor::ConvertU8stringUnpairedSurrogates(input);

    EXPECT_EQ(expected, result);
}

/**
 * @tc.name: TextFieldControllerClearPreviewTextTest
 * @tc.desc: test textfield controller ClearPreviewText function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldControllerClearPreviewTextTest, TestSize.Level0)
{
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    PreviewTextInfo info = {
        .text = u"abc",
        .range = {0, 2}
    };
    pattern_->SetPreviewTextOperation(info);
    EXPECT_TRUE(pattern_->GetIsPreviewText());
    FlushLayoutTask(frameNode_);

    pattern_->textFieldController_->ClearPreviewText();
    EXPECT_FALSE(pattern_->GetIsPreviewText());
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: TextFieldControllerGetTextTest
 * @tc.desc: test textfield controller GetText function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldControllerGetTextTest, TestSize.Level0)
{
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();
    FlushLayoutTask(frameNode_);

    pattern_->contentController_->content_ = u"123";
    EXPECT_EQ(pattern_->textFieldController_->GetText(), u"123");

    pattern_->contentController_->content_ = u"";
    EXPECT_EQ(pattern_->textFieldController_->GetText(), u"");

    pattern_->contentController_->content_ = u"😓";
    EXPECT_EQ(pattern_->textFieldController_->GetText(), u"😓");

    pattern_->contentController_->content_ = std::u16string(u"😓").substr(0, 1);
    EXPECT_EQ(pattern_->textFieldController_->GetText(), std::u16string(u"😓").substr(0, 1));
}

/**
 * @tc.name: TextFieldSelectControllerTest001
 * @tc.desc: test textfield select controller function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldSelectControllerTest001, TestSize.Level0)
{
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    SelectionInfo info = pattern_->textFieldController_->GetSelection();
    auto selectionStart = info.GetSelection().selection[0];
    auto selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 3);
    EXPECT_EQ(selectionEnd, 3);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    FlushLayoutTask(frameNode_);
    info = pattern_->textFieldController_->GetSelection();
    selectionStart = info.GetSelection().selection[0];
    selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 2);
    EXPECT_EQ(selectionEnd, 2);

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextAlign(TextAlign::END);
    auto rect = controller->CalculateEmptyValueCaretRect();
    EXPECT_EQ(rect.Height(), 50);
}

/**
 * @tc.name: TextFieldSelectControllerTest002
 * @tc.desc: test textfield select controller function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldSelectControllerTest002, TestSize.Level0)
{
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    SelectionInfo info = pattern_->textFieldController_->GetSelection();
    auto selectionStart = info.GetSelection().selection[0];
    auto selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 3);
    EXPECT_EQ(selectionEnd, 3);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    FlushLayoutTask(frameNode_);
    info = pattern_->textFieldController_->GetSelection();
    selectionStart = info.GetSelection().selection[0];
    selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 2);
    EXPECT_EQ(selectionEnd, 2);

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    auto rect = controller->CalculateEmptyValueCaretRect();
    EXPECT_EQ(rect.Height(), 50);

    layoutProperty->UpdateTextAlign(TextAlign::JUSTIFY);
    rect = controller->CalculateEmptyValueCaretRect();
    EXPECT_EQ(rect.Height(), 50);
}

/**
 * @tc.name: TextFieldSelectControllerTest003
 * @tc.desc: test textfield select controller function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldSelectControllerTest003, TestSize.Level0)
{
    CreateTextField("1234567", "7654321", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    SelectionInfo info = pattern_->textFieldController_->GetSelection();
    auto selectionStart = info.GetSelection().selection[0];
    auto selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 7);
    EXPECT_EQ(selectionEnd, 7);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    FlushLayoutTask(frameNode_);
    info = pattern_->textFieldController_->GetSelection();
    selectionStart = info.GetSelection().selection[0];
    selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 2);
    EXPECT_EQ(selectionEnd, 2);

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    auto rect = controller->CalculateEmptyValueCaretRect();
    EXPECT_EQ(rect.Height(), 50);
}

/**
 * @tc.name: TextFieldSelectControllerTest004
 * @tc.desc: test textfield select controller function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldSelectControllerTest004, TestSize.Level0)
{
    CreateTextField("1234567", "7654321", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    SelectionInfo info = pattern_->textFieldController_->GetSelection();
    auto selectionStart = info.GetSelection().selection[0];
    auto selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 7);
    EXPECT_EQ(selectionEnd, 7);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    FlushLayoutTask(frameNode_);
    info = pattern_->textFieldController_->GetSelection();
    selectionStart = info.GetSelection().selection[0];
    selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 2);
    EXPECT_EQ(selectionEnd, 2);

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    controller->UpdateParagraph(nullptr);
    auto rect = controller->CalculateEmptyValueCaretRect();
    EXPECT_EQ(rect.Height(), 50);
}

/**
 * @tc.name: TextFieldSelectControllerTest005
 * @tc.desc: test textfield select controller function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldSelectControllerTest005, TestSize.Level0)
{
    CreateTextField("1234567", "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    SelectionInfo info = pattern_->textFieldController_->GetSelection();
    auto selectionStart = info.GetSelection().selection[0];
    auto selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 7);
    EXPECT_EQ(selectionEnd, 7);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    FlushLayoutTask(frameNode_);
    info = pattern_->textFieldController_->GetSelection();
    selectionStart = info.GetSelection().selection[0];
    selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 2);
    EXPECT_EQ(selectionEnd, 2);

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    controller->UpdateParagraph(nullptr);
    auto rect = controller->CalculateEmptyValueCaretRect();
    EXPECT_EQ(rect.Height(), 50);
}

/**
 * @tc.name: TextFieldSelectControllerTest006
 * @tc.desc: test textfield select controller function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextFieldSelectControllerTest006, TestSize.Level0)
{
    CreateTextField("123", "7654321", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    SelectionInfo info = pattern_->textFieldController_->GetSelection();
    auto selectionStart = info.GetSelection().selection[0];
    auto selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 3);
    EXPECT_EQ(selectionEnd, 3);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    FlushLayoutTask(frameNode_);
    info = pattern_->textFieldController_->GetSelection();
    selectionStart = info.GetSelection().selection[0];
    selectionEnd = info.GetSelection().selection[1];
    EXPECT_EQ(selectionStart, 2);
    EXPECT_EQ(selectionEnd, 2);

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    controller->UpdateParagraph(nullptr);
    auto rect = controller->CalculateEmptyValueCaretRect();
    EXPECT_EQ(rect.Height(), 50);
}
} // namespace OHOS::Ace::NG