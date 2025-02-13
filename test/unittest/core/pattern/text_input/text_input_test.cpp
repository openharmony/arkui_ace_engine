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
     * @tc.steps: step1. Initialize textInput and focusHub
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
 * @tc.desc: Test showCancelSymbolIcon true, since VERSION_SIXTEEN
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode005, TestSize.Level1)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));

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
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));

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
     * @tc.steps: step2. Get foucs
     */
    GetFocus();

    /**
     * @tc.steps: step3. Get foucs by press tab
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
 * @tc.name: testCaretPosition001
 * @tc.desc: test testInput caretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: caretPosition is 10
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set caretPosition
     */
    pattern_->SetCaretPosition(10);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 10);

    /**
     * @tc.step: step3. Set caretPosition
     */
    pattern_->SetCaretPosition(5);
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890987654321";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    pattern_->UpdateSelectionOffset();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), value.text.length());
}

/**
 * @tc.name: testShowPasswordIcon001
 * @tc.desc: test testInput showPasswordIcon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowPasswordIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showPasswordIcon is false
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(false);
    });

    /**
     * @tc.step: step2. Set showPasswordIcon
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetCaretUpdateType(), CaretUpdateType::NONE);
    EXPECT_EQ(layoutProperty_->GetShowPasswordIcon(), false);

     /**
     * @tc.step: step3. Set showPasswordIcon
     */
    layoutProperty_->UpdateShowPasswordIcon(true);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetShowPasswordIcon(), true);
}

/**
 * @tc.name: testShowPasswordSymbol001
 * @tc.desc: test testInput showPasswordSymbol true, since VERSION_THIRTEEN
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowPasswordSymbol001, TestSize.Level1)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));

    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showPasswordSymbol is true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });

    /**
     * @tc.step: step2. Set showPasswordSymbol
     */
    frameNode_->MarkModifyDone();
    auto passwordResponseArea = AceType::DynamicCast<PasswordResponseArea>(pattern_->responseArea_);
    ASSERT_NE(passwordResponseArea, nullptr);
    auto stackNode = passwordResponseArea->stackNode_;
    ASSERT_NE(stackNode, nullptr);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    ASSERT_NE(iconFrameNode, nullptr);
    EXPECT_EQ(iconFrameNode->GetTag(), V2::SYMBOL_ETS_TAG);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: testShowPasswordSymbol002
 * @tc.desc: test testInput showPasswordSymbol false, because VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowPasswordSymbol002, TestSize.Level1)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showPasswordSymbol is false
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });

    /**
     * @tc.step: step2. Set showPasswordSymbol
     */
    frameNode_->MarkModifyDone();
    auto passwordResponseArea = AceType::DynamicCast<PasswordResponseArea>(pattern_->responseArea_);
    ASSERT_NE(passwordResponseArea, nullptr);
    auto stackNode = passwordResponseArea->stackNode_;
    ASSERT_NE(stackNode, nullptr);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    ASSERT_NE(iconFrameNode, nullptr);
    EXPECT_EQ(iconFrameNode->GetTag(), V2::IMAGE_ETS_TAG);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: testShowPasswordSymbol003
 * @tc.desc: test testInput showPasswordSymbol false, because set SetPasswordIcon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowPasswordSymbol003, TestSize.Level1)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));

    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showPasswordSymbol is false
     */
    PasswordIcon passwordIcon;
    CreateTextField(DEFAULT_TEXT, "", [passwordIcon](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetPasswordIcon(passwordIcon);
    });

    /**
     * @tc.step: step2. Set showPasswordSymbol
     */
    frameNode_->MarkModifyDone();
    auto passwordResponseArea = AceType::DynamicCast<PasswordResponseArea>(pattern_->responseArea_);
    ASSERT_NE(passwordResponseArea, nullptr);
    auto stackNode = passwordResponseArea->stackNode_;
    ASSERT_NE(stackNode, nullptr);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    ASSERT_NE(iconFrameNode, nullptr);
    EXPECT_EQ(iconFrameNode->GetTag(), V2::IMAGE_ETS_TAG);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: testType001
 * @tc.desc: test testInput type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testType001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: type is TextInputType::TEXT
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::BEGIN);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::BEGIN);

    /**
     * @tc.step: step3. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::UNSPECIFIED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::UNSPECIFIED);

    /**
     * @tc.step: step4. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::TEXT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::TEXT);

    /**
     * @tc.step: step5. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::MULTILINE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::MULTILINE);

    /**
     * @tc.step: step6. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::NUMBER);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::NUMBER);

    /**
     * @tc.step: step7. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::PHONE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::PHONE);

    /**
     * @tc.step: step8. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::DATETIME);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::DATETIME);

    /**
     * @tc.step: step9. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::EMAIL_ADDRESS);

    /**
     * @tc.step: step10. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::URL);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::URL);

    /**
     * @tc.step: step11. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::VISIBLE_PASSWORD);

    /**
     * @tc.step: step12. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::END);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::END);
}

/**
 * @tc.name: testEnterKeyType001
 * @tc.desc: test testInput enterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testEnterKeyType001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::GO);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Go");

    /**
     * @tc.step: step3. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::SEARCH);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Search");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::SEND);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Send");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::DONE);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Done");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::NEXT);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Next");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::BEGIN);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::BEGIN);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::UNSPECIFIED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::UNSPECIFIED);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::NONE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::NONE);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::PREVIOUS);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::PREVIOUS);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::END);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::END);
}

/**
 * @tc.name: testStyle001
 * @tc.desc: test testInput style
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set style
     */
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetInputStyle(), InputStyle::DEFAULT);

    /**
     * @tc.step: step3. Set style
     */
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetInputStyle(), InputStyle::INLINE);
}

