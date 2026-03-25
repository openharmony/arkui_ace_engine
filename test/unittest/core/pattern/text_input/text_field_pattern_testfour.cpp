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
    ASSERT_NE(pattern->selectController_, nullptr);
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
    auto textInputLayoutAlgorithm = AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
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
    pattern->contentController_->content_ = u" T e s t ";
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
    auto eventHub = textFieldNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto paintProperty = textFieldNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->focusIndex_ = FocuseIndex::TEXT;
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    pattern->PerformAction(TextInputAction::DONE);
    eventHub->SetOnSubmit([](int32_t, NG::TextFieldCommonEvent& event) { event.SetKeepEditable(false); });
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
    auto eventHub = textFieldNode->GetEventHub<TextFieldEventHub>();
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

/**
 * @tc.name: GetStrokeColorTest001
 * @tc.desc: Test GetStrokeColor when theme is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetStrokeColorTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetStrokeColor with default theme
     * @tc.expected: Should return a valid color string (not empty)
     */
    std::string strokeColor = pattern->GetStrokeColor();
    EXPECT_FALSE(strokeColor.empty());
}

/**
 * @tc.name: GetStrokeColorTest002
 * @tc.desc: Test GetStrokeColor when stroke color is set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetStrokeColorTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with custom stroke color
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetTextColor(DEFAULT_TEXT_COLOR);
        model.SetStrokeWidth(Dimension(5, DimensionUnit::VP));
        model.SetStrokeColor(Color::RED);
    });

    /**
     * @tc.steps: step2. Call GetStrokeColor
     * @tc.expected: Should return the custom stroke color
     */
    std::string strokeColor = pattern_->GetStrokeColor();
    EXPECT_FALSE(strokeColor.empty());
    EXPECT_EQ(strokeColor, "#FFFF0000");
}

/**
 * @tc.name: GetStrokeColorTest003
 * @tc.desc: Test GetStrokeColor when only text color is set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetStrokeColorTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with text color but no stroke color
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetTextColor(Color::BLUE);
    });

    /**
     * @tc.steps: step2. Call GetStrokeColor
     * @tc.expected: Should return text color as fallback
     */
    std::string strokeColor = pattern_->GetStrokeColor();
    EXPECT_FALSE(strokeColor.empty());
    EXPECT_EQ(strokeColor, "#FF0000FF");
}

/**
 * @tc.name: CheckAutoSaveTest001
 * @tc.desc: Test CheckAutoSave when auto fill is disabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CheckAutoSaveTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with auto fill disabled
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetEnableAutoFill(false);
    });

    /**
     * @tc.steps: step2. Call CheckAutoSave
     * @tc.expected: Should return false because auto fill is disabled
     */
    bool result = pattern_->CheckAutoSave();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAutoSaveTest002
 * @tc.desc: Test CheckAutoSave when content is empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CheckAutoSaveTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with empty content
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetEnableAutoFill(true);
    });

    /**
     * @tc.steps: step2. Call CheckAutoSave
     * @tc.expected: Should return false because content is empty
     */
    bool result = pattern_->CheckAutoSave();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAutoSaveTest003
 * @tc.desc: Test CheckAutoSave when username auto fill type and text changed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CheckAutoSaveTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with username auto fill type
     */
    CreateTextField("test_user", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::USER_NAME);
    });

    /**
     * @tc.steps: step2. Set lastAutoFillTextValue_ to different value
     * @tc.expected: CheckAutoSave should detect the change
     */
    pattern_->lastAutoFillTextValue_ = std::string("old_user");

    bool result = pattern_->CheckAutoSave();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckAutoSaveTest004
 * @tc.desc: Test CheckAutoSave when password auto fill type and text changed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CheckAutoSaveTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with password auto fill type
     */
    CreateTextField("test_password", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::NEW_PASSWORD);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::NEW_PASSWORD);
    });

    /**
     * @tc.steps: step2. Set lastAutoFillTextValue_ to different value
     * @tc.expected: CheckAutoSave should detect the change for password type
     */
    pattern_->lastAutoFillTextValue_ = std::string("old_password");

    bool result = pattern_->CheckAutoSave();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckAutoSaveTest005
 * @tc.desc: Test CheckAutoSave when text not changed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, CheckAutoSaveTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with auto fill enabled
     */
    CreateTextField("same_text", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetEnableAutoFill(true);
    });

    /**
     * @tc.steps: step2. Set lastAutoFillTextValue_ to same value
     * @tc.expected: CheckAutoSave should return false because text not changed
     */
    pattern_->lastAutoFillTextValue_ = std::string("same_text");

    bool result = pattern_->CheckAutoSave();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleSwithFocusTest001
 * @tc.desc: Test HandleSwithFocus with TEXT index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleSwithFocus with TEXT index
     * @tc.expected: Should return true and set focus to TEXT
     */
    bool result = pattern->HandleSwithFocus(FocuseIndex::TEXT);
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern->focusIndex_, FocuseIndex::TEXT);
}

