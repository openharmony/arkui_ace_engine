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

#include "test/mock/core/rosen/mock_canvas.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldUXTest : public TextInputBases {
public:
};

/**
 * @tc.name: UpdateCaretByTouchMove001
 * @tc.desc: Test UpdateCaretByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateCaretByTouchMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub.
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create location info, touch type DOWN
     */
    TouchLocationInfo touchLocationInfo1(0);
    touchLocationInfo1.touchType_ = TouchType::DOWN;
    touchLocationInfo1.localLocation_ = Offset(0.0f, 0.0f);
    TouchLocationInfo touchLocationInfo11(0);
    touchLocationInfo11.touchType_ = TouchType::DOWN;
    touchLocationInfo11.localLocation_ = Offset(0.0f, 0.0f);

    /**
     * @tc.steps: step3. create touch info, touch type DOWN
     */
    TouchEventInfo touchInfo1("");
    touchInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));
    touchInfo1.AddChangedTouchLocationInfo(std::move(touchLocationInfo11));

    /**
     * @tc.steps: step4. test touch down
     */
    pattern_->HandleTouchEvent(touchInfo1);
    EXPECT_TRUE(pattern_->moveCaretState_.isTouchCaret);

    /**
     * @tc.steps: step5. create location info, touch type MOVE
     */
    TouchLocationInfo touchLocationInfo2(0);
    touchLocationInfo2.touchType_ = TouchType::MOVE;
    touchLocationInfo2.localLocation_ = Offset(0.0f, 0.0f);
    TouchLocationInfo touchLocationInfo22(0);
    touchLocationInfo22.touchType_ = TouchType::MOVE;
    touchLocationInfo22.localLocation_ = Offset(0.0f, 0.0f);

    /**
     * @tc.steps: step6. create touch info, touch type MOVE
     */
    TouchEventInfo touchInfo2("");
    touchInfo2.AddTouchLocationInfo(std::move(touchLocationInfo2));
    touchInfo2.AddChangedTouchLocationInfo(std::move(touchLocationInfo22));

    /**
     * @tc.steps: step7. test touch move
     */
    pattern_->HandleTouchEvent(touchInfo2);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 0);

    /**
     * @tc.steps: step8. create location, touch type info UP
     */
    TouchLocationInfo touchLocationInfo3(0);
    touchLocationInfo3.touchType_ = TouchType::UP;
    touchLocationInfo3.localLocation_ = Offset(0.0f, 0.0f);
    TouchLocationInfo touchLocationInfo33(0);
    touchLocationInfo33.touchType_ = TouchType::UP;
    touchLocationInfo33.localLocation_ = Offset(0.0f, 0.0f);

    /**
     * @tc.steps: step9. create touch info, touch type UP
     */
    TouchEventInfo touchInfo3("");
    touchInfo3.AddTouchLocationInfo(std::move(touchLocationInfo3));
    touchInfo3.AddChangedTouchLocationInfo(std::move(touchLocationInfo33));

    /**
     * @tc.steps: step10. test touch up
     */
    pattern_->HandleTouchEvent(touchInfo3);
    EXPECT_FALSE(pattern_->moveCaretState_.isTouchCaret);
}

/**
 * @tc.name: CleanNode001
 * @tc.desc: Test UpdateClearNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto iconLayoutProperty = iconFrameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(iconLayoutProperty, nullptr);

    /**
     * @tc.steps: step5. create text icon size
     */
    auto iconSize = Dimension(ICON_SIZE, DimensionUnit::PX);

    /**
     * @tc.steps: step6. test Update clear node true
     */
    cleanNodeResponseArea->UpdateCleanNode(true);
    EXPECT_EQ(iconLayoutProperty->calcLayoutConstraint_->selfIdealSize,
        CalcSize(CalcLength(iconSize), CalcLength(iconSize)));

    /**
     * @tc.steps: step7. test Update clear node false
     */
    cleanNodeResponseArea->UpdateCleanNode(false);
    EXPECT_EQ(iconLayoutProperty->calcLayoutConstraint_->selfIdealSize, CalcSize(CalcLength(0.0), CalcLength(0.0)));
}