/**
 * @tc.name: testSelectedBackgroundColor001
 * @tc.desc: test testInput selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR);
    });
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(Color::RED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testCaretStyle001
 * @tc.desc: test testInput caretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testCaretStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCaretStyle(DEFAULT_CARET_STYLE);
    });
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set caretStyle
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetCursorWidth().value().Value(), 3.0);
}

/**
 * @tc.name: HandleOnEscape001
 * @tc.desc: Test let handle on escape after selectAll
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnEscape001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Call ProcessOverlay
     */
    pattern_->ProcessOverlay();


    /**
     * @tc.steps: step3. Press esc
     */
    KeyEvent event;
    event.code = KeyCode::KEY_ESCAPE;
    pattern_->OnKeyEvent(event);

    /**
     * @tc.steps: step4. escape when select all value
     */
    pattern_->HandleOnSelectAll(true);
    EXPECT_FALSE(pattern_->HandleOnEscape());
}

/**
 * @tc.name: HandleOnTab001
 * @tc.desc: Test HandleOnTab
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnTab001, TestSize.Level1)
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
     * @tc.steps: step3. Test update focus backward when handleOnTab.
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_TRUE(pattern_->HandleOnTab(true));

    /**
     * @tc.steps: step4. Test update focus forward when handleOnTab.
     */
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->HandleOnTab(false));
}

/**
 * @tc.name: ConvertTouchOffsetToCaretPosition001
 * @tc.desc: test testInput caretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, ConvertTouchOffsetToCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCaretStyle(DEFAULT_CARET_STYLE);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call ConvertTouchOffsetToCaretPosition
     */
    pattern_->SetCaretPosition(2);
    int32_t caretPosition = pattern_->ConvertTouchOffsetToCaretPosition(Offset(0.0, 0.0));
    EXPECT_EQ(caretPosition, 0);
    caretPosition = pattern_->ConvertTouchOffsetToCaretPositionNG(Offset(0.0, 0.0));
    EXPECT_EQ(caretPosition, 0);
}