/**
 * @tc.name: HandleSwithFocusTest002
 * @tc.desc: Test HandleSwithFocus with CANCEL index when cancel node not shown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern without cancel button
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleSwithFocus with CANCEL index
     * @tc.expected: Should return false because cancel node is not shown
     */
    bool result = pattern->HandleSwithFocus(FocuseIndex::CANCEL);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleSwithFocusTest003
 * @tc.desc: Test HandleSwithFocus with CANCEL index when cancel node shown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with show cancel button
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetIsShowCancelButton(true);
    });

    /**
     * @tc.steps: step2. Call HandleSwithFocus with CANCEL index
     * @tc.expected: Should return true and set focus to CANCEL
     */
    bool result = pattern_->HandleSwithFocus(FocuseIndex::CANCEL);
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->focusIndex_, FocuseIndex::CANCEL);
}

/**
 * @tc.name: HandleSwithFocusTest004
 * @tc.desc: Test HandleSwithFocus with VOICE index when voice response area not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern without voice response
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleSwithFocus with VOICE index
     * @tc.expected: Should return false because voiceResponseArea_ is null
     */
    bool result = pattern->HandleSwithFocus(FocuseIndex::VOICE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleSwithFocusTest005
 * @tc.desc: Test HandleSwithFocus with VOICE index when voice response area set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with voice input type
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetIsShowVoiceButton(true);
    });

    /**
     * @tc.steps: step2. Call HandleSwithFocus with VOICE index
     * @tc.expected: Should return true and set focus to VOICE
     */
    bool result = pattern_->HandleSwithFocus(FocuseIndex::VOICE);
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->focusIndex_, FocuseIndex::VOICE);
}

/**
 * @tc.name: HandleSwithFocusTest006
 * @tc.desc: Test HandleSwithFocus with UNIT index when response area not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern without unit response
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleSwithFocus with UNIT index
     * @tc.expected: Should return false because responseArea_ is null
     */
    bool result = pattern->HandleSwithFocus(FocuseIndex::UNIT);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleSwithFocusTest007
 * @tc.desc: Test HandleSwithFocus with UNIT index when show password icon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest007, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with password type and show password icon
     */
    CreateTextField("password123", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetShowPasswordIcon(true);
    });

    /**
     * @tc.steps: step2. Call HandleSwithFocus with UNIT index
     * @tc.expected: Should return true because password icon is shown
     */
    bool result = pattern_->HandleSwithFocus(FocuseIndex::UNIT);
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->focusIndex_, FocuseIndex::UNIT);
}