/**
 * @tc.name: CleanNode002
 * @tc.desc: Test OnCleanNodeClicked
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Get clean node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);

    /**
     * @tc.steps: step3. test clean node clicked
     */
    cleanNodeResponseArea->OnCleanNodeClicked();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetTextValue(), "");
}

/**
 * @tc.name: CleanNode003
 * @tc.desc: Test showCancelButtonSymbol false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input, set cancelButtonSymbol false
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);

    /**
     * @tc.steps: step3. test clean node symbol false
     */
    EXPECT_FALSE(cleanNodeResponseArea->IsShowSymbol());
    EXPECT_FALSE(cleanNodeResponseArea->IsSymbolIcon());
}

/**
 * @tc.name: CleanNode004
 * @tc.desc: Test showCancelButtonSymbol true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input, set cancelButtonSymbol true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(true);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);

    /**
     * @tc.steps: step3. test clean node symbol true
     */
    EXPECT_TRUE(cleanNodeResponseArea->IsShowSymbol());
    EXPECT_TRUE(cleanNodeResponseArea->IsSymbolIcon());
}

/**
 * @tc.name: CleanNode005
 * @tc.desc: Test showCancelSymbolIcon true, since VERSION_EIGHTEEN
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode005, TestSize.Level1)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /**
     * @tc.steps: step1. Initialize text input, set cancelSymbolIcon not nullptr
     */
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        EXPECT_NE(node, nullptr);
    };
    CreateTextField(DEFAULT_TEXT, "", [onApply](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(true);
        model.SetCancelSymbolIcon(onApply);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);

    /**
     * @tc.steps: step3. test cancelSymbolIcon is not nullptr
     */
    ASSERT_NE(layoutProperty_, nullptr);
    EXPECT_NE(layoutProperty_->GetCancelIconSymbol(), nullptr);
    EXPECT_TRUE(cleanNodeResponseArea->IsShowSymbol());
    EXPECT_TRUE(cleanNodeResponseArea->IsSymbolIcon());

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: CleanNode006
 * @tc.desc: Test showCancelSymbolIcon false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode006, TestSize.Level1)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /**
     * @tc.steps: step1. Initialize text input, set cancelSymbolIcon nullptr
     */
    auto onApply = nullptr;
    CreateTextField(DEFAULT_TEXT, "", [onApply](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(true);
        model.SetCancelSymbolIcon(onApply);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);

    /**
     * @tc.steps: step3. test cancelSymbolIcon is nullptr
     */
    ASSERT_NE(layoutProperty_, nullptr);
    EXPECT_EQ(layoutProperty_->GetCancelIconSymbol(), nullptr);
    EXPECT_TRUE(cleanNodeResponseArea->IsShowSymbol());
    EXPECT_TRUE(cleanNodeResponseArea->IsSymbolIcon());

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: RepeatClickCaret
 * @tc.desc: Test RepeatClickCaret
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, RepeatClickCaret, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Initialize click offset
     */
    Offset clickOffset(0.0f, 0.0f);
    int32_t lastIndex = 0;
    RectF lastCaretRect = RectF(-1.0f, -1.0f, 2.0f, 2.0f);

    /**
     * @tc.steps: step3. Text input request focus
     */
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps: step3. test repeat click caret
     */
    EXPECT_TRUE(pattern_->RepeatClickCaret(clickOffset, lastIndex));
    EXPECT_TRUE(pattern_->RepeatClickCaret(clickOffset, lastCaretRect));
}