/**
 * @tc.name: HandleOnUndoAction001
 * @tc.desc: test testInput caretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnUndoAction001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call ConvertTouchOffsetToCaretPosition
     */
    pattern_->SetCaretPosition(5);
    pattern_->UpdateEditingValueToRecord();
    pattern_->HandleOnUndoAction();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 26);
}

/**
 * @tc.name: TextInputToJsonValue001
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLUE);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
        model.SetLetterSpacing(1.0_px);
        model.SetLineHeight(2.0_px);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the corresponding JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("decoration"));
    EXPECT_TRUE(json->Contains("letterSpacing"));
    EXPECT_TRUE(json->Contains("lineHeight"));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: TextInputToJsonValue002
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputToJsonValue002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetAdaptMinFontSize(1.0_px);
        model.SetAdaptMaxFontSize(2.0_px);
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the corresponding JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("minFontSize"));
    EXPECT_TRUE(json->Contains("maxFontSize"));
    EXPECT_TRUE(json->Contains("heightAdaptivePolicy"));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: TextInputMinFontSize001
 * @tc.desc: test TextInput minFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputMinFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with set minFontSize 1.0_fp
     * @tc.expected: minFontSize is 1.0_fp
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetAdaptMinFontSize(1.0_fp);
    });

    /**
     * @tc.step: step2. test minFontSize
     */
    EXPECT_EQ(layoutProperty_->GetAdaptMinFontSize(), 1.0_fp);
}

/**
 * @tc.name: TextInputMaxFontSize001
 * @tc.desc: test TextInput maxFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputMaxFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with set maxFontSize 2.0_fp
     * @tc.expected: maxFontSize is 2.0_fp
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetAdaptMaxFontSize(2.0_fp);
    });

    /**
     * @tc.step: step2. test maxFontSize
     */
    EXPECT_EQ(layoutProperty_->GetAdaptMaxFontSize(), 2.0_fp);
}

/**
 * @tc.name: TextInputHeightAdaptivePolicy001
 * @tc.desc: test TextInput heightAdaptivePolicy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputHeightAdaptivePolicy001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with set heightAdaptivePolicy TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST
     * @tc.expected: heightAdaptivePolicy is TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test heightAdaptivePolicy
     */
    EXPECT_EQ(layoutProperty_->GetHeightAdaptivePolicy(), TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    layoutProperty_->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(layoutProperty_->GetHeightAdaptivePolicy(), TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    layoutProperty_->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    EXPECT_EQ(layoutProperty_->GetHeightAdaptivePolicy(), TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
}

/**
 * @tc.name: TextInputLetterSpacing001
 * @tc.desc: test TextInput letterSpacing
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputLetterSpacing001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set letterSpacing 1.0_fp
     * @tc.expected: letterSpacing is 1.0_fp
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLetterSpacing(1.0_fp);
    });

    /**
     * @tc.step: step2. test letterSpacing
     */
    EXPECT_EQ(layoutProperty_->GetLetterSpacing(), 1.0_fp);
}

/**
 * @tc.name: TextInputLineHeight001
 * @tc.desc: test TextInput lineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputLineHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set lineHeight 2.0_fp
     * @tc.expected: lineHeight is 2.0_fp
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLineHeight(2.0_fp);
    });

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(layoutProperty_->GetLineHeight(), 2.0_fp);
}

/**
 * @tc.name: TextInputHalfLeading001
 * @tc.desc: test TextInput halfLeading
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputHalfLeading001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set halfLeading true
     * @tc.expected: halfLeading is true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHalfLeading(true);
    });

    /**
     * @tc.step: step2. test halfLeading
     */
    EXPECT_EQ(layoutProperty_->GetHalfLeading(), true);
}