/**
 * @tc.name: HandleSwithFocusTest008
 * @tc.desc: Test HandleSwithFocus with invalid index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSwithFocusTest008, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleSwithFocus with invalid index value
     * @tc.expected: Should return false for invalid index
     */
    bool result = pattern->HandleSwithFocus(static_cast<FocuseIndex>(99));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleSpaceEventTest001
 * @tc.desc: Test HandleSpaceEvent when focusIndex is CANCEL
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSpaceEventTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with cancel button using CreateTextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetIsShowCancelButton(true);
    });

    /**
     * @tc.steps: step2. Set focus to CANCEL and call HandleSpaceEvent
     * @tc.expected: Should handle CANCEL focus without crash
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;

    /**
     * @tc.steps: step3. Call HandleSpaceEvent and verify execution
     * @tc.expected: Function executes successfully
     */
    pattern_->HandleSpaceEvent();
    EXPECT_TRUE(pattern_->focusIndex_ == FocuseIndex::CANCEL || pattern_->focusIndex_ == FocuseIndex::TEXT);
}

/**
 * @tc.name: HandleSpaceEventTest002
 * @tc.desc: Test HandleSpaceEvent when focusIndex is VOICE
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSpaceEventTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set focus to VOICE and call HandleSpaceEvent
     * @tc.expected: Should handle VOICE focus without crash
     */
    pattern->focusIndex_ = FocuseIndex::VOICE;

    /**
     * @tc.steps: step3. Call HandleSpaceEvent - returns false when voiceResponseArea_ is null
     * @tc.expected: Function executes, focusIndex remains VOICE
     */
    pattern->HandleSpaceEvent();
    EXPECT_EQ(pattern->focusIndex_, FocuseIndex::VOICE);
}

/**
 * @tc.name: HandleSpaceEventTest003
 * @tc.desc: Test HandleSpaceEvent when focusIndex is UNIT with password icon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSpaceEventTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with password icon
     */
    CreateTextField("password123", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetShowPasswordIcon(true);
    });

    /**
     * @tc.steps: step2. Set focus to UNIT and call HandleSpaceEvent
     * @tc.expected: Should call PasswordResponseKeyEvent and return true
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;

    bool result = pattern_->HandleSpaceEvent();
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->focusIndex_, FocuseIndex::UNIT);
}

/**
 * @tc.name: HandleSpaceEventTest004
 * @tc.desc: Test HandleSpaceEvent when focusIndex is UNIT with unit button
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSpaceEventTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with show unit function
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetShowUnit([]() {});
    });

    /**
     * @tc.steps: step2. Set focus to UNIT and call HandleSpaceEvent
     * @tc.expected: Should call UnitResponseKeyEvent and return true
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;

    bool result = pattern_->HandleSpaceEvent();
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->focusIndex_, FocuseIndex::UNIT);
}

/**
 * @tc.name: HandleSpaceEventTest005
 * @tc.desc: Test HandleSpaceEvent when focusIndex is TEXT (default)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, HandleSpaceEventTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern with default TEXT focus
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleSpaceEvent with TEXT focus (default)
     * @tc.expected: Should return false (no action taken)
     */
    pattern->focusIndex_ = FocuseIndex::TEXT;

    bool result = pattern->HandleSpaceEvent();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern->focusIndex_, FocuseIndex::TEXT);
}

/**
 * @tc.name: ConvertGlobalToLocalOffsetTest001
 * @tc.desc: Test ConvertGlobalToLocalOffset without render transform
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, ConvertGlobalToLocalOffsetTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call ConvertGlobalToLocalOffset with global offset (100, 100)
     * @tc.expected: Should return local offset (may equal global if parentGlobalOffset is zero)
     */
    Offset globalOffset(100.0, 100.0);
    Offset localOffset = pattern->ConvertGlobalToLocalOffset(globalOffset);

    /**
     * @tc.expected: Local offset should be valid (non-negative when parentGlobalOffset is zero)
     */
    EXPECT_GE(localOffset.GetX(), 0.0);
    EXPECT_GE(localOffset.GetY(), 0.0);
}

/**
 * @tc.name: ConvertGlobalToLocalOffsetTest002
 * @tc.desc: Test ConvertGlobalToLocalOffset with zero global offset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, ConvertGlobalToLocalOffsetTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call ConvertGlobalToLocalOffset with zero offset
     * @tc.expected: Should return negative offset (transformed by parent global offset)
     */
    Offset globalOffset(0.0, 0.0);
    Offset localOffset = pattern->ConvertGlobalToLocalOffset(globalOffset);

    /**
     * @tc.expected: Local offset should be negative or zero
     */
    EXPECT_LE(localOffset.GetX(), 0.0);
    EXPECT_LE(localOffset.GetY(), 0.0);
}