/**
 * @tc.name: UpdateFocusForward001
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus forward when focus index = UNIT.
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_FALSE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusForward002
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step4. Test update focus forward when focus index = CANCEL.
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    EXPECT_FALSE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusForward003
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus forward, focus index = CANCEL.
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    EXPECT_TRUE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusForward004
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus forward when focus index = TEXT.
     */
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusBackward001
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = TEXT.
     */
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_FALSE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: UpdateFocusBackward002
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = CANCEL.
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: UpdateFocusBackward003
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
    });

    /**
     * @tc.steps: step2. Text input request focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = UNIT.
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: UpdateFocusBackward004
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = UNIT.
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Verify the onDraw Magnifier.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, onDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Move handle
     */
    OffsetF localOffset(1.0f, 1.0f);
    auto controller = pattern_->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    controller->SetLocalOffset(localOffset);
    RectF handleRect;
    pattern_->OnHandleMove(handleRect, false);

    /**
     * @tc.steps: step3. Test magnifier open or close
     * @tc.expected: magnifier is open
     */
    auto ret = controller->GetShowMagnifier();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step4. Craete TextFieldOverlayModifier
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern_, scrollEdgeEffect);

    /**
     * @tc.steps: step5. Create DrawingContext
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step6. Do onDraw(context)
     */
    textFieldOverlayModifier->onDraw(context);

    /**
     * @tc.steps: step7. When handle move done
     */
    pattern_->ProcessOverlay();
    pattern_->selectOverlay_->OnHandleMoveDone(handleRect, true);

    /**
     * @tc.steps: step8. Test magnifier open or close
     * @tc.expected: magnifier is close
     */
    ret = controller->GetShowMagnifier();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleOnShowMenu001
 * @tc.desc: Test close menu after HandleOnShowMenu()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnShowMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Do HandleOnShowMenu()
     */
    pattern_->HandleOnShowMenu();

    /**
     * @tc.steps: step3. Press esc
     */
    KeyEvent event;
    event.code = KeyCode::KEY_ESCAPE;
    event.action = KeyAction::DOWN;
    pattern_->OnKeyEvent(event);

    /**
     * @tc.steps: step4. Test menu open or close
     * @tc.expected: text menu is close
     */
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step5. Show menu when select all value
     */
    pattern_->HandleOnSelectAll(true);
    pattern_->HandleOnShowMenu();

    /**
     * @tc.steps: step6. Select all value again
     */
    pattern_->HandleOnSelectAll(true);

    /**
     * @tc.steps: step7. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step8. emulate Press shift + F10 key event
     */
    event.code = KeyCode::KEY_F10;
    event.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_F10);

    /**
     * @tc.steps: step9. call OnKeyEvent
     */
    ret = pattern_->OnKeyEvent(event);
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step10. Inset value
     */
    pattern_->InsertValue(u"abc");

    /**
     * @tc.steps: step11. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectAll001
 * @tc.desc: Test .SelectAll(true)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, SelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Set .SelectAll(true)
     */
    layoutProperty_->UpdateSelectAllValue(true);

    /**
     * @tc.steps: step3. Get focus by single click
     * @tc.expected: Select all value without handles
     */
    GestureEvent info;
    pattern_->HandleSingleClickEvent(info);
    EXPECT_EQ(pattern_->GetTextSelectController()->GetFirstHandleOffset().GetX(),
        pattern_->GetTextSelectController()->GetSecondHandleOffset().GetX());
}

/**
 * @tc.name: TabGetFocus001
 * @tc.desc: Test select all value when press tab and get focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TabGetFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Get focus by press tab
     * @tc.expected: Select all value without handles
     */
    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextSelectController()->GetFirstHandleOffset().GetX(),
        pattern_->GetTextSelectController()->GetSecondHandleOffset().GetX());
}

/**
 * @tc.name: NeedSoftKeyboard001
 * @tc.desc: Test NeedSoftKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, NeedSoftKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Test whether text field need soft keyboard.
     */
    ASSERT_NE(pattern_, nullptr);
    EXPECT_TRUE(pattern_->NeedSoftKeyboard());
}

/**
 * @tc.name: MaxLength001
 * @tc.desc: test textInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text
     * @tc.expected: maxLength is 1000000
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. test  default maxLength.
     */
    EXPECT_EQ(pattern_->GetMaxLength(), 1000000);
}

