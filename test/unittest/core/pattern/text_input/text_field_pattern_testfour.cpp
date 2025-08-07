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

class TextFieldPatternTestFour : public TextInputBases {
public:
};

/**
 * @tc.name: UltralimitShake001
 * @tc.desc: test testInput text UltralimitShake
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, UltralimitShake001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateNumberOfLines(1024);

    pattern->UltralimitShake();
}

/**
 * @tc.name: CleanCounterNode001
 * @tc.desc: test testInput text CleanCounterNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CleanCounterNode001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CleanCounterNode();
    pattern->AddCounterNode();
    pattern->CleanCounterNode();
}

/**
 * @tc.name: HandleOnDelete001
 * @tc.desc: test testInput text HandleOnDelete
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleOnDelete001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 1;
    pattern->HandleOnDelete(true);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 1;
    pattern->HandleOnDelete(false);
}

/**
 * @tc.name: InitSurfacePositionChangedCallback001
 * @tc.desc: test testInput text InitSurfacePositionChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, InitSurfacePositionChangedCallback001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitSurfaceChangedCallback();
    pattern->InitSurfacePositionChangedCallback();

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->OnSurfacePositionChanged(0, 0);
    pipeline->OnSurfaceChanged(500, 700, WindowSizeChangeReason::CUSTOM_ANIMATION);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test testInput text HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSurfaceChanged001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->HandleSurfaceChanged(1, 3, 2, 4);
    pattern->HandleSurfaceChanged(1, 3, 2, 3);
    pattern->HandleSurfaceChanged(1, 2, 1, 3);
    pattern->HandleSurfaceChanged(1, 2, 1, 2);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    ASSERT_NE(holder, nullptr);
    manager->selectOverlayHolder_ = holder;
    pattern->selectOverlay_->OnBind(manager);

    Ace::NG::SelectOverlayInfo soi;
    soi.enableHandleLevel = true;
    manager->CreateSelectOverlay(soi, true);
    EXPECT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());
    pattern->HandleSurfaceChanged(1, 3, 2, 4);
    pattern->HandleSurfaceChanged(1, 3, 2, 3);
    pattern->HandleSurfaceChanged(1, 2, 1, 3);
    pattern->HandleSurfaceChanged(1, 2, 1, 2);
    pattern->magnifierController_->isShowMagnifier_ = true;
    pattern->HandleSurfaceChanged(1, 2, 1, 2);
    pattern->HandleSurfaceChanged(1, 2, 3, 4);
    soi.menuInfo.menuIsShow = true;
    soi.menuInfo.menuType = OptionMenuType::MOUSE_MENU;
    manager->CreateSelectOverlay(soi, true);
    pattern->HandleSurfaceChanged(1, 2, 1, 2);
    pattern->HandleSurfaceChanged(1, 2, 3, 4);
}

/**
 * @tc.name: OnVisibleChanget001
 * @tc.desc: test testInput text OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, OnVisibleChanget001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    pattern->OnVisibleChange(false);
    pattern->OnVisibleChange(true);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    ASSERT_NE(holder, nullptr);
    manager->selectOverlayHolder_ = holder;
    pattern->selectOverlay_->OnBind(manager);
    pattern->OnVisibleChange(false);
    pattern->OnVisibleChange(true);
    ASSERT_NE(pattern, nullptr);
    Ace::NG::SelectOverlayInfo soi;
    soi.enableHandleLevel = true;
    manager->CreateSelectOverlay(soi, true);
    pattern->OnVisibleChange(false);
    pattern->OnVisibleChange(true);
}

/**
 * @tc.name: UpdateInputFilterErrorText001
 * @tc.desc: test testInput text UpdateInputFilterErrorText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, UpdateInputFilterErrorText001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateInputFilterErrorText(u"");
    pattern->UpdateInputFilterErrorText(u"Error123456");
}

/**
 * @tc.name: ProcessFocusIndexAction001
 * @tc.desc: test testInput text ProcessFocusIndexAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, ProcessFocusIndexAction001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    pattern->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern->ProcessFocusIndexAction());
    pattern->focusIndex_ = FocuseIndex::CANCEL;
    EXPECT_FALSE(pattern->ProcessFocusIndexAction());

    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    layoutProperty->UpdateShowPasswordIcon(true);
    EXPECT_TRUE(pattern->ProcessFocusIndexAction());

    pattern->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_FALSE(pattern->ProcessFocusIndexAction());

    layoutProperty->UpdateShowUnderline(true);
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    EXPECT_FALSE(pattern->ProcessFocusIndexAction());
}

/**
 * @tc.name: OnCursorMoveDone001
 * @tc.desc: test testInput text OnCursorMoveDone
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, OnCursorMoveDone001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateMaxLines(0);
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    pattern->OnObscuredChanged(true);
    pattern->obscureTickCountDown_ = 1024;
    pattern->OnCursorMoveDone();
}

/**
 * @tc.name: WordLength001
 * @tc.desc: test testInput text GetWordLength GetLineBeginPosition GetLineEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, WordLength001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT);
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    std::vector<std::u16string> strVec = { u"0", u"1", u"2" };
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_ELLIPSIS);
    auto paragraphData = CreateParagraphData { true, textStyle.GetFontSize().ConvertToPx() };
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, u"content", true, paragraphData);
    DirtySwapConfig config;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textFieldNode, AceType::MakeRefPtr<GeometryNode>(), textFieldNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textInputLayoutAlgorithm));
    auto textDragNode0 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextDragPattern>(); });
    ASSERT_NE(textDragNode0, nullptr);
    pattern_->dragNode_ = textDragNode0;
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);
    pattern_->contentController_->content_ = u" T e s t ";
    pattern_->GetWordLength(0, 2);
    pattern_->GetWordLength(1, 2);
    pattern_->GetWordLength(0, 1);
    pattern_->GetWordLength(1, 1);
    pattern_->contentController_->content_ = u"       ";
    pattern_->GetWordLength(0, 2);
    pattern_->GetWordLength(1, 2);
    pattern_->GetWordLength(0, 1);
    pattern_->GetWordLength(1, 1);
    pattern_->contentController_->content_ = u"T\ne\ns\nt\n";
    pattern_->GetLineBeginPosition(0, true);
    pattern_->GetLineBeginPosition(0, false);
    pattern_->GetLineBeginPosition(1, true);
    pattern_->GetLineBeginPosition(1, false);
    pattern_->GetLineEndPosition(0, true);
    pattern_->GetLineEndPosition(0, false);
    pattern_->GetLineEndPosition(1, true);
    pattern_->GetLineEndPosition(1, false);
    pattern_->contentController_->content_ = u"\n\n\n\n\n";
    pattern_->GetLineBeginPosition(0, true);
    pattern_->GetLineBeginPosition(0, false);
    pattern_->GetLineBeginPosition(1, true);
    pattern_->GetLineBeginPosition(1, false);
    pattern_->GetLineEndPosition(0, true);
    pattern_->GetLineEndPosition(0, false);
    pattern_->GetLineEndPosition(1, true);
    pattern_->GetLineEndPosition(1, false);
}

/**
 * @tc.name: CursorMove001
 * @tc.desc: test testInput text CursorMoveLeftWord CursorMoveToParagraphBegin
 * CursorMoveRightWord CursorMoveLineEnd CursorMoveToParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CursorMove001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    pattern->selectController_->caretInfo_.index = -1;
    pattern->CursorMoveLeftWord();
    pattern->CursorMoveLineBegin();
    pattern->CursorMoveToParagraphBegin();
    pattern->CursorMoveLineEnd();
    pattern->CursorMoveToParagraphEnd();
    pattern->contentController_->content_  = u" T e s t ";
    pattern->selectController_->caretInfo_.index = -1;
    pattern->CursorMoveLeftWord();
    pattern->CursorMoveLineBegin();
    pattern->CursorMoveToParagraphBegin();
    pattern->CursorMoveLineEnd();
    pattern->CursorMoveToParagraphEnd();
    pattern->selectController_->caretInfo_.index = 0;
    pattern->CursorMoveLeftWord();
    pattern->CursorMoveLineBegin();
    pattern->CursorMoveToParagraphBegin();
    pattern->CursorMoveLineEnd();
    pattern->CursorMoveToParagraphEnd();
    pattern->selectController_->caretInfo_.index = -1;
    layoutProperty->UpdateMaxLines(0);
    pattern->CursorMoveLeftWord();
    pattern->CursorMoveLineBegin();
    pattern->CursorMoveToParagraphBegin();
    pattern->CursorMoveLineEnd();
    pattern->CursorMoveToParagraphEnd();
}

/**
 * @tc.name: HandleCounterBorder001
 * @tc.desc: test testInput text HandleCounterBorder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleCounterBorder001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    pattern->showCountBorderStyle_ = true;
    layoutProperty->UpdateShowUnderline(true);
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    pattern->HandleCounterBorder();
}

/**
 * @tc.name: OnValueChanged001
 * @tc.desc: test testInput text OnValueChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, OnValueChanged001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnValueChanged(true, true);
}

/**
 * @tc.name: PerformAction001
 * @tc.desc: test testInput text PerformAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, PerformAction001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto eventHub = textFieldNode->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto paintProperty = textFieldNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->focusIndex_ = FocuseIndex::TEXT;
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    pattern->PerformAction(TextInputAction::DONE);
    eventHub->SetOnSubmit([](int32_t, NG::TextFieldCommonEvent& event) {
        event.SetKeepEditable(false);
    });
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    paintProperty->UpdateInputStyle(InputStyle::INLINE);

    pattern->PerformAction(TextInputAction::DONE);
    layoutProperty->UpdateMaxLines(0);
    pattern->textAreaBlurOnSubmit_ = true;
    pattern->PerformAction(TextInputAction::NEW_LINE);
    layoutProperty->UpdateInputFilter("\n");
    pattern->textAreaBlurOnSubmit_ = false;
    pattern->PerformAction(TextInputAction::NEW_LINE);
    layoutProperty->UpdateInputFilter(" ");
    pattern->PerformAction(TextInputAction::NEW_LINE);
}

/**
 * @tc.name: RecordSubmitEvent001
 * @tc.desc: test testInput text RecordSubmitEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, RecordSubmitEvent001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto eventHub = textFieldNode->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    pattern->RecordSubmitEvent();
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    pattern->RecordSubmitEvent();
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    pattern->RecordSubmitEvent();
}

/**
 * @tc.name: HandleParentGlobalOffsetChange001
 * @tc.desc: test testInput text HandleParentGlobalOffsetChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleParentGlobalOffsetChange001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    pattern->HandleParentGlobalOffsetChange();
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    ASSERT_NE(holder, nullptr);
    manager->selectOverlayHolder_ = holder;
    pattern->selectOverlay_->OnBind(manager);
    Ace::NG::SelectOverlayInfo soi;
    soi.enableHandleLevel = true;
    manager->CreateSelectOverlay(soi, true);
    pattern->HandleParentGlobalOffsetChange();
    soi.menuInfo.menuIsShow = true;
    soi.menuInfo.menuType = OptionMenuType::MOUSE_MENU;
    manager->CreateSelectOverlay(soi, true);
    pattern->HandleParentGlobalOffsetChange();
}

/**
 * @tc.name: IsModalCovered001
 * @tc.desc: test testInput text IsModalCovered
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, IsModalCovered001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->IsModalCovered();
}

/**
 * @tc.name: CursorMoveUpTest001
 * @tc.desc: Test the cursor move up
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CursorMoveUpTest001, TestSize.Level0)
{
    /**
     * @tc.steps: Move up and down in a single-line text
     * @tc.expected: In single-line text, there is no up and down movement
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveUp();
    EXPECT_TRUE(ret);
    ret = pattern_->CursorMoveDown();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CursorMoveToParagraphEndTest001
 * @tc.desc: Test the cursor move to pragraph to the end
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CursorMoveToParagraphEndTest001, TestSize.Level0)
{
    /**
     * @tc.steps: Initialize text and move to the pargraph of the line
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveToParagraphEnd();
    EXPECT_TRUE(ret);

    /**
     * @tc.expected: Moving to the paragraph end and check if cursor is on pargraph end
     */
    ret = pattern_->CursorMoveLeft();
    ret = pattern_->CursorMoveToParagraphEnd();
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length())
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: StrokeTest001
 * @tc.desc: Test attrs about stroke
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, StrokeTest001, TestSize.Level0)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetTextColor(DEFAULT_TEXT_COLOR);
        model.SetStrokeWidth(Dimension(5, DimensionUnit::VP));
        model.SetStrokeColor(DEFAULT_TEXT_COLOR);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the corresponding JSON
     */
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("strokeWidth"), "5.00vp");
    EXPECT_EQ(json->GetString("strokeColor"), "#FF000000");
}

/**
 * @tc.name: TextAreaMinLinesTest001
 * @tc.desc: Test attrs about stroke
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, TextAreaMinLinesTest001, TestSize.Level0)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetTextColor(DEFAULT_TEXT_COLOR);
        model.SetMinLines(1);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the corresponding JSON
     */
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("minLines"), "1");
}
}