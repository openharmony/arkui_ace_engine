/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
} // namespace

class RichEditorOverlayTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorOverlayTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorOverlayTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorOverlayTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: OnCaretTwinkling001
 * @tc.desc: test on caret twinkling
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnCaretTwinkling001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->OnCaretTwinkling();
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: GetCaretRect001
 * @tc.desc: test get caret rect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, GetCaretRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretOffsetAndHeight(OffsetF(80.0f, 100.0f), 60.0f);
    auto caretRect = richEditorPattern->GetCaretRect();

    EXPECT_EQ(richEditorOverlay->GetCaretOffset(), OffsetF(80.0f, 100.0f));
    EXPECT_EQ(richEditorOverlay->GetCaretHeight(), 60.0f);
    EXPECT_EQ(caretRect.GetOffset(), richEditorOverlay->GetCaretOffset());
    EXPECT_EQ(caretRect.Height(), richEditorOverlay->GetCaretHeight());
}

/**
 * @tc.name: GetCaretRect002
 * @tc.desc: test get caret rect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, GetCaretRect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretOffsetAndHeight(OffsetF(80.0f, 100.0f), 60.0f);
    auto caretRect = richEditorPattern->GetCaretRect();

    manager->SetClickPosition({ caretRect.GetOffset().GetX(), caretRect.GetOffset().GetY() });
    manager->SetHeight(caretRect.Height());
    manager->ScrollTextFieldToSafeArea();
    EXPECT_EQ(GreatNotEqual(manager->GetClickPosition().GetX(), 0.0f), true);
    EXPECT_EQ(GreatNotEqual(manager->GetClickPosition().GetY(), 0.0f), true);

    EXPECT_EQ(GreatNotEqual(manager->GetHeight(), 0.0f), true);
    EXPECT_EQ(LessNotEqual(manager->GetHeight(), 800.0f), true);
}

/**
 * @tc.name: CaretColorTest001
 * @tc.desc: test set and get caretColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, CaretColorTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    Color patternCaretColor = richEditorPattern->GetCaretColor();
    EXPECT_EQ(patternCaretColor, SYSTEM_CARET_COLOR);
    model.SetCaretColor(Color::BLUE);
    patternCaretColor = richEditorPattern->GetCaretColor();
    EXPECT_EQ(patternCaretColor, Color::BLUE);
}

/**
 * @tc.name: SelectedBackgroundColorTest001
 * @tc.desc: test set and get selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SelectedBackgroundColorTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    Color patternSelectedBackgroundColor = richEditorPattern->GetSelectedBackgroundColor();
    EXPECT_EQ(patternSelectedBackgroundColor, SYSTEM_SELECT_BACKGROUND_COLOR);
    model.SetSelectedBackgroundColor(Color::RED);
    patternSelectedBackgroundColor = richEditorPattern->GetSelectedBackgroundColor();
    auto selectedBackgroundColorResult = Color::RED.ChangeOpacity(DEFAILT_OPACITY);
    EXPECT_EQ(patternSelectedBackgroundColor, selectedBackgroundColorResult);
}

/**
 * @tc.name: InitSelection001
 * @tc.desc: test InitSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, InitSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    richEditorPattern->paragraphs_.paragraphs_.push_front({ paragraph });
    richEditorPattern->textForDisplay_ = "test";
    richEditorPattern->InitSelection(Offset(0, 0));
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: InitSelection002
 * @tc.desc: test InitSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, InitSelection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    richEditorPattern->paragraphs_.paragraphs_.push_front({ paragraph });
    richEditorPattern->textForDisplay_ = "test";
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->spans_.front()->position = 3;
    richEditorPattern->InitSelection(Offset(0, 1));
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: Selection001
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->SetSelection(0, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    auto richEditorSelection = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection.selection[0], 0);
    EXPECT_EQ(richEditorSelection.selection[1], 0);

    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->SetSelection(0, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 1);
    auto richEditorSelection2 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection2.selection[0], 0);
    EXPECT_EQ(richEditorSelection2.selection[1], 1);

    richEditorPattern->SetSelection(3, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 1);
    auto richEditorSelection3 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection3.selection[0], 1);
    EXPECT_EQ(richEditorSelection3.selection[1], 1);

    richEditorPattern->SetSelection(-1, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 6);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection4 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection4.selection[0], 0);
    EXPECT_EQ(richEditorSelection4.selection[1], 6);
}

/**
 * @tc.name: Selection011
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection101, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    richEditorPattern->SetSelection(0, 10);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 6);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection5 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection5.selection[0], 0);
    EXPECT_EQ(richEditorSelection5.selection[1], 6);

    richEditorPattern->SetSelection(-2, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 3);
    EXPECT_EQ(richEditorPattern->caretPosition_, 3);
    auto richEditorSelection6 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection6.selection[0], 0);
    EXPECT_EQ(richEditorSelection6.selection[1], 3);

    richEditorPattern->SetSelection(-2, 8);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 6);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection7 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection7.selection[0], 0);
    EXPECT_EQ(richEditorSelection7.selection[1], 6);

    richEditorPattern->SetSelection(-2, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection8 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection8.selection[0], 6);
    EXPECT_EQ(richEditorSelection8.selection[1], 6);

    richEditorPattern->SetSelection(1, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 3);
    EXPECT_EQ(richEditorPattern->caretPosition_, 3);
    auto richEditorSelection9 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection9.selection[0], 1);
    EXPECT_EQ(richEditorSelection9.selection[1], 3);
}

/**
 * @tc.name: SetSelection002
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->SetSelection(0, 1);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.step: step1. Empty text calls the setSelection interface.
     * @tc.expected: The interface exits normally, but it does not take effect
     */
    ClearSpan();
    richEditorPattern->SetSelection(1, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
    auto richEditorSelection = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection.selection[0], 0);
    EXPECT_EQ(richEditorSelection.selection[1], 0);
    /**
     * @tc.step: step2. Extra-long text scenes.
     * @tc.expected: A portion of the selected text is not displayed, but the selection range can be updated
     * successfully
     */
    AddSpan(INIT_VALUE_3);
    SizeF sizeF(10.0f, 10.0f);
    richEditorNode_->GetGeometryNode()->SetContentSize(sizeF);
    richEditorPattern->SetSelection(15, 30);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 15);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 30);
    EXPECT_EQ(richEditorPattern->caretPosition_, 30);
    auto richEditorSelection2 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection2.selection[0], 15);
    EXPECT_EQ(richEditorSelection2.selection[1], 30);
    auto resultObject = richEditorSelection2.resultObjects.front();
    EXPECT_EQ(resultObject.valueString, INIT_VALUE_3);
    EXPECT_EQ(resultObject.offsetInSpan[0], 15);
    EXPECT_EQ(resultObject.offsetInSpan[1], 30);
}