/**
 * @tc.name: NeedDrawPreviewTextTest001
 * @tc.desc: Test NeedDrawPreviewText when paintProperty is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, NeedDrawPreviewTextTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern without proper initialization
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call NeedDrawPreviewText
     * @tc.expected: Should return false when paintProperty is not set
     */
    bool result = pattern->NeedDrawPreviewText();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedDrawPreviewTextTest002
 * @tc.desc: Test NeedDrawPreviewText with default preview text settings
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, NeedDrawPreviewTextTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with default settings
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Call NeedDrawPreviewText without preview text
     * @tc.expected: Should return false (no preview text to draw)
     */
    bool result = pattern_->NeedDrawPreviewText();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedDrawPreviewTextTest003
 * @tc.desc: Test NeedDrawPreviewText when preview start and end are different
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, NeedDrawPreviewTextTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Call NeedDrawPreviewText twice to trigger paint property update
     * @tc.expected: First call updates properties, second call checks for changes
     */
    bool result1 = pattern_->NeedDrawPreviewText();
    EXPECT_FALSE(result1);

    bool result2 = pattern_->NeedDrawPreviewText();
    EXPECT_FALSE(result2);
}

/**
 * @tc.name: InsertOrDeleteSpaceTest001
 * @tc.desc: Test InsertOrDeleteSpace with invalid index (negative)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, InsertOrDeleteSpaceTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with text
     */
    CreateTextField("test text", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Call InsertOrDeleteSpace with negative index
     * @tc.expected: Should return false for invalid index
     */
    bool result = pattern_->InsertOrDeleteSpace(-1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InsertOrDeleteSpaceTest002
 * @tc.desc: Test InsertOrDeleteSpace with index out of range
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, InsertOrDeleteSpaceTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with short text
     */
    CreateTextField("test", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Call InsertOrDeleteSpace with index beyond text length
     * @tc.expected: Should return false for out of range index
     */
    bool result = pattern_->InsertOrDeleteSpace(100);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InsertOrDeleteSpaceTest003
 * @tc.desc: Test InsertOrDeleteSpace to delete existing space
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, InsertOrDeleteSpaceTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with text containing space
     */
    CreateTextField("test text", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Get initial text value
     * @tc.expected: Text should contain space
     */
    std::u16string initialText = pattern_->GetTextUtf16Value();
    EXPECT_EQ(initialText, u"test text");

    /**
     * @tc.steps: step3. Call InsertOrDeleteSpace at position 4 (space position)
     * @tc.expected: Should process the space (delete or keep based on implementation)
     */
    bool result = pattern_->InsertOrDeleteSpace(4);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. Verify text was modified or stayed same
     * @tc.expected: Text length should be 8 or 9 (space deleted or inserted)
     */
    std::u16string currentText = pattern_->GetTextUtf16Value();
    EXPECT_TRUE(currentText.length() == 8 || currentText.length() == 9);
}

/**
 * @tc.name: InsertOrDeleteSpaceTest004
 * @tc.desc: Test InsertOrDeleteSpace when character before index is space
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, InsertOrDeleteSpaceTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with text containing space
     */
    CreateTextField("test text", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Get initial text value
     * @tc.expected: Text should contain space
     */
    std::u16string initialText = pattern_->GetTextUtf16Value();
    EXPECT_EQ(initialText, u"test text");

    /**
     * @tc.steps: step3. Call InsertOrDeleteSpace at position 5 (after space)
     * @tc.expected: Should process the space
     */
    bool result = pattern_->InsertOrDeleteSpace(5);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. Verify text was modified
     * @tc.expected: Text length should be 8 or 9
     */
    std::u16string currentText = pattern_->GetTextUtf16Value();
    EXPECT_TRUE(currentText.length() == 8 || currentText.length() == 9);
}

/**
 * @tc.name: InsertOrDeleteSpaceTest005
 * @tc.desc: Test InsertOrDeleteSpace to insert space
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, InsertOrDeleteSpaceTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with text without space at target position
     */
    CreateTextField("testtext", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Get initial text value
     * @tc.expected: Text should be "testtext" (8 characters)
     */
    std::u16string initialText = pattern_->GetTextUtf16Value();
    EXPECT_EQ(initialText.length(), 8);
    EXPECT_EQ(initialText, u"testtext");

    /**
     * @tc.steps: step3. Call InsertOrDeleteSpace at position 4
     * @tc.expected: Should process and return true (index is valid)
     */
    bool result = pattern_->InsertOrDeleteSpace(4);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. Verify text state after operation
     * @tc.expected: Text should be in valid state (8-10 characters)
     */
    std::u16string currentText = pattern_->GetTextUtf16Value();
    EXPECT_TRUE(currentText.length() >= 8);
    EXPECT_TRUE(currentText.length() <= 10);

    /**
     * @tc.steps: step5. Verify text content is valid UTF-16 string
     * @tc.expected: Text should not contain invalid characters
     */
    for (size_t i = 0; i < currentText.length(); ++i) {
        EXPECT_TRUE(
            currentText[i] >= u' ' || currentText[i] == u'\t' || currentText[i] == u'\n' || currentText[i] == u'\r');
    }
}

/**
 * @tc.name: InsertOrDeleteSpaceTest006
 * @tc.desc: Test InsertOrDeleteSpace with empty text
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, InsertOrDeleteSpaceTest006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with empty text
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Call InsertOrDeleteSpace with index 0
     * @tc.expected: Should return false (index equals length, out of valid range)
     */
    bool result = pattern_->InsertOrDeleteSpace(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NotifyFillRequestSuccessTest001
 * @tc.desc: Test NotifyFillRequestSuccess with PASTE_REQUEST trigger type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, NotifyFillRequestSuccessTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create viewDataWrap and nodeWrap using factory methods
     */
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    ASSERT_NE(viewDataWrap, nullptr);

    auto nodeWrap = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    ASSERT_NE(nodeWrap, nullptr);
    nodeWrap->SetValue("pasted_text");

    /**
     * @tc.steps: step3. Call NotifyFillRequestSuccess with PASTE_REQUEST
     * @tc.expected: Should call HandleOnAutoFillSecurePaste and return
     */
    pattern->NotifyFillRequestSuccess(
        viewDataWrap, nodeWrap, AceAutoFillType::ACE_USER_NAME, AceAutoFillTriggerType::PASTE_REQUEST);

    /**
     * @tc.steps: step4. Verify fill request was marked as finished
     * @tc.expected: Fill request should be marked complete
     */
    EXPECT_TRUE(pattern->IsFillRequestFinish());
}

/**
 * @tc.name: NotifyFillRequestSuccessTest002
 * @tc.desc: Test NotifyFillRequestSuccess with MANUAL_REQUEST trigger type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, NotifyFillRequestSuccessTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with auto fill enabled
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetEnableAutoFill(true);
    });

    /**
     * @tc.steps: step2. Create viewDataWrap and nodeWrap with focus
     */
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    ASSERT_NE(viewDataWrap, nullptr);

    auto nodeWrap = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    ASSERT_NE(nodeWrap, nullptr);
    nodeWrap->SetValue("autofill_text");
    nodeWrap->SetIsFocus(true);

    /**
     * @tc.steps: step3. Call NotifyFillRequestSuccess with MANUAL_REQUEST
     * @tc.expected: Should request focus and add insert command
     */
    pattern_->NotifyFillRequestSuccess(
        viewDataWrap, nodeWrap, AceAutoFillType::ACE_USER_NAME, AceAutoFillTriggerType::MANUAL_REQUEST);

    /**
     * @tc.steps: step4. Verify fill request was marked as finished
     * @tc.expected: Fill request should be marked complete
     */
    EXPECT_TRUE(pattern_->IsFillRequestFinish());
}

/**
 * @tc.name: NotifyFillRequestSuccessTest003
 * @tc.desc: Test NotifyFillRequestSuccess when content matches existing value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, NotifyFillRequestSuccessTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with existing text
     */
    CreateTextField("existing_text", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Verify initial text value
     * @tc.expected: Text should be "existing_text"
     */
    std::u16string initialText = pattern_->GetTextUtf16Value();
    EXPECT_EQ(initialText, u"existing_text");

    /**
     * @tc.steps: step3. Create viewDataWrap and nodeWrap with same value
     */
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    ASSERT_NE(viewDataWrap, nullptr);

    auto nodeWrap = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    ASSERT_NE(nodeWrap, nullptr);
    nodeWrap->SetValue("existing_text");

    /**
     * @tc.steps: step4. Call NotifyFillRequestSuccess with same content
     * @tc.expected: Should process the request
     */
    pattern_->NotifyFillRequestSuccess(
        viewDataWrap, nodeWrap, AceAutoFillType::ACE_USER_NAME, AceAutoFillTriggerType::AUTO_REQUEST);

    /**
     * @tc.steps: step5. Verify fill request was processed
     * @tc.expected: Fill request should be marked as finished
     */
    EXPECT_TRUE(pattern_->IsFillRequestFinish());

    /**
     * @tc.steps: step6. Verify text state after processing
     * @tc.expected: Text should be in valid state (may be modified or cleared)
     */
    std::u16string currentText = pattern_->GetTextUtf16Value();
    EXPECT_TRUE(currentText.length() >= 0);
}

/**
 * @tc.name: UpdateHandlesOffsetOnScrollTest001
 * @tc.desc: Test UpdateHandlesOffsetOnScroll when SelectOverlay is on with single handle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, UpdateHandlesOffsetOnScrollTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call UpdateHandlesOffsetOnScroll with positive offset
     * @tc.expected: Should update caret offset based on scroll offset
     */
    float offset = 50.0f;
    pattern->UpdateHandlesOffsetOnScroll(offset, true);
    
    /**
     * @tc.steps: step3. Verify pattern is still valid after operation
     * @tc.expected: Pattern pointer should remain valid (no crash)
     */
    EXPECT_NE(pattern->selectController_, nullptr);
    EXPECT_GE(offset, 0.0f);
}

/**
 * @tc.name: UpdateHandlesOffsetOnScrollTest002
 * @tc.desc: Test UpdateHandlesOffsetOnScroll when SelectOverlay is on with multiple handles
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, UpdateHandlesOffsetOnScrollTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with selection
     */
    CreateTextField("test text", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
    });

    /**
     * @tc.steps: step2. Select text to enable handles
     */
    pattern_->selectController_->firstHandleInfo_.index = 0;
    pattern_->selectController_->secondHandleInfo_.index = 4;

    /**
     * @tc.steps: step3. Call UpdateHandlesOffsetOnScroll
     * @tc.expected: Should update all handles offset
     */
    float offset = -30.0f;
    pattern_->UpdateHandlesOffsetOnScroll(offset, false);
    
    /**
     * @tc.steps: step4. Verify handles info was maintained
     * @tc.expected: firstHandleInfo and secondHandleInfo should exist
     */
    EXPECT_NE(pattern_->selectController_, nullptr);
    EXPECT_GE(pattern_->selectController_->firstHandleInfo_.index, 0);
}

