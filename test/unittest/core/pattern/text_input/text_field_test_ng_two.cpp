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

class TextFieldTestNgTwo : public TextInputBases {
public:
};

/**
 * @tc.name: testCaretPosition001
 * @tc.desc: test testInput caretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, testCaretPosition001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testShowPasswordIcon001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testShowPasswordSymbol001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testShowPasswordSymbol002, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testShowPasswordSymbol003, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testType001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testEnterKeyType001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testStyle001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testSelectedBackgroundColor001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, testCaretStyle001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, HandleOnEscape001, TestSize.Level1)
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
    EXPECT_TRUE(pattern_->HandleOnEscape());
}

/**
 * @tc.name: HandleOnTab001
 * @tc.desc: Test HandleOnTab
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, HandleOnTab001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, ConvertTouchOffsetToCaretPosition001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, HandleOnUndoAction001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputToJsonValue001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputToJsonValue002, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputMinFontSize001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputMaxFontSize001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputHeightAdaptivePolicy001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputLetterSpacing001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputLineHeight001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputHalfLeading001, TestSize.Level1)
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
 * @tc.name: TextInputHalfLeading002
 * @tc.desc: test TextInput halfLeading
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, TextInputHalfLeading002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set halfLeading false
     * @tc.expected: halfLeading is false
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHalfLeading(false);
    });

    /**
     * @tc.step: step2. test halfLeading
     */
    EXPECT_EQ(layoutProperty_->GetHalfLeading(), false);
}

/**
 * @tc.name: TextInputTextDecoration001
 * @tc.desc: test TextInput decoration
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, TextInputTextDecoration001, TestSize.Level1)
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
    EXPECT_EQ(layoutProperty_->GetTextDecorationFirst(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(layoutProperty_->GetTextDecorationColor(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetTextDecorationStyle(), TextDecorationStyle::DOTTED);
}

/**
 * @tc.name: SupportAvoidanceTest
 * @tc.desc: test whether the custom keyboard supports the collision avoidance function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, SupportAvoidanceTest, TestSize.Level1)
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
 * @tc.name: TextInputLineBreakStrategy001
 * @tc.desc: test testInput text lineBreakStrategy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, TextInputLineBreakStrategy001, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set lineBreakStrategy GREEDY
     */
    layoutProperty_->UpdateLineBreakStrategy(LineBreakStrategy::GREEDY);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetLineBreakStrategy(), LineBreakStrategy::GREEDY);

    /**
     * @tc.step: step3. Set lineBreakStrategy HIGH_QUALITY
     */
    layoutProperty_->UpdateLineBreakStrategy(LineBreakStrategy::HIGH_QUALITY);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetLineBreakStrategy(), LineBreakStrategy::HIGH_QUALITY);

    /**
     * @tc.step: step4. Set lineBreakStrategy BALANCED
     */
    layoutProperty_->UpdateLineBreakStrategy(LineBreakStrategy::BALANCED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetLineBreakStrategy(), LineBreakStrategy::BALANCED);
}

 /**
 * @tc.name: HandleClickEventTest001
 * @tc.desc: test scrolling when clicking on the scroll bar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, HandleClickEventTest001, TestSize.Level1)
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
 * @tc.name: StopBackPress
 * @tc.desc: Test whether the stopBackPress property is set successfully.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, StopBackPress, TestSize.Level1)
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
 * @tc.name: TextInputMinFontScale001
 * @tc.desc: test TextInput minFontScale
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, TextInputMinFontScale001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextInputMaxFontScale001, TestSize.Level1)
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

/**
 * @tc.name: SupportTextFadeoutTest002
 * @tc.desc: Test whether the text node has the ability to support fadeout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, SupportTextFadeoutTest002, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextFadeoutStateTest001, TestSize.Level1)
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
HWTEST_F(TextFieldTestNgTwo, TextFadeoutStateTest002, TestSize.Level1)
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
 * @tc.name: AutoCapTypeToString001
 * @tc.desc: test testInput AutoCapTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, AutoCapTypeToString001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set NONE
     */
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::NONE);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->AutoCapTypeToString().c_str(), "AutoCapitalizationMode.NONE");

    /**
     * @tc.step: step3. Set WORDS
     */
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::WORDS);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->AutoCapTypeToString().c_str(), "AutoCapitalizationMode.WORDS");

    /**
     * @tc.step: step4. Set SENTENCES
     */
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::SENTENCES);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->AutoCapTypeToString().c_str(), "AutoCapitalizationMode.SENTENCES");

    /**
     * @tc.step: step5. Set ALL_CHARACTERS
     */
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::ALL_CHARACTERS);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->AutoCapTypeToString().c_str(), "AutoCapitalizationMode.ALL_CHARACTERS");
}

/**
 * @tc.name: accessibilityProperty001
 * @tc.desc: test testInput accessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, accessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text filed node
     */
    std::string contentStr = "12345678";
    CreateTextField(contentStr, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });

    EXPECT_NE(frameNode_, nullptr);
    EXPECT_NE(accessibilityProperty_, nullptr);

    /**
     * @tc.steps: step2. GetText
     */
    std::string textPropStr = accessibilityProperty_->GetText();
    EXPECT_EQ(textPropStr, contentStr);
}

/**
 * @tc.name: accessibilityProperty002
 * @tc.desc: test textInput accessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, accessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text filed node
     */
    std::string contentStr = "你好12345678";
    CreateTextField(contentStr, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });

    EXPECT_NE(frameNode_, nullptr);
    EXPECT_NE(accessibilityProperty_, nullptr);

    /**
     * @tc.steps: step2. GetText
     */
    std::string textPropStr = accessibilityProperty_->GetText();
    EXPECT_EQ(textPropStr, "**********");
}

/**
 * @tc.name: accessibilityProperty003
 * @tc.desc: test textInput accessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, accessibilityProperty003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text filed node
     */
    CreateTextField("", "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });

    EXPECT_NE(frameNode_, nullptr);
    EXPECT_NE(accessibilityProperty_, nullptr);

    /**
     * @tc.steps: step2. GetText
     */
    std::string textPropStr = accessibilityProperty_->GetText();
    EXPECT_EQ(textPropStr, "");
}

/**
 * @tc.name: accessibilityProperty004
 * @tc.desc: test textInput accessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgTwo, accessibilityProperty004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text filed node
     */
    std::string contentStr = "12345678";
    CreateTextField(contentStr, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordText(true);
    });

    EXPECT_NE(frameNode_, nullptr);
    EXPECT_NE(accessibilityProperty_, nullptr);

    /**
     * @tc.steps: step2. GetText
     */
    std::string textPropStr = accessibilityProperty_->GetText();
    EXPECT_EQ(textPropStr, contentStr);
}
} // namespace OHOS::Ace::NG