/**
 * @tc.name: Selection003
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection003, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Call SetSelection with no menu
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSelection(start, end, options);

    /**
     * @tc.step: step4. Call SetSelection with forward selection
     * @tc.expected: Cursor at start position
     */
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), start);

    /**
     * @tc.step: step5. Call SetSelection with backward selection
     * @tc.expected: Cursor at end position
     */
    richEditorPattern->SetSelection(start, end, options, false);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), end);

    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, start);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, end);
}

/**
 * @tc.name: Selection004
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection004, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Create a scene where the text menu has popped up.
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. Call SetSelection with menu pop up
     * @tc.expected: Text is selected and the menu still pop up
     */
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options);

    /**
     * @tc.step: step5. Call SetSelection with forward selection
     * @tc.expected: Cursor at start position
     */
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);

    /**
     * @tc.step: step6. Call SetSelection with backward selection
     * @tc.expected: Cursor at end position
     */
    richEditorPattern->SetSelection(start, end, options, false);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), INIT_VALUE_1.length());

    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, INIT_VALUE_1.length());
}

/**
 * @tc.name: Selection005
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection005, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Call SetSelection with no menu
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, start);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, end);
}

/**
 * @tc.name: Selection006
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection006, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Create a scene where the text menu has popped up.
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. Call SetSelection with menu pop up.
     * @tc.expected: Text is selected and menu doesn't pop up.
     */
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, INIT_VALUE_1.length());
}