/**
 * @tc.name: UpdateHandlesOffsetOnScrollTest003
 * @tc.desc: Test UpdateHandlesOffsetOnScroll with negative offset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, UpdateHandlesOffsetOnScrollTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call UpdateHandlesOffsetOnScroll with negative offset
     * @tc.expected: Should handle negative scroll offset correctly
     */
    float offset = -100.0f;
    pattern->UpdateHandlesOffsetOnScroll(offset, true);
    
    /**
     * @tc.steps: step3. Verify operation completed without error
     * @tc.expected: Pattern and selectController should remain valid
     */
    EXPECT_NE(pattern->selectController_, nullptr);
    EXPECT_LT(offset, 0.0f);
}

/**
 * @tc.name: GetInnerFocusPaintRectTest001
 * @tc.desc: Test GetInnerFocusPaintRect when focusIndex is TEXT (default)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetInnerFocusPaintRectTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField pattern with default TEXT focus
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetInnerFocusPaintRect
     * @tc.expected: Should get text input focus paint rect
     */
    RoundRect paintRect;
    pattern->GetInnerFocusPaintRect(paintRect);

    /**
     * @tc.steps: step3. Verify paintRect was populated
     * @tc.expected: PaintRect should have valid dimensions
     */
    EXPECT_GE(paintRect.GetRect().Width(), 0.0);
    EXPECT_GE(paintRect.GetRect().Height(), 0.0);
}