/**
 * @tc.name: TextInputTextDecoration001
 * @tc.desc: test TextInput decoration
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputTextDecoration001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set decoration(LINE_THROUGH, BLUE, DOTTED)
     * @tc.expected: maxLength is decoration(LINE_THROUGH, BLUE, DOTTED)
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLUE);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test decoration
     */
    EXPECT_EQ(layoutProperty_->GetTextDecoration(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(layoutProperty_->GetTextDecorationColor(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetTextDecorationStyle(), TextDecorationStyle::DOTTED);
}

/**
 * @tc.name: HandleClickEventTest001
 * @tc.desc: test scrolling when clicking on the scroll bar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleClickEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CreateTextField , GestureEvent and ScrollBars.
     * @tc.expected: create CreateTextField , GestureEvent and ScrollBars created successfully.
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    GestureEvent info;
    info.localLocation_ = Offset(1.0f, 110.0f);
    auto setupScrolbar = [pattern = pattern_]() {
        pattern->scrollBar_->barRect_ = Rect(0.0f, 0.0f, 30.0f, 500.0f);
        pattern->scrollBar_->touchRegion_ = Rect(10.0f, 100.0f, 30.0f, 100.0f);
        pattern->scrollBar_->isScrollable_ = true;
    };

    /**
    * @tc.steps: step2. Test HandleClickEvent.
    * @tc.expect: CheckBarDirection equal BarDirection's Value.
    */
    pattern_->hasMousePressed_ = true;
    pattern_->HandleClickEvent(info);
    Point point(info.localLocation_.GetX(), info.localLocation_.GetY());
    setupScrolbar();
    EXPECT_EQ(pattern_->scrollBar_->CheckBarDirection(point), BarDirection::BAR_NONE);
    info.localLocation_ = Offset(1.0f, 1.0f);
    pattern_->HandleClickEvent(info);
    Point point1(info.localLocation_.GetX(), info.localLocation_.GetY());
    setupScrolbar();
    EXPECT_EQ(pattern_->scrollBar_->CheckBarDirection(point1), BarDirection::PAGE_UP);
    info.localLocation_ = Offset(1.0f, 300.0f);
    pattern_->HandleClickEvent(info);
    Point point2(info.localLocation_.GetX(), info.localLocation_.GetY());
    setupScrolbar();
    EXPECT_EQ(pattern_->scrollBar_->CheckBarDirection(point2), BarDirection::PAGE_DOWN);
}

/**
 * @tc.name: SupportAvoidanceTest
 * @tc.desc: test whether the custom keyboard supports the collision avoidance function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, SupportAvoidanceTest, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    auto supportAvoidance = true;
    pattern_->SetCustomKeyboardOption(supportAvoidance);
    EXPECT_TRUE(pattern_->keyboardAvoidance_);
    supportAvoidance = false;
    pattern_->SetCustomKeyboardOption(supportAvoidance);
    EXPECT_FALSE(pattern_->keyboardAvoidance_);
}

/**
 * @tc.name: StopBackPress
 * @tc.desc: Test whether the stopBackPress property is set successfully.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, StopBackPress, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG& model) {
        model.SetStopBackPress(false);
    });
    pattern_->isCustomKeyboardAttached_ = true;
    /**
     * @tc.steps: step1. Test IsStopBackPress OnBackPressed.
     * @tc.expect: return return false.
     */
    EXPECT_FALSE(pattern_->IsStopBackPress());
    EXPECT_FALSE(pattern_->OnBackPressed());
    /**
     * @tc.steps: step2. Test SelectContentOverlayManager::IsStopBackPress.
     * @tc.expect: return false.
     */
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->selectOverlayHolder_ = pattern_->selectOverlay_;
    pattern_->selectOverlay_->OnBind(manager);
    EXPECT_FALSE(manager->IsStopBackPress());
    /**
     * @tc.steps: step3. Set stopBackPress to true.
     * @tc.expect: return true.
     */
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateStopBackPress(true);

    EXPECT_TRUE(pattern_->IsStopBackPress());
    EXPECT_TRUE(pattern_->OnBackPressed());
    EXPECT_TRUE(manager->IsStopBackPress());
}

