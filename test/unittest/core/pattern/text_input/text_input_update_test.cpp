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

class TextInputUpdateTestNg : public TextInputBases {
public:
};

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: Test textinput handle action.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, HandleLongPress001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::NUMBER_PASSWORD);
    });
    GetFocus();
    GestureEvent gestureEvent;

    /**
     * @tc.steps: step2. Set secondhandle. Call function HandleLongPress.
     * @tc.expected: Check if return true.
     */
    pattern_->obscureTickCountDown_ = 1;
    pattern_->longPressEvent_->operator()(gestureEvent);
    pattern_->processOverlayDelayTask_();
    EXPECT_TRUE(pattern_->showSelect_);
}

/**
 * @tc.name: InsertValueOperation001
 * @tc.desc: Test insert value operation.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, InsertValueOperation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetMaxLength(1000023);
    });
    EXPECT_FALSE(pattern_->HasFocus());

    /**
     * @tc.steps: step2. Call function InsertValueOperation.
     * @tc.expected: Check if result right.
     */
    auto insertValue = "Hello world";
    pattern_->InsertValueOperation(insertValue);
    EXPECT_EQ(pattern_->contentController_->GetTextValue().compare(insertValue), 0);
    pattern_->UpdateOverCounterColor();
}

/**
 * @tc.name: UpdateCounterBorderStyle001
 * @tc.desc: Test insert value operation.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, UpdateCounterBorderStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField("DEFAULT_TEXT", "", [](TextFieldModelNG model) {
        model.SetMaxLength(1000023);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Create text layoutWrapper. Call function InsertValueOperation.
     * @tc.expected: Check if result right.
     */
    pattern_->UpdateOverCounterColor();
    pattern_->UltralimitShake();
    auto errorText = "error text";
    pattern_->UpdateInputFilterErrorText(errorText);
    pattern_->OnAreaChangedInner();
    auto textLength = static_cast<int32_t>
        (pattern_->contentController_->GetWideText().length());
    auto maxlength = pattern_->GetMaxLength();
    pattern_->UpdateCounterBorderStyle(textLength, maxlength);
    EXPECT_TRUE(pattern_->counterChange_);
}

/**
 * @tc.name: DeleteBackwardWhenHasMaxLength001
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, DeleteBackwardWhenHasMaxLength001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node and call delete backward
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(1000023);
    });

    GetFocus();
    pattern_->DeleteBackward(5);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("abcdefghijklmnopqrstu"),
        0) << "Text is " + pattern_->GetTextValue();
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.length() - 5));
}

/**
 * @tc.name: GetWordLengthOutlier001
 * @tc.desc: GetWordLength passes in abnormal parameters.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetWordLengthOutlier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set originCaretPosition outlier. Call function GetWordLength.
     * @tc.expected: set originCaretPosition less then wideTextLong, return 0.
     */
    auto originCaretPosition = -1;
    auto directionMove = 2;
    EXPECT_EQ(pattern_->GetWordLength(originCaretPosition, directionMove), 0);

    /**
     * @tc.expected: set originCaretPosition greater then wideTextLong
     * @tc.expected: return 0
     */
    originCaretPosition = 27;
    EXPECT_EQ(pattern_->GetWordLength(originCaretPosition, directionMove), 0);
}

/**
 * @tc.name: GetWordLengthOutlier002
 * @tc.desc: GetWordLength passes in abnormal parameters.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetWordLengthOutlier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set originCaretPosition outlier. Call function GetWordLength.
     * @tc.expected: set originCaretPosition less then wideTextLong, return 0.
     */
    auto originCaretPosition = 0;
    auto directionMove = 0;
    EXPECT_EQ(pattern_->GetWordLength(originCaretPosition, directionMove), 0);

    /**
     * @tc.expected: set originCaretPosition greater then wideTextLong
     * @tc.expected: return 0
     */
    originCaretPosition = 26;
    directionMove = 1;
    EXPECT_EQ(pattern_->GetWordLength(originCaretPosition, directionMove), 0);
}