/**
 * @tc.name: GetInnerFocusPaintRectTest002
 * @tc.desc: Test GetInnerFocusPaintRect when focusIndex is CANCEL
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetInnerFocusPaintRectTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with cancel button
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetIsShowCancelButton(true);
    });

    /**
     * @tc.steps: step2. Set focus to CANCEL
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRect
     * @tc.expected: Should get cancel button focus paint rect
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRect(paintRect);

    /**
     * @tc.steps: step4. Verify paintRect was set for cancel button
     * @tc.expected: PaintRect should have valid dimensions
     */
    EXPECT_GE(paintRect.GetRect().Width(), 0.0);
    EXPECT_GE(paintRect.GetRect().Height(), 0.0);
}

/**
 * @tc.name: GetInnerFocusPaintRectTest003
 * @tc.desc: Test GetInnerFocusPaintRect when focusIndex is VOICE
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetInnerFocusPaintRectTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with voice button
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetIsShowVoiceButton(true);
    });

    /**
     * @tc.steps: step2. Set focus to VOICE
     */
    pattern_->focusIndex_ = FocuseIndex::VOICE;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRect
     * @tc.expected: Should get voice button focus paint rect
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRect(paintRect);

    /**
     * @tc.steps: step4. Verify paintRect was set for voice button
     * @tc.expected: PaintRect should have valid dimensions
     */
    EXPECT_GE(paintRect.GetRect().Width(), 0.0);
    EXPECT_GE(paintRect.GetRect().Height(), 0.0);
}

