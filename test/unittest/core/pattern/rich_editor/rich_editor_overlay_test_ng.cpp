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
int32_t testNumber0 = 0;
int32_t testNumber5 = 5;
const std::string TEST_IMAGE_SOURCE = "src/image.png";
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
    richEditorPattern->textForDisplay_ = "test";
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->spans_.front()->position = 3;
    richEditorPattern->InitSelection(Offset(0, 0));
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
    richEditorPattern->isEditing_ = true;
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
    richEditorPattern->isEditing_ = true;

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
    richEditorPattern->isEditing_ = true;
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
    richEditorPattern->isEditing_ = true;

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
    richEditorPattern->isEditing_ = true;

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
    richEditorPattern->isEditing_ = true;

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
    richEditorPattern->isEditing_ = true;

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
    richEditorPattern->isEditing_ = true;

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
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
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
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
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
    richEditorPattern->isEditing_ = true;

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
    richEditorPattern->HandleFocusEvent();
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
    richEditorPattern->HandleFocusEvent();
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
    AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_)
        ->SetCaretOffsetAndHeight(OffsetF(0, 0), 50.0f);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    textOverlayTheme->handleDiameter_ = 14.0_vp;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = touchOffset;
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.SetSourceTool(SourceTool::FINGER);
    richEditorPattern->HandleTouchDown(touchEventInfo);
    EXPECT_TRUE(richEditorPattern->moveCaretState_.isTouchCaret);
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

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: test UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
	
    /**
     * @tc.steps: step2. add text
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_2;
    richEditorController->AddTextSpan(textOptions);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->SetSelection(0, 2);
	
    /**
     * @tc.steps: step3. create RichEditorPaintMethod
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);

    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    auto paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(richEditorPattern->CreateNodePaintMethod());
	
    /**
     * @tc.steps: step4. test UpdateOverlayModifier
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    const auto& selection = richEditorPattern->GetTextSelector();
    EXPECT_EQ(selection.baseOffset, -1);
    EXPECT_EQ(selection.destinationOffset, -1);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: OnMenuItemAction001
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnMenuItemAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
	
    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
	
    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_.Update(0, 2);

    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);
	
    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->isMousePressed_ = true;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::MOUSE_MENU);
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: OnMenuItemAction002
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnMenuItemAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();
	
    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(1, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
	
    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::NO_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
	
    auto selectOverlayInfo = richEditorPattern->selectOverlay_->GetSelectOverlayInfo();
    auto selectInfoFirstHandle = selectOverlayInfo->firstHandle;
    EXPECT_FALSE(selectInfoFirstHandle.isShow);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: OnMenuItemAction003
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnMenuItemAction003, TestSize.Level1)
{
    /**
     * @tc.step: step1. get richeditor pattern and add text span.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
	
    /**
     * @tc.step: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();
    richEditorPattern->isEditing_ = true;

    /**
     * @tc.step: step3. call SetSelection
     */
    int32_t start = 0;
    int32_t end = 2;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->OnModifyDone();
    auto selectOverlay = richEditorPattern->selectOverlay_;
    richEditorPattern->SetSelection(start, end, options, false);

    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->isMousePressed_ = true;
    selectOverlay->OnMenuItemAction(OptionMenuActionId::CUT, OptionMenuType::TOUCH_MENU);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), start);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
	
    /**
     * @tc.step: step5. call SetSelection again
     */
    richEditorPattern->SetSelection(1, 2, options, false);
    richEditorPattern->OnModifyDone();
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 1);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step6. test OnMenuItemAction again
     */
    selectOverlay->OnMenuItemAction(OptionMenuActionId::SELECT_ALL, OptionMenuType::NO_MENU);
    auto selectOverlayInfo = selectOverlay->GetSelectOverlayInfo();
    auto selectInfoFirstHandle = selectOverlayInfo->firstHandle;
    EXPECT_FALSE(selectInfoFirstHandle.isShow);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: SelectionMenuOptionsTest001
 * @tc.desc: test SelectionMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SelectionMenuOptionsTest001, TestSize.Level1)
{
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<NG::MenuOptionsParam> menuOptionsItems;
    NG::MenuOptionsParam menuOptionsParam1;
    menuOptionsParam1.content = "按钮1";
    menuOptionsParam1.icon = TEST_IMAGE_SOURCE;
    menuOptionsItems.push_back(menuOptionsParam1);

    NG::MenuOptionsParam menuOptionsParam2;
    menuOptionsParam2.content = "按钮2";
    menuOptionsParam2.icon = TEST_IMAGE_SOURCE;
    menuOptionsItems.push_back(menuOptionsParam2);

    NG::MenuOptionsParam menuOptionsParam3;
    menuOptionsParam3.content = "按钮3";
    menuOptionsParam3.icon = TEST_IMAGE_SOURCE;
    menuOptionsItems.push_back(menuOptionsParam3);
    OnCreateMenuCallback onCreateMenuCallback;
    OnMenuItemClickCallback onMenuItemClick;
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

/**
 * @tc.name: SelectionMenuOptionsTest002
 * @tc.desc: test SelectionMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SelectionMenuOptionsTest002, TestSize.Level1)
{
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<NG::MenuOptionsParam> menuOptionsItems;
    NG::MenuOptionsParam menuOptionsParam1;
    menuOptionsParam1.content = "按钮1";
    menuOptionsItems.push_back(menuOptionsParam1);

    NG::MenuOptionsParam menuOptionsParam2;
    menuOptionsParam2.content = "按钮2";
    menuOptionsItems.push_back(menuOptionsParam2);

    NG::MenuOptionsParam menuOptionsParam3;
    menuOptionsParam3.content = "按钮3";
    menuOptionsItems.push_back(menuOptionsParam3);
    OnCreateMenuCallback onCreateMenuCallback;
    OnMenuItemClickCallback onMenuItemClick;
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

/**
 * @tc.name: HandleLevel001
 * @tc.desc: Test RichEditorPattern Handle Level OnFrameNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, HandleLevel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get rich editor pattern instance, then add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. show overlay
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_.Update(0, 2);

    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.steps: step3. mark framnode changed.
     */
    richEditorNode_->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_SCROLL);
    richEditorNode_->ProcessFrameNodeChangeFlag();
    EXPECT_EQ(richEditorPattern->selectOverlay_->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: HandleLevel002
 * @tc.desc: Test RichEditorPattern Handle Level on FrameNode changed finish.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, HandleLevel002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get rich editor pattern instance, then add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. show overlay
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_.Update(0, 2);

    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.steps: step3. mark framnode change finish.
     */
    richEditorNode_->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_END_SCROLL);
    richEditorNode_->ProcessFrameNodeChangeFlag();
    EXPECT_EQ(richEditorPattern->selectOverlay_->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: SetCaretWidth001
 * @tc.desc: test SetCaretWidth
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SetCaretWidth001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretWidth(-1);
    EXPECT_NE(richEditorOverlay->caretWidth_, -1);
}