/**
 * @tc.name: MaxLength002
 * @tc.desc: test textInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength 20
     * @tc.expected: maxLength is 20
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(5);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("12345"), 0);
    EXPECT_EQ(pattern_->GetMaxLength(), 5);
}

/**
 * @tc.name: MaxLength003
 * @tc.desc: test testIput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength 0
     * @tc.expected: maxLength is 0
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(0);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetTextValue().compare(""), 0);
    EXPECT_EQ(pattern_->GetMaxLength(), 0);
}

/**
 * @tc.name: MaxLength004
 * @tc.desc: test testInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with reset maxLength
     * @tc.expected: maxLength is 1000000
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.ResetMaxLength();
    });

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetMaxLength(), 1000000);
}

/**
 * @tc.name: MaxLength005
 * @tc.desc: test testInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength -1
     * @tc.expected: maxLength is -1
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(-1);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("1234567890"), 0);
    EXPECT_EQ(pattern_->GetMaxLength(), -1);
}

/**
 * @tc.name: MaxLength006
 * @tc.desc: test testInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength 1000023
     * @tc.expected: maxLength is 1000023
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(1000023);
    });

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetMaxLength(), 1000023);
}

/**
 * @tc.name: NeedSoftKeyboard002
 * @tc.desc: Test NeedSoftKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, NeedSoftKeyboard002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Test whether text field need soft keyboard.
     */
    ASSERT_NE(pattern_, nullptr);
    EXPECT_TRUE(pattern_->NeedSoftKeyboard());
}

/**
 * @tc.name: CopyOption001
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default copyOption
     * @tc.expected: Default CopyOption is Distributed
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. test default copyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.Local");
}

/**
 * @tc.name: CopyOption002
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set copyOption
     * @tc.expected: CopyOption is Local
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::Local);
        model.SetType(TextInputType::TEXT);
    });

    /**
     * @tc.step: step2. Test CopyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), true);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.Local");
}

/**
 * @tc.name: CopyOption003
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption003, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node with set copyOption
     * @tc.expected: CopyOption is inApp
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::InApp);
        model.SetType(TextInputType::TEXT);
    });

    /**
     * @tc.step: step2. Test CopyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), true);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.InApp");
}

/**
 * @tc.name: CopyOption004
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption004, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node with set copyOption
     * @tc.expected: CopyOption is none
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::None);
    });

    /**
     * @tc.step: step2. Test CopyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), false);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.None");
}

/**
 * @tc.name: CopyOption005
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption005, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node with set copyOption
     * @tc.expected: CopyOption is not vaild
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(static_cast<CopyOptions>(99));
    });

    /**
     * @tc.step: step2. Test CopyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), true);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.Local");
}

/**
 * @tc.name: enableAutoFill001
 * @tc.desc: test testInput enableAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, enableAutoFill001, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: enableAutoFill is true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
    });

    /**
     * @tc.step: step2. Test default enableAutoFill
     */
    pattern_->CheckAutoFill();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetEnableAutoFill(), true);
}

/**
 * @tc.name: enableAutoFill002
 * @tc.desc: test testInput enableAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, enableAutoFill002, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: enableAutoFill is false
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(false);
    });

    /**
     * @tc.step: step2. Test enableAutoFill
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetEnableAutoFill(), false);
}

/**
 * @tc.name: testMaxLines001
 * @tc.desc: test testInput maxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testMaxLines001, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: maxLines is 5
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxViewLines(5);
    });

    /**
     * @tc.step: step2. Test maxLines
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetMaxViewLines(), 5);
}

/**
 * @tc.name: testBarState001
 * @tc.desc: test testInput barState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testBarState001, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: barState is DisplayMode::OFF
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::OFF);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetDisplayMode(), DisplayMode::OFF);
}

/**
 * @tc.name: testBarState002
 * @tc.desc: test testInput barState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testBarState002, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: barState is DisplayMode::AUTO
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::AUTO);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: testBarState003
 * @tc.desc: test testInput barState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testBarState003, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: barState is DisplayMode::ON
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::ON);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetDisplayMode(), DisplayMode::ON);
}

/**
 * @tc.name: testSelectionMenuHidden001
 * @tc.desc: test testInput selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testSelectionMenuHidden001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: selectionMenuHidden is DisplayMode::ON
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });

    /**
     * @tc.step: step2. Set selectionMenuHidden
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetSelectionMenuHidden(), false);

    /**
     * @tc.step: step3. Set selectionMenuHidden
     */
    layoutProperty_->UpdateSelectionMenuHidden(true);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetSelectionMenuHidden(), true);
}

/**
 * @tc.name: testEnableKeyboardOnFocus001
 * @tc.desc: test testInput EnableKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testEnableKeyboardOnFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: selectionMenuHidden is true
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. default enableKeyboardOnFocus
     */
    pattern_->RequestKeyboardByFocusSwitch();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->needToRequestKeyboardOnFocus_, true);

    /**
     * @tc.step: step3. Set enableKeyboardOnFocus
     */
    pattern_->SetNeedToRequestKeyboardOnFocus(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->needToRequestKeyboardOnFocus_, false);
}

