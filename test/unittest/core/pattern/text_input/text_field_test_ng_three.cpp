/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {

class TextFieldTestNgThree : public TestNG {
    void SetUp() override;
    void TearDown() override;
};

void TextFieldTestNgThree::SetUp() {}

void TextFieldTestNgThree::TearDown() {}

/**
 * @tc.name: OnThemeScopeUpdate002
 * @tc.desc: Test OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnThemeScopeUpdate002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->cleanNodeResponseArea_ =
        AceType::MakeRefPtr<CleanNodeResponseArea>(AIWriteAdapter::WeakClaim(AceType::RawPtr(textFieldPattern)));
    int32_t themeScopeId = 1;
    textFieldPattern->OnThemeScopeUpdate(themeScopeId);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: TwinklingByFocus001
 * @tc.desc: Test TwinklingByFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, TwinklingByFocus001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->focusIndex_ = FocuseIndex::TEXT;
    textFieldPattern->TwinklingByFocus();
    EXPECT_EQ(textFieldPattern->cursorVisible_, false);
}

/**
 * @tc.name: PreferredTextHeight001
 * @tc.desc: Test PreferredTextHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, PreferredTextHeight001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->focusIndex_ = FocuseIndex::TEXT;
    bool isPlaceholder = true;
    bool isAlgorithmMeasure = true;
    textFieldPattern->PreferredTextHeight(isPlaceholder, isAlgorithmMeasure);
    EXPECT_EQ(textFieldPattern->cursorVisible_, false);
}

/**
 * @tc.name: GetLineBeginPosition001
 * @tc.desc: Test GetLineBeginPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, GetLineBeginPosition001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"hhh";
    int32_t originCaretPosition = 1;
    bool needToCheckLineChanged = true;
    auto result = textFieldPattern->GetLineBeginPosition(originCaretPosition, needToCheckLineChanged);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CursorMoveToParagraphEnd001
 * @tc.desc: Test CursorMoveToParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CursorMoveToParagraphEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 0;
    auto result = textFieldPattern->CursorMoveToParagraphEnd();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveUpOperation001
 * @tc.desc: Test CursorMoveUpOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CursorMoveUpOperation001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    auto result = textFieldPattern->CursorMoveUpOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveUpOperation002
 * @tc.desc: Test CursorMoveUpOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CursorMoveUpOperation002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->textRect_ = { 5, 5, 5, 5 };
    auto result = textFieldPattern->CursorMoveUpOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveDownOperation001
 * @tc.desc: Test CursorMoveDownOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CursorMoveDownOperation001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    auto result = textFieldPattern->CursorMoveDownOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveDownOperation002
 * @tc.desc: Test CursorMoveDownOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CursorMoveDownOperation002, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 5;
    textFieldPattern->textRect_ = { 1, 1, 1, 1 };
    auto result = textFieldPattern->CursorMoveDownOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: HandleParentGlobalOffsetChange001
 * @tc.desc: Test HandleParentGlobalOffsetChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleParentGlobalOffsetChange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectOverlay_->isSingleHandle_ = true;
    textFieldPattern->HandleParentGlobalOffsetChange();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: DeleteBackwardWord002
 * @tc.desc: Test DeleteBackwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, DeleteBackwardWord002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->DeleteBackwardWord();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: DeleteForwardWord002
 * @tc.desc: Test DeleteForwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, DeleteForwardWord002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->DeleteForwardWord();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLeftWord001
 * @tc.desc: Test HandleSelectionLeftWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleSelectionLeftWord001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->HandleSelectionLeftWord();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLineBegin005
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleSelectionLineBegin005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = -1;
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLineBegin006
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleSelectionLineBegin006, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionParagraghBegin001
 * @tc.desc: Test HandleSelectionParagraghBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleSelectionParagraghBegin001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 0;
    textFieldPattern->HandleSelectionParagraghBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionParagraghBegin002
 * @tc.desc: Test HandleSelectionParagraghBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleSelectionParagraghBegin002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 5;
    textFieldPattern->contentController_->content_ = u"hhhhh";
    textFieldPattern->HandleSelectionParagraghBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLineEnd001
 * @tc.desc: Test HandleSelectionLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleSelectionLineEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 1;
    textFieldPattern->contentController_->content_ = u"hhhhhhh";
    textFieldPattern->HandleSelectionLineEnd();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: SetSelection001
 * @tc.desc: Test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, SetSelection001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    SelectionOptions options;
    bool isForward = true;
    textFieldPattern->SetSelection(start, end, options, isForward);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: CalcDecoratorHeight001
 * @tc.desc: Test CalcDecoratorHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CalcDecoratorHeight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RefPtr<FrameNode> decoratorNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    textFieldPattern->CalcDecoratorHeight(decoratorNode);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: ResetObscureTickCountDown001
 * @tc.desc: Test ResetObscureTickCountDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, ResetObscureTickCountDown001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textObscured_ = true;
    textFieldPattern->ResetObscureTickCountDown();
    EXPECT_EQ(textFieldPattern->obscureTickCountDown_, 0);
}

/**
 * @tc.name: ToTreeJson001
 * @tc.desc: Test ToTreeJson
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, ToTreeJson001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    InspectorConfig config;
    textFieldPattern->ToTreeJson(json, config);
    EXPECT_EQ(textFieldPattern->obscureTickCountDown_, 0);
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: Test DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, DumpAdvanceInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(textFieldPattern->customKeyboard_, nullptr);
    textFieldPattern->customKeyboardBuilder_ = []() {};
    textFieldPattern->DumpAdvanceInfo();
    EXPECT_EQ(textFieldPattern->isCustomKeyboardAttached_, false);
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.desc: Test DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, DumpAdvanceInfo002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->customKeyboardBuilder_ = []() {};
    textFieldPattern->DumpAdvanceInfo();
    EXPECT_EQ(textFieldPattern->isCustomKeyboardAttached_, false);
}

/**
 * @tc.name: CheckAutoSave001
 * @tc.desc: Test CheckAutoSave
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CheckAutoSave001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"hh";
    auto result = textFieldPattern->CheckAutoSave();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: CheckPasswordAreaState002
 * @tc.desc: Test CheckPasswordAreaState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, CheckPasswordAreaState002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    textFieldPattern->showPasswordState_ = false;
    textFieldPattern->CheckPasswordAreaState();
    EXPECT_EQ(textFieldPattern->responseArea_, 0);
}

/**
 * @tc.name: UpdateFocusForward001
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, UpdateFocusForward001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto focusHub = textFieldPattern->GetFocusHub();
    focusHub->currentFocus_ = true;
    textFieldPattern->focusIndex_ = FocuseIndex::TEXT;
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    auto result = textFieldPattern->UpdateFocusForward();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateFocusForward002
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, UpdateFocusForward002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto focusHub = textFieldPattern->GetFocusHub();
    focusHub->currentFocus_ = true;
    textFieldPattern->focusIndex_ = FocuseIndex::CANCEL;
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    auto result = textFieldPattern->UpdateFocusForward();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateFocusBackward001
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, UpdateFocusBackward001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->focusIndex_ = FocuseIndex::UNIT;
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    auto result = textFieldPattern->UpdateFocusBackward();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PaintUnitRect001
 * @tc.desc: Test PaintUnitRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, PaintUnitRect001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->PaintUnitRect();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnWindowSizeChanged001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t width = 1;
    int32_t height = 1;
    WindowSizeChangeReason type = WindowSizeChangeReason::ROTATION;
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, true);
    textFieldPattern->OnWindowSizeChanged(width, height, type);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnWindowSizeChanged002
 * @tc.desc: Test OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnWindowSizeChanged002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t width = 1;
    int32_t height = 1;
    WindowSizeChangeReason type = WindowSizeChangeReason::ROTATION;
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->OnWindowSizeChanged(width, height, type);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange001
 * @tc.desc: Test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, TriggerAvoidOnCaretChange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RefPtr<SafeAreaManager> safeAreaManager_ = nullptr;
    textFieldPattern->TriggerAvoidOnCaretChange();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange002
 * @tc.desc: Test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, TriggerAvoidOnCaretChange002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->TriggerAvoidOnCaretChange();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: ConvertGlobalToLocalOffset001
 * @tc.desc: Test ConvertGlobalToLocalOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, ConvertGlobalToLocalOffset001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    Offset globalOffset;
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->ConvertGlobalToLocalOffset(globalOffset);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: NeedDrawPreviewText001
 * @tc.desc: Test NeedDrawPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, NeedDrawPreviewText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->hasPreviewText_ = false;
    textFieldPattern->selectController_->caretInfo_.index = 1;
    auto result = textFieldPattern->NeedDrawPreviewText();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate002
 * @tc.desc: Test OnTextGestureSelectionUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnTextGestureSelectionUpdate002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentScroller_.isScrolling = true;
    textFieldPattern->contentController_->content_ = u"hhh";
    int32_t start = 1;
    int32_t end = 1;
    TouchEventInfo info = TouchEventInfo("info");
    TouchLocationInfo tinfo("test", 0);
    info.touches_.push_back(tinfo);
    textFieldPattern->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd001
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnTextGestureSelectionEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = false;
    textFieldPattern->contentRect_.width_ = 1;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd002
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnTextGestureSelectionEnd002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = false;
    locationInfo.localLocation_.deltaY_ = 1;
    textFieldPattern->contentRect_.height_ = 2;
    textFieldPattern->contentRect_.width_ = 1;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd003
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnTextGestureSelectionEnd003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = false;
    locationInfo.localLocation_.deltaY_ = 1;
    textFieldPattern->contentRect_.width_ = 2;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd004
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, OnTextGestureSelectionEnd004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = true;
    locationInfo.localLocation_.deltaY_ = 1;
    textFieldPattern->contentRect_.width_ = 2;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: IsShowAIWrite001
 * @tc.desc: Test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, IsShowAIWrite001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    ASSERT_NE(textFieldTheme, nullptr);
    textFieldTheme->aiWriteBundleName_ = "hhh";
    textFieldTheme->aiWriteAbilityName_ = "";
    auto result = textFieldPattern->IsShowAIWrite();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleOnAIWrite001
 * @tc.desc: Test HandleOnAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, HandleOnAIWrite001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto aiWriteAdapter = AceType::MakeRefPtr<AIWriteAdapter>();
    textFieldPattern->aiWriteAdapter_ = aiWriteAdapter;
    textFieldPattern->HandleOnAIWrite();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: InsertOrDeleteSpace002
 * @tc.desc: Test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, InsertOrDeleteSpace002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"hh";
    int32_t index = 0;
    auto result = textFieldPattern->InsertOrDeleteSpace(index);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DeleteTextRange001
 * @tc.desc: Test DeleteTextRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, DeleteTextRange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = 1;
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->DeleteTextRange(start, end, direction);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: DeleteTextRange002
 * @tc.desc: Test DeleteTextRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, DeleteTextRange002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = -1;
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->DeleteTextRange(start, end, direction);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: DeleteTextRange003
 * @tc.desc: Test DeleteTextRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, DeleteTextRange003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = 2;
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->DeleteTextRange(start, end, direction);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: GetAcceptedTouchLocationInfo001
 * @tc.desc: Test GetAcceptedTouchLocationInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, GetAcceptedTouchLocationInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchEventInfo info = TouchEventInfo("info");
    info.changedTouches_.clear();
    textFieldPattern->moveCaretState_.isMoveCaret = false;
    textFieldPattern->isSelecting_ = true;
    auto result = textFieldPattern->GetAcceptedTouchLocationInfo(info);
    EXPECT_EQ(result, std::nullopt);
}

/**
 * @tc.name: GetPaddingBottom001
 * @tc.desc: Test GetPaddingBottom
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, GetPaddingBottom001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto result = textFieldPattern->GetPaddingBottom();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ExecuteInputCommand001
 * @tc.desc: Test ExecuteInputCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, ExecuteInputCommand001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    InputCommandInfo info;
    info.reason = InputReason::IME;
    textFieldPattern->ExecuteInputCommand(info);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: ExecuteInputCommand002
 * @tc.desc: Test ExecuteInputCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, ExecuteInputCommand002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    InputCommandInfo info;
    info.reason = InputReason::AI_WRITE;
    info.deleteRange.start = 1;
    info.deleteRange.end = 1;
    textFieldPattern->ExecuteInputCommand(info);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: SetIsEnableSubWindowMenu001
 * @tc.desc: Test SetIsEnableSubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, SetIsEnableSubWindowMenu001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->SetIsEnableSubWindowMenu();
    EXPECT_EQ(textFieldPattern->selectOverlay_->isHostNodeEnableSubWindowMenu_, true);
}

/**
 * @tc.name: NotifyKeyboardClosedByUser001
 * @tc.desc: Test NotifyKeyboardClosedByUser
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, NotifyKeyboardClosedByUser001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->NotifyKeyboardClosedByUser();
    EXPECT_EQ(textFieldPattern->isKeyboardClosedByUser_, false);
    auto focusHub = textFieldPattern->GetFocusHub();
    focusHub->currentFocus_ = true;
    textFieldPattern->NotifyKeyboardClosedByUser();
    EXPECT_EQ(textFieldPattern->isKeyboardClosedByUser_, false);
}

/**
 * @tc.name: NotifyKeyboardClosed001
 * @tc.desc: Test NotifyKeyboardClosed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, NotifyKeyboardClosed001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = nullptr;
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->NotifyKeyboardClosed();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: BetweenSelectedPosition002
 * @tc.desc: Test BetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, BetweenSelectedPosition002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    Offset globalOffset = { 1, 1 };
    textFieldPattern->selectController_->firstHandleInfo_.index = 1;
    textFieldPattern->selectController_->secondHandleInfo_.index = 2;
    auto result = textFieldPattern->BetweenSelectedPosition(globalOffset);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SetUnitNode005
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, SetUnitNode005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ =
        AceType::MakeRefPtr<PasswordResponseArea>(textFieldPattern, textFieldPattern->GetTextObscured());
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    textFieldPattern->unitNode_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 1);
}

/**
 * @tc.name: SetUnitNode006
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, SetUnitNode006, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ =
        AceType::MakeRefPtr<PasswordResponseArea>(textFieldPattern, textFieldPattern->GetTextObscured());
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    textFieldPattern->unitNode_ = nullptr;
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 1);
}

/**
 * @tc.name: SetUnitNode007
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, SetUnitNode007, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = nullptr;
    textFieldPattern->unitNode_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, nullptr);
}

/**
 * @tc.name: SetUnitNode008
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, SetUnitNode008, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = nullptr;
    textFieldPattern->unitNode_ = nullptr;
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, nullptr);
}

/**
 * @tc.name: IsStopEditWhenCloseKeyboard001
 * @tc.desc: Test IsStopEditWhenCloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgThree, IsStopEditWhenCloseKeyboard001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto result = textFieldPattern->IsStopEditWhenCloseKeyboard();
    EXPECT_EQ(result, true);
}
} // namespace OHOS::Ace::NG