/**
 * @tc.name: PaintPreviewTextDecoration001
 * @tc.desc: test PaintPreviewTextDecoration
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, PaintPreviewTextDecoration001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetPreviewTextStyle(PreviewTextStyle::NORMAL);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
    richEditorOverlay->PaintPreviewTextDecoration(context);
    EXPECT_NE(richEditorOverlay->previewTextUnderlineWidth_, 0);
}

/**
 * @tc.name: OnMenuItemAction004
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnMenuItemAction004, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::DISAPPEAR, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemAction005
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnMenuItemAction005, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::APPEAR, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnMenuItemAction006
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnMenuItemAction006, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::CAMERA_INPUT, OptionMenuType::MOUSE_MENU);
}

/**
 * @tc.name: OnCloseOverlay001
 * @tc.desc: test OnCloseOverlay
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnCloseOverlay001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    RefPtr<OverlayInfo> info = nullptr;
    info = AceType::MakeRefPtr<OverlayInfo>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnCloseOverlay(
        OptionMenuType::MOUSE_MENU, CloseReason::CLOSE_REASON_BACK_PRESSED, info);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate001
 * @tc.desc: Test GetGlyphPositionAtCoordinate.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, GetGlyphPositionAtCoordinate001, TestSize.Level1)
{
    auto offset = Offset(50.0, -80.0);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    PositionWithAffinity position = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(offset);
    EXPECT_EQ(position.position_, 0);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin001
 * @tc.desc: Test IsSelectLineHeadAndUseLeadingMargin.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, IsSelectLineHeadAndUseLeadingMargin001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool ret =richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(0);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: RichEditorOverlayTestNg001
 * @tc.desc: Test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));

    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    auto richEditorOverlayModifier = AceType::MakeRefPtr<RichEditorOverlayModifier>(
        richEditorPattern, AceType::WeakClaim(AceType::RawPtr(scrollBarModifier)), scrollEdgeEffect);
    ASSERT_NE(richEditorOverlayModifier, nullptr);

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    richEditorOverlayModifier->previewTextStyle_ = PreviewTextStyle::NORMAL;
    richEditorPattern->contentRect_ = RectF(0, 0, 10.0f, 10.0f);
    richEditorOverlayModifier->showPreviewTextDecoration_ = AceType::MakeRefPtr<PropertyBool>(1);
    richEditorOverlayModifier->caretVisible_ = AceType::MakeRefPtr<PropertyBool>(1);
    richEditorOverlayModifier->caretOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF(50, 30));
    richEditorOverlayModifier->caretWidth_ = AceType::MakeRefPtr<PropertyFloat>(10.0f);
    richEditorOverlayModifier->caretHeight_ = AceType::MakeRefPtr<PropertyFloat>(10.0f);
    richEditorOverlayModifier->contentRect_ = RectF(0, 0, 10.0, 10.0);
    richEditorOverlayModifier->onDraw(context);
    EXPECT_EQ(richEditorPattern->contentRect_.Height(), 10.0f);

    richEditorPattern->contentRect_ = RectF(0, 0, 10.0f, 50.0f);
    richEditorOverlayModifier->contentRect_ = RectF(0, 0, 100.0, 10.0);
    richEditorOverlayModifier->onDraw(context);
    richEditorOverlayModifier->contentRect_ = RectF(0, 0, 100.0, 100.0);
    richEditorOverlayModifier->onDraw(context);
    EXPECT_EQ(richEditorPattern->contentRect_.Height(), 50.0f);
}

/**
 * @tc.name: RichEditorOverlayTestNg002
 * @tc.desc: Test UpdateScrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    auto richEditorOverlayModifier = AceType::MakeRefPtr<RichEditorOverlayModifier>(
        richEditorPattern, AceType::WeakClaim(AceType::RawPtr(scrollBarModifier)), scrollEdgeEffect);
    ASSERT_NE(richEditorOverlayModifier, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto  renderContext = RenderContext::Create();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    ASSERT_NE(geometryNode, nullptr);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    richEditorPattern->InitScrollablePattern();
    richEditorOverlayModifier->UpdateScrollBar(AceType::RawPtr(paintWrapper));

    auto scrollBar = richEditorPattern->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    scrollBar->isScrollable_ = true;
    richEditorOverlayModifier->UpdateScrollBar(AceType::RawPtr(paintWrapper));
    scrollBar->positionModeUpdate_ = true;
    richEditorOverlayModifier->UpdateScrollBar(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
}

/**
 * @tc.name: RichEditorOverlayTestNg003
 * @tc.desc: test OnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    AddImageSpan();

    richEditorPattern->ShowSelectOverlay(
    richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);

    richEditorPattern->selectOverlay_->hasTransform_ = false;
    richEditorPattern->selectOverlay_->SetHandleLevelMode(HandleLevelMode::EMBED);
    richEditorPattern->selectOverlay_->OnHandleMove(RectF(1.0f, 0.0f, 10.0f, 10.0f), true);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle.GetOffset().GetX(), 1.0f);
}

/**
 * @tc.name: RichEditorOverlayTestNg004
 * @tc.desc: test CheckHandleVisible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(BUILDER_WIDTH, BUILDER_HEIGHT));

    richEditorPattern->selectOverlay_->enableHandleLevel_ = true;
    richEditorPattern->selectOverlay_->SetHandleLevelMode(HandleLevelMode::EMBED);
    auto isShow1 = richEditorPattern->selectOverlay_->CheckHandleVisible(RectF(0.0f, 0.0f, 10.0f, 10.0f));
    EXPECT_EQ(isShow1, true);

    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto isShow2 = richEditorPattern->selectOverlay_->CheckHandleVisible(RectF(0.0f, 0.0f, 10.0f, 10.0f));
    EXPECT_EQ(isShow2, true);
}

/**
 * @tc.name: RichEditorOverlayTestNg005
 * @tc.desc: test UpdateSelectorOnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->isSingleHandle_ = false;
    richEditorPattern->selectOverlay_->UpdateSelectorOnHandleMove(OffsetF(50.0f, 50.0f), false);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: RichEditorOverlayTestNg007
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::DISAPPEAR, OptionMenuType::MOUSE_MENU);
    EXPECT_TRUE(richEditorPattern->GetTextDetectEnable());
    EXPECT_FALSE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: RichEditorOverlayTestNg008
 * @tc.desc: test OnCloseOverlay
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isEditing_ = true;
    auto info = AceType::MakeRefPtr<OverlayInfo>();
    richEditorPattern->selectOverlay_->OnCloseOverlay(
        OptionMenuType::MOUSE_MENU, CloseReason::CLOSE_REASON_BACK_PRESSED, info);
    EXPECT_EQ(richEditorPattern->caretTwinkling_, true);
}

/**
 * @tc.name: RichEditorOverlayTestNg009
 * @tc.desc: test OnHandleLevelModeChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg009, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto selectOverlay = richEditorPattern->selectOverlay_;
    ASSERT_NE(selectOverlay, nullptr);
    selectOverlay->handleLevelMode_ = HandleLevelMode::EMBED;
    selectOverlay->OnHandleLevelModeChanged(HandleLevelMode::OVERLAY);
    EXPECT_EQ(selectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    selectOverlay->handleLevelMode_ = HandleLevelMode::OVERLAY;
    selectOverlay->OnHandleLevelModeChanged(HandleLevelMode::EMBED);
    EXPECT_EQ(selectOverlay->handleLevelMode_, HandleLevelMode::EMBED);
}

/**
 * @tc.name: RichEditorOverlayTestNg010
 * @tc.desc: test OnAncestorNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg010, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    richEditorPattern->selectOverlay_->OnAncestorNodeChanged(flag);
    EXPECT_EQ(richEditorPattern->selectOverlay_->IsAncestorNodeGeometryChange(flag), true);
}
} // namespace OHOS::Ace::NG