/**
 * @tc.name: Selection007
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection007, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Call SetSelection with no menu
     * @tc.expected: Text is selected and the menu pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, start);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, end);
}

/**
 * @tc.name: SetSelection
 * @tc.desc: test Set Selection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SetSelection, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->SetSelection(1, 3);
    auto info1 = richEditorController->GetSpansInfo(1, 2);
    EXPECT_EQ(info1.selection_.resultObjects.front().textStyle.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(info1.selection_.resultObjects.front().textStyle.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : info1.selection_.resultObjects.front().textStyle.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: SetSelection
 * @tc.desc: test Set Selection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SetSelection2, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->SetSelection(1, 3);
    auto info1 = richEditorController->GetSpansInfo(1, 2);
    for (const auto& pair : info1.selection_.resultObjects.front().textStyle.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: Selection008
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, Selection008, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Create a scene where the text menu has popped up.
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. Call SetSelection with menu pop up.
     * @tc.expected: Text is selected and menu pop up.
     */
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, INIT_VALUE_1.length());
}

/*
 * @tc.name: AdjustWordCursorAndSelect01
 * @tc.desc: test double click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, AdjustWordCursorAndSelect01, TestSize.Level1)
{
    using namespace std::chrono;
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(INIT_VALUE_1);
    int32_t pos = 3;

    MockDataDetectorMgr mockDataDetectorMgr;
    InitAdjustObject(mockDataDetectorMgr);

    richEditorPattern->lastAiPosTimeStamp_ = high_resolution_clock::now();
    richEditorPattern->lastClickTimeStamp_ = richEditorPattern->lastAiPosTimeStamp_ + seconds(2);
    int32_t spanStart = -1;
    std::string content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, 2);

    int32_t start = 1;
    int32_t end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 2);
    EXPECT_EQ(end, 3);

    AddSpan(INIT_VALUE_2);
    pos = 1;
    content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, 4);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 2);

    ClearSpan();
    pos = 2;
    content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, -1);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, -1);
    EXPECT_EQ(end, -1);
}

/**
 * @tc.name: MoveCaretAfterTextChange001
 * @tc.desc: test move caret after text change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, MoveCaretAfterTextChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->moveDirection_ = MoveDirection::BACKWARD;
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 4);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection::FORWARD;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection(-1);
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
}

/**
 * @tc.name: MoveHandle
 * @tc.desc: test whether the handle is moved when scrolling.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, MoveHandle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->textResponseType_ = TextResponseType::LONG_PRESS;
    richEditorPattern->selectOverlay_->ProcessOverlay({.animation = true});

    richEditorPattern->textSelector_.selectionBaseOffset = OffsetF(20, 20);
    richEditorPattern->textSelector_.firstHandle = RectF(20, 20, 20, 20);
    richEditorPattern->textSelector_.selectionDestinationOffset = OffsetF(60, 40);
    richEditorPattern->textSelector_.secondHandle = RectF(60, 40, 20, 20);
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetY(), 10);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle.GetY(), 10);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionDestinationOffset.GetY(), 30);
    EXPECT_EQ(richEditorPattern->textSelector_.secondHandle.GetY(), 30);

    richEditorPattern->OnScrollCallback(5, SCROLL_FROM_UPDATE);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetY(), 15);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle.GetY(), 15);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionDestinationOffset.GetY(), 35);
    EXPECT_EQ(richEditorPattern->textSelector_.secondHandle.GetY(), 35);
}

/**
 * @tc.name: SingleHandle001
 * @tc.desc: test show single handle with empty text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SingleHandle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = -1;
    /**
     * @tc.steps: step1. first click does not show single handle
     */
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step2. repeat click caret position show single handle
     */
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step3. repeat click away from caret position does not show single handle
     */
    richEditorPattern->selectOverlay_->SetIsSingleHandle(false);
    info.localLocation_ = Offset(50, 50);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step4. double click or long press show single handle
     */
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: SingleHandle002
 * @tc.desc: test show single handle with text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SingleHandle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    AddSpan(INIT_VALUE_1);
    TestParagraphItem paragraphItem = { .start = 0, .end = 6,
        .indexOffsetMap = { { 0, Offset(0, 5) }, { 6, Offset(50, 0) } } };
    AddParagraph(paragraphItem);
    /**
     * @tc.steps: step2. first click does not show single handle
     */
    richEditorPattern->caretPosition_ = -1;
    GestureEvent info;
    info.localLocation_ = Offset(0, 5);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step3. repeat click caret position show single handle
     */
    richEditorPattern->HandleClickEvent(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step4. repeat click away from caret position does not show single handle
     */
    richEditorPattern->selectOverlay_->SetIsSingleHandle(false);
    info.localLocation_ = Offset(50, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step5. double click or long press the end of text show single handle
     */
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step6. move single handle
     */
    auto handleOffset = OffsetF(0, 5);
    richEditorPattern->selectOverlay_->UpdateSelectorOnHandleMove(handleOffset, false);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: SingleHandle003
 * @tc.desc: test move caret by touch event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SingleHandle003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    AddSpan(INIT_VALUE_1);
    TestParagraphItem paragraphItem = { .start = 0, .end = 6,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } } };
    AddParagraph(paragraphItem);
    /**
     * @tc.steps: step2. request foucus and show caret
     */
    RequestFocus();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->StartTwinkling();
    /**
     * @tc.steps: step3. touch down caret position
     */
    auto touchOffset = Offset(0, 0);
    richEditorPattern->HandleTouchDown(touchOffset);
    EXPECT_TRUE(richEditorPattern->isTouchCaret_);
    /**
     * @tc.steps: step4. move caret position by touch move
     */
    touchOffset = Offset(50, 0);
    richEditorPattern->HandleTouchMove(touchOffset);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
}