/**
 * @tc.name: GetLineBeginPositionOutlier001
 * @tc.desc: GetLineBeginPosition passes in abnormal parameters.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetLineBeginPositionOutlier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set originCaretPosition outlier. Call function GetLineBeginPosition.
     * @tc.expected: set originCaretPosition less then wideTextLong, return 0.
     */
    auto originCaretPosition = -1;
    EXPECT_EQ(pattern_->GetLineBeginPosition(originCaretPosition, false), 0);

    /**
     * @tc.expected: set originCaretPosition greater then wideTextLong
     * @tc.expected: return 0
     */
    originCaretPosition = 27;
    EXPECT_EQ(pattern_->GetLineBeginPosition(originCaretPosition, false), 0);

    originCaretPosition = 0;
    EXPECT_EQ(pattern_->GetLineBeginPosition(originCaretPosition, false), 0);
}

/**
 * @tc.name: GetLineEndPositionOutlier001
 * @tc.desc: GetLineEndPosition passes in abnormal parameters.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetLineEndPositionOutlier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set originCaretPosition outlier. Call function GetLineEndPosition.
     * @tc.expected: set originCaretPosition less then wideTextLong, return 0.
     */
    auto originCaretPosition = -1;
    EXPECT_EQ(pattern_->GetLineEndPosition(originCaretPosition, false), originCaretPosition);

    /**
     * @tc.expected: set originCaretPosition greater then wideTextLong
     * @tc.expected: return 0
     */
    originCaretPosition = 27;
    EXPECT_EQ(pattern_->GetLineEndPosition(originCaretPosition, false), originCaretPosition);

    originCaretPosition = 26;
    pattern_->HandleOnDelete(true);
    EXPECT_EQ(pattern_->GetLineEndPosition(originCaretPosition, false), originCaretPosition);
}

/**
 * @tc.name: CursorMoveLeftAfterSelected001
 * @tc.desc: Call function CursorMoveLeft.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, CursorMoveLeftAfterSelected001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set Select. Call function CursorMoveLeft.
     * @tc.expected:
     */
    pattern_->HandleSetSelection(5, 10, false);
    auto ret = pattern_->CursorMoveLeft();
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetCaretIndex(), 5) << "Text is " + pattern_->GetTextValue() +
        ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveLeftWord001
 * @tc.desc: Call function CursorMoveLeftWord.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, CursorMoveLeftWord001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_PLACE_HOLDER);
    GetFocus();

    /**
     * @tc.steps: step2. Set cursor at the beginning of the line.
     * @tc.expected:return true.
     */
    pattern_->SetCaretPosition(0);
    EXPECT_TRUE(pattern_->CursorMoveLeftWord());
}

/**
 * @tc.name: CursorMoveRightAfterSelected001
 * @tc.desc: Call function CursorMoveRight.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, CursorMoveRightAfterSelected001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_FALSE(pattern_->UpdateFocusForward());
    pattern_->CursorMoveRight();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Set Select. Call function CursorMoveRight.
     * @tc.expected:
     */
    pattern_->HandleSetSelection(5, 10, false);
    auto ret = pattern_->CursorMoveRight();
    EXPECT_FALSE(ret);
    EXPECT_EQ(pattern_->GetCaretIndex(), 10) << "Text is " + pattern_->GetTextValue() +
        ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: HandleCounterBorder001
 * @tc.desc: test testIput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, HandleCounterBorder001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength 0
     * @tc.expected: maxLength is 0
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(26);
    });
    GetFocus();

    /**
     * @tc.step: step2. test maxLength
     */
    pattern_->HandleCounterBorder();
    pattern_->HandleOnDelete(true);
    EXPECT_EQ(pattern_->GetMaxLength(), 26);
    EXPECT_EQ(pattern_->GetTextIndexAtCursor(), 26);
}