/**
 * @tc.name: SupportTextFadeoutTest002
 * @tc.desc: Test whether the text node has the ability to support fadeout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, SupportTextFadeoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text field node with default text and placeholder.
     * @tc.expected: Check the textinput node has the ability to support fadeout.
     */
    CreateTextField(DEFAULT_TEXT);
    EXPECT_FALSE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetTextFadeoutCapacity());
}

/**
 * @tc.name: TextFadeoutStateTest001
 * @tc.desc: Test the text fadeout and marquee state.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextFadeoutStateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node with default text and placeholder.
     * @tc.expected: Check the node has the ability to support fadeout.
     */
    CreateTextField(DEFAULT_TEXT);
    EXPECT_TRUE(pattern_->GetTextFadeoutCapacity());
    EXPECT_FALSE(pattern_->textFieldContentModifier_->textFadeoutEnabled_);

    /**
     * @tc.steps: step2. Set theme textFadeoutEnabled_.
     */
    auto pipelineContext = frameNode_->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    theme->textFadeoutEnabled_ = true;

    /**
     * @tc.steps: step3. Set contentSize size is less than text size and call UpdateContentModifier.
     * @tc.expected: text need fadeout and marquee.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    paintWrapper->GetGeometryNode()->SetContentSize({ 40.0f, 40.0f });
    auto paintMethod = AceType::DynamicCast<TextFieldPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_NE(paintMethod, nullptr);

    paintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_TRUE(pattern_->GetParagraph()->GetTextWidth() > paintWrapper->GetContentSize().Width());
    EXPECT_TRUE(pattern_->textFieldContentModifier_->textFadeoutEnabled_);
}

/**
 * @tc.name: TextFadeoutStateTest002
 * @tc.desc: Test the text fadeout and marquee state.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextFadeoutStateTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field node with default text and placeholder.
     * @tc.expected: Check the node has the ability to support fadeout.
     */
    CreateTextField(DEFAULT_TEXT);
    EXPECT_TRUE(pattern_->GetTextFadeoutCapacity());
    EXPECT_FALSE(pattern_->textFieldContentModifier_->textFadeoutEnabled_);

    /**
     * @tc.steps: step2. Set theme textFadeoutEnabled_.
     */
    auto pipelineContext = frameNode_->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    theme->textFadeoutEnabled_ = true;

    /**
     * @tc.steps: step3. Set contentSize size is larger than text size and call UpdateContentModifier.
     * @tc.expected: text do not need fadeout.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    paintWrapper->GetGeometryNode()->SetContentSize({ 500.0f, 500.0f });

    auto paintMethod = AceType::DynamicCast<TextFieldPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_NE(paintMethod, nullptr);

    paintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_FALSE(pattern_->GetParagraph()->GetTextWidth() > paintWrapper->GetContentSize().Width());
    EXPECT_FALSE(pattern_->textFieldContentModifier_->textFadeoutEnabled_);
}

/**
 * @tc.name: TextInputMinFontScale001
 * @tc.desc: test TextInput minFontScale
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputMinFontScale001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with set minFontScale 1.0
     * @tc.expected: minFontScale is 1.0
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMinFontScale(1.0);
    });

    /**
     * @tc.step: step2. test minFontScale
     */
    EXPECT_EQ(layoutProperty_->GetMinFontScale(), 1.0);
}

/**
 * @tc.name: TextInputMaxFontScale001
 * @tc.desc: test TextInput maxFontScale
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputMaxFontScale001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with set maxFontScale 2.0
     * @tc.expected: maxFontScale is 2.0
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxFontScale(2.0);
    });

    /**
     * @tc.step: step2. test maxFontScale
     */
    EXPECT_EQ(layoutProperty_->GetMaxFontScale(), 2.0);
}
} // namespace OHOS::Ace::NG