/**
 * @tc.name: CopySelectionMenuParams001
 * @tc.desc: test CopySelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, CopySelectionMenuParams001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectOverlayInfo selectInfo;
    richEditorPattern->selectedType_ = TextSpanType::TEXT;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType::IMAGE;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType(-1);
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    callBack1 = 0;
    callBack2 = 0;
    callBack3 = 0;
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params1;
    selectInfo.isUsingMouse = true;
    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(selectInfo.menuCallback.onDisappear, nullptr);

    key = std::make_pair(TextSpanType::MIXED, TextResponseType::LONG_PRESS);
    std::shared_ptr<SelectionMenuParams> params2 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, nullptr, nullptr, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params2;
    selectInfo.isUsingMouse = false;
    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(selectInfo.menuCallback.onDisappear, nullptr);
}

/**
 * @tc.name: UpdateSelectionType001
 * @tc.desc: test UpdateSelectionType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, UpdateSelectionType001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectionInfo selection;

    ResultObject obj1;
    obj1.type = SelectSpanType::TYPESPAN;
    selection.selection_.resultObjects.push_front(obj1);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::TEXT);

    selection.selection_.resultObjects.pop_front();
    ResultObject obj2;
    obj2.type = SelectSpanType::TYPEIMAGE;
    selection.selection_.resultObjects.push_front(obj2);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::IMAGE);

    selection.selection_.resultObjects.push_front(obj1);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::MIXED);
}


/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, BindSelectionMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    callBack1 = 0;
    callBack2 = 0;
    callBack3 = 0;
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params1;

    std::function<void()> nullFunc = nullptr;

    richEditorPattern->BindSelectionMenu(
        TextResponseType::RIGHT_CLICK, TextSpanType::MIXED, nullFunc, onAppear, onDisappear);
    EXPECT_TRUE(richEditorPattern->selectionMenuMap_.empty());

    richEditorPattern->selectionMenuMap_[key] = params1;
    richEditorPattern->BindSelectionMenu(
        TextResponseType::RIGHT_CLICK, TextSpanType::MIXED, buildFunc, onAppear, onDisappear);
    EXPECT_FALSE(richEditorPattern->selectionMenuMap_.empty());

    richEditorPattern->BindSelectionMenu(
        TextResponseType::RIGHT_CLICK, TextSpanType::IMAGE, buildFunc, onAppear, onDisappear);
    EXPECT_FALSE(richEditorPattern->selectionMenuMap_.empty());
}
} // namespace OHOS::Ace::NG