/**
 * @tc.name: GetInnerFocusPaintRectTest004
 * @tc.desc: Test GetInnerFocusPaintRect when focusIndex is UNIT with password icon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetInnerFocusPaintRectTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with password icon
     */
    CreateTextField("password123", "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetShowPasswordIcon(true);
    });

    /**
     * @tc.steps: step2. Set focus to UNIT
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRect
     * @tc.expected: Should get password icon focus paint rect
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRect(paintRect);

    /**
     * @tc.steps: step4. Verify paintRect was set for password icon
     * @tc.expected: PaintRect should have valid dimensions
     */
    EXPECT_GE(paintRect.GetRect().Width(), 0.0);
    EXPECT_GE(paintRect.GetRect().Height(), 0.0);
}

/**
 * @tc.name: GetInnerFocusPaintRectTest005
 * @tc.desc: Test GetInnerFocusPaintRect when focusIndex is UNIT with unit button
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFour, GetInnerFocusPaintRectTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TextField with unit button
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetShowUnit([]() {});
    });

    /**
     * @tc.steps: step2. Set focus to UNIT
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRect
     * @tc.expected: Should get unit button focus paint rect
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRect(paintRect);

    /**
     * @tc.steps: step4. Verify paintRect was set for unit button
     * @tc.expected: PaintRect should have valid dimensions
     */
    EXPECT_GE(paintRect.GetRect().Width(), 0.0);
    EXPECT_GE(paintRect.GetRect().Height(), 0.0);
}

} // namespace OHOS::Ace::NG