/**
 * @tc.name: testTextAlign001
 * @tc.desc: test testInput textAlign
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testTextAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: textAlign is TextAlign::START
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::LEFT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::LEFT);

    /**
     * @tc.step: step3. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::RIGHT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::RIGHT);

    /**
     * @tc.step: step4. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::CENTER);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::CENTER);

    /**
     * @tc.step: step5. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::JUSTIFY);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::JUSTIFY);

    /**
     * @tc.step: step6. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::START);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::START);

    /**
     * @tc.step: step7. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::END);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::END);
}


/**
 * @tc.name: testTextAlign002
 * @tc.desc: test testInput textAlign
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testTextAlign002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    TextAlign textAligns[] = {TextAlign::CENTER, TextAlign::JUSTIFY, TextAlign::START,
        TextAlign::END};
    TextDirection textDirectoins[] = {TextDirection::LTR, TextDirection::RTL, TextDirection::AUTO};
    for (auto textAlign : textAligns) {
        for (auto textDirectoin : textDirectoins) {
            layoutProperty_->UpdateTextAlign(textAlign);
            layoutProperty_->UpdateLayoutDirection(textDirectoin);
            frameNode_->MarkModifyDone();
            EXPECT_EQ(layoutProperty_->GetTextAlign(), textAlign);
            EXPECT_EQ(layoutProperty_->GetLayoutDirection(), textDirectoin);
        }
    }
}

/**
 * @tc.name: testTextOverFlow001
 * @tc.desc: test testInput text TextOverFlow
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testTextOverFlow001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textOverflow CLIP
     */
    layoutProperty_->UpdateTextOverflow(TextOverflow::CLIP);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextOverflow(), TextOverflow::CLIP);

    /**
     * @tc.step: step2. Set textOverflow ELLIPSIS
     */
    layoutProperty_->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextOverflow(), TextOverflow::ELLIPSIS);
}

/**
 * @tc.name: testTextIndent001
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testTextIndent001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE);
}

/**
 * @tc.name: testShowUnderline001
 * @tc.desc: test testInput showUnderline
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowUnderline001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showUnderline is true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
    });

    /**
     * @tc.step: step2. Set showUnderline
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetShowUnderline(), true);

    /**
     * @tc.step: step2. Set showUnderline
     */
    layoutProperty_->UpdateShowUnderline(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetShowUnderline(), false);
}

/**
 * @tc.name: testShowUnderline002
 * @tc.desc: test testInput showUnderline
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowUnderline002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showUnderline is true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(false);
    });

    /**
     * @tc.step: step2. Set showUnderline
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetShowUnderline(), false);
}

/**
 * @tc.name: testUnderlineColor001
 * @tc.desc: test testInput underlineColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: underlineColor is Red
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
    });

    /**
     * @tc.step: step2. Set normalUnderlineColor is Red
     */
    pattern_->SetNormalUnderlineColor(Color::RED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetUserUnderlineColor().normal, Color::RED);

    /**
     * @tc.step: step3. Set userUnderlineColor is RED, GREEN, BLUE, BLACK
     */
    UserUnderlineColor userColor = {Color::RED, Color::GREEN, Color::BLUE, Color::BLACK};
    pattern_->SetUserUnderlineColor(userColor);
    frameNode_->MarkModifyDone();
    UserUnderlineColor userColorRes = pattern_->GetUserUnderlineColor();
    EXPECT_EQ(userColorRes.typing, Color::RED);
    EXPECT_EQ(userColorRes.normal, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::BLUE);
    EXPECT_EQ(userColorRes.disable, Color::BLACK);

    /**
     * @tc.step: step4. Set userUnderlineColor is null
     */
    UserUnderlineColor userColorNull = UserUnderlineColor();
    pattern_->SetUserUnderlineColor(userColorNull);
    frameNode_->MarkModifyDone();
    UserUnderlineColor userColorNullRes = pattern_->GetUserUnderlineColor();
    EXPECT_EQ(userColorNullRes.typing, std::nullopt);
    EXPECT_EQ(userColorNullRes.normal, std::nullopt);
    EXPECT_EQ(userColorNullRes.error, std::nullopt);
    EXPECT_EQ(userColorNullRes.disable, std::nullopt);
}

