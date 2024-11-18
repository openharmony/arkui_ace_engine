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
    auto textFieldEventHub = frameNode_->GetEventHub<TextFieldEventHub>();

    textFieldEventHub->SetOnInputFilterError([](std::string errorText) { ASSERT_TRUE(errorText.empty()); });
    pattern_->UpdateInputFilterErrorText("");

    textFieldEventHub->SetOnInputFilterError([](std::string errorText) { ASSERT_FALSE(errorText.empty()); });
    pattern_->UpdateInputFilterErrorText("hasErrorText");
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

    layoutProperty->UpdateErrorText("This is Error Text");
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
    pattern_->contentController_->content_ = "hhh";
    pattern_->AdjustTextRectByCleanNode(rect);
    ASSERT_EQ(rect.Left(), 2);
    layoutProperty->UpdateCleanNodeStyle(CleanNodeStyle::INVISIBLE);
    pattern_->contentController_->content_ = "hhh";
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

    pattern_->contentController_->content_ = "123 456 abc def";
    ASSERT_EQ(pattern_->InsertOrDeleteSpace(3), true);

    pattern_->contentController_->content_ = "123 456 abc def";
    ASSERT_EQ(pattern_->InsertOrDeleteSpace(4), true);

    pattern_->contentController_->content_ = "123 456 abc def";
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
} // namespace OHOS::Ace::NG