/**
 * @tc.name: GetShowPasswordIconString001
 * @tc.desc: Test GetShowPasswordIconString
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetShowPasswordIconString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. show password icon string.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(true);
    });

    EXPECT_EQ(pattern_->GetShowPasswordIconString(), "true");
}

/**
 * @tc.name: GetShowPasswordIconString002
 * @tc.desc: Test GetShowPasswordIconString
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetShowPasswordIconString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. show password icon string.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(false);
    });

    EXPECT_EQ(pattern_->GetShowPasswordIconString(), "false");
}

/**
 * @tc.name: GetErrorTextString001
 * @tc.desc: Test GetErrorTextString
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetErrorTextString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. show password icon string.
     */
    CreateTextField(DEFAULT_TEXT);

    pattern_->SearchRequestKeyboard();
    EXPECT_EQ(pattern_->GetErrorTextString(), "");
}

/**
 * @tc.name: GetBarStateString001
 * @tc.desc: test GetBarStateString
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetBarStateString001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     * @tc.expected: barState is DisplayMode::ON
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::ON);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetBarStateString(), "BarState.ON");
}

/**
 * @tc.name: GetBarStateString002
 * @tc.desc: test GetBarStateString
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetBarStateString002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     * @tc.expected: barState is DisplayMode::OFF
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::OFF);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetBarStateString(), "BarState.OFF");
}

/**
 * @tc.name: GetScrollBarWidth001
 * @tc.desc: test GetScrollBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, GetScrollBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     * @tc.expected: scrollBarWidth is 0.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Test Width
     */
    EXPECT_EQ(pattern_->GetScrollBarWidth(), 0);
}

/**
 * @tc.name: AddCounterNode001
 * @tc.desc: test AddCounterNode
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, AddCounterNode001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     * @tc.expected: counterTextNode_ is created
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Test counterTextNode_ is null
     */
    EXPECT_FALSE(pattern_->counterTextNode_.Upgrade());

    /**
     * @tc.step: step3. call AddCounterNode
     */
    pattern_->AddCounterNode();
    EXPECT_TRUE(pattern_->counterTextNode_.Upgrade());
    pattern_->ClearCounterNode();
}

/**
 * @tc.name: AdjustTextInReasonableArea
 * @tc.desc: test AdjustTextInReasonableArea
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, AdjustTextInReasonableArea, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps:set textRect
     */
    RectF textRect = RectF(0.0f, 0.0f, 800.0f, 60.0f);
    pattern_->SetTextRect(textRect);
    pattern_->AdjustTextInReasonableArea();
    EXPECT_EQ(pattern_->GetTextRect().GetOffset(), OffsetF(0.0f, 0.0f));

    /**
     * @tc.steps:set contentOffset, contentY > textY.
     */
    OffsetF contentOffset1(0.0f, 20.0f);
    pattern_->contentRect_.SetOffset(contentOffset1);
    pattern_->AdjustTextInReasonableArea();
    EXPECT_EQ(pattern_->GetTextRect().GetOffset(), OffsetF(0.0f, 10.0f));

    /**
     * @tc.steps:set contentOffset, contentX > textX.
     */
    OffsetF contentOffset2(90.0f, 0.0f);
    pattern_->contentRect_.SetOffset(contentOffset2);
    pattern_->AdjustTextInReasonableArea();
    EXPECT_EQ(pattern_->GetTextRect().GetOffset(), OffsetF(10.0f, 0.0f));
}

/**
 * @tc.name: HandleTouchUp
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TextInputUpdateTestNg, HandleTouchUp, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create location info, touch type DOWN
     */
    TouchLocationInfo touchLocationInfo1(0);
    touchLocationInfo1.touchType_ = TouchType::UP;
    touchLocationInfo1.localLocation_ = Offset(0.0f, 0.0f);

    /**
     * @tc.steps: step3. create touch info, touch type DOWN
     */
    TouchEventInfo touchInfo1("");
    touchInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));

    /**
     * @tc.steps: step4. test touch down
     */
    pattern_->isMousePressed_ = true;
    pattern_->HandleTouchEvent(touchInfo1);
    frameNode_->UpdateInspectorId("123");
    pattern_->OnAfterModifyDone();
    EXPECT_FALSE(pattern_->isMousePressed_);
}
} // namespace OHOS::Ace::NG