/**
 * @tc.name: TextSelectOverlayTestOnUpdateMenuInfo002
 * @tc.desc: Verify OnUpdateMenuInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextSelectOverlayTestOnUpdateMenuInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto textFieldTheme = pattern_->GetTheme();
    ASSERT_NE(textFieldTheme, nullptr);
    textFieldTheme->aiWriteBundleName_ = "BundleName";
    textFieldTheme->aiWriteAbilityName_ = "AbilityName";
    textFieldTheme->aiWriteIsSupport_ = "true";
    auto textSelectOverlay = pattern_->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    /**
     * @tc.steps: step2. Do OnUpdateMenuInfo
     */
    SelectMenuInfo menuInfo;
    textSelectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showAIWrite, true);
}

/**
 * @tc.name: TextSelectOverlayTestOnUpdateMenuInfo003
 * @tc.desc: Verify OnUpdateMenuInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextSelectOverlayTestOnUpdateMenuInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::None);
    });
    frameNode_->MarkModifyDone();

    GetFocus();
    auto textFieldTheme = pattern_->GetTheme();
    ASSERT_NE(textFieldTheme, nullptr);
    pattern_->textSelector_.Update(0, 0);
    textFieldTheme->aiWriteBundleName_ = "BundleName";
    textFieldTheme->aiWriteAbilityName_ = "AbilityName";
    textFieldTheme->aiWriteIsSupport_ = "true";
    auto textSelectOverlay = pattern_->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    /**
     * @tc.steps: step2. Do OnUpdateMenuInfo
     */
    auto info = std::make_shared<SelectOverlayInfo>();
    textSelectOverlay->OnHandleMarkInfoChange(info, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(info->menuInfo.showAIWrite, false);
}

/**
 * @tc.name: TextSelectOverlayTestOnUpdateMenuInfo004
 * @tc.desc: Verify OnUpdateMenuInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextSelectOverlayTestOnUpdateMenuInfo004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
        model.SetCopyOption(CopyOptions::InApp);
    });
    frameNode_->MarkModifyDone();

    GetFocus();
    auto textFieldTheme = pattern_->GetTheme();
    ASSERT_NE(textFieldTheme, nullptr);
    pattern_->textSelector_.Update(0, 0);
    textFieldTheme->aiWriteBundleName_ = "BundleName";
    textFieldTheme->aiWriteAbilityName_ = "AbilityName";
    textFieldTheme->aiWriteIsSupport_ = "true";
    auto textSelectOverlay = pattern_->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    /**
     * @tc.steps: step2. Do OnUpdateMenuInfo
     */
    SelectMenuInfo menuInfo;
    textSelectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showAIWrite, true);
}

/**
 * @tc.name: TextSelectOverlayTestOnUpdateMenuInfo005
 * @tc.desc: Verify OnUpdateMenuInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextSelectOverlayTestOnUpdateMenuInfo005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
        model.SetInputStyle(InputStyle::INLINE);
    });
    frameNode_->MarkModifyDone();

    GetFocus();
    auto textFieldTheme = pattern_->GetTheme();
    ASSERT_NE(textFieldTheme, nullptr);
    pattern_->textSelector_.Update(0, 0);
    textFieldTheme->aiWriteBundleName_ = "BundleName";
    textFieldTheme->aiWriteAbilityName_ = "AbilityName";
    textFieldTheme->aiWriteIsSupport_ = "true";
    auto textSelectOverlay = pattern_->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    /**
     * @tc.steps: step2. Do OnUpdateMenuInfo
     */
    SelectMenuInfo menuInfo;
    textSelectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    ASSERT_EQ(menuInfo.showAIWrite, true);
}

/**
 * @tc.name: SetPlaceholderColorInfo001
 * @tc.desc: Verify OnUpdateMenuInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, SetPlaceholderColorInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->SetPlaceholderColorInfo("TextFieldPattern");
    EXPECT_EQ(pattern_->placeholderColorInfo_, "[TextFieldPattern]");
}
} // namespace OHOS::Ace::NG