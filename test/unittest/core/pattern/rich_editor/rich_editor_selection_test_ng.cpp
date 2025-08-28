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
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::u16string TEST_INSERT_LINE_SPACE = u" ";
} // namespace


class RichEditorSelectionTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<RichEditorPattern> GetRichEditorPattern();
    static void TearDownTestSuite();
};

void RichEditorSelectionTestNg::SetUp()
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

void RichEditorSelectionTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorSelectionTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorSelectionTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: SetSelection001
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection001, TestSize.Level1)
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
 * @tc.name: SetSelection002
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection002, TestSize.Level1)
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
 * @tc.name: SetSelection003
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection003, TestSize.Level1)
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
 * @tc.name: SetSelection004
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection004, TestSize.Level1)
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
 * @tc.name: SetSelection005
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection005, TestSize.Level1)
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
 * @tc.name: SetSelection006
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection006, TestSize.Level1)
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
 * @tc.name: SetSelection007
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection007, TestSize.Level1)
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
 * @tc.name: SetSelection008
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection008, TestSize.Level1)
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
 * @tc.name: SetSelection009
 * @tc.desc: test Set Selection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection009, TestSize.Level1)
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
 * @tc.name: SetSelection010
 * @tc.desc: test Set Selection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection010, TestSize.Level1)
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
 * @tc.name: SetSelection011
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection011, TestSize.Level1)
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

/**
 * @tc.name: SetSelection012
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection012, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->DumpInfo();

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);

    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), false);

    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    richEditorPattern->ScrollToSafeArea();
    EXPECT_EQ(LessNotEqual(manager->GetHeight(), 800.0f), true);

    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    Offset Offset = {1, 4};
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    int32_t index = 1;
    richEditorPattern->MouseDoubleClickParagraphEnd(index);
    EXPECT_NE(richEditorPattern->GetParagraphEndPosition(index), index);

    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    int32_t start = 1;
    int32_t end = 3;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetStart(), start);

    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetEnd(), end);

    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetEnd(), end);
}

/**
 * @tc.name: SetSelection001
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection013, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->previewTextRecord_.previewContent = u"test";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = 1;
    int32_t end = 3;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection002
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection014, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>(u"test123456");
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection003
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection015, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>(u"test123456");
    richEditorPattern->textSelector_ = TextSelector(0, 6);

    int32_t start = 1;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection004
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection016, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>(u"test123456");
    richEditorPattern->textSelector_ = TextSelector(2, 4);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->themeManager_ = theme;

    richEditorPattern->customKeyboardBuilder_ = []() {};
    richEditorPattern->DumpInfo();
    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), true);

    int32_t start = 2;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection005
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection017, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>(u"test123456");

    richEditorPattern->textSelector_ = TextSelector(2, 4);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->themeManager_ = theme;

    richEditorPattern->customKeyboardBuilder_ = []() {};
    richEditorPattern->DumpInfo();
    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), true);

    int32_t start = 2;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection006
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection018, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>(u"test123456");
    richEditorPattern->textSelector_ = TextSelector(2, 4);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->themeManager_ = theme;

    richEditorPattern->customKeyboardBuilder_ = []() {};
    richEditorPattern->DumpInfo();
    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), true);

    int32_t start = 2;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->SetSelection(start, end, options, false);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection019
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection019, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    ASSERT_EQ(richEditorPattern->contentMod_, nullptr);
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->previewTextRecord_.previewContent = u"test";
    richEditorPattern->previewTextRecord_.startOffset = 1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = -1;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: SetSelection020
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection020, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    ASSERT_EQ(richEditorPattern->contentMod_, nullptr);
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);
    richEditorPattern->previewTextRecord_.previewContent = u"test";
    richEditorPattern->previewTextRecord_.startOffset = -1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: SetSelection021
 * @tc.desc: test set selection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, SetSelection021, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->isEditing_ = true;
    richEditorController->SetSelection(0, 2);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);
    richEditorController->SetSelection(-1, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);
}

/**
 * @tc.name: InitSelection001
 * @tc.desc: test InitSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, InitSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textForDisplay_ = u"test";
    richEditorPattern->InitSelection(Offset(0, 0));
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: InitSelection002
 * @tc.desc: test InitSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, InitSelection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textForDisplay_ = u"test";
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->spans_.front()->position = 3;
    richEditorPattern->InitSelection(Offset(0, 0));
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: InitSelection003
 * @tc.desc: test InitSelection003
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, InitSelection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    AddSpan("ab\n\nab");

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    PositionWithAffinity positionWithAffinity(3, TextAffinity::DOWNSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));

    Offset touchOffset = Offset(0.0f, 0.0f);
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->InitSelection(touchOffset);

    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: InitSelection004
 * @tc.desc: test InitSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, InitSelection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->previewLongPress_ = true;
    auto offset = Offset(0, 0);
    AddSpan("hello1");
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->editingLongPress_ = false;
    PositionWithAffinity positionWithAffinity(3, TextAffinity::DOWNSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));
    ParagraphManager::ParagraphInfo info;
    info.paragraph = paragraph;
    richEditorPattern->paragraphs_.AddParagraph(std::move(info));

    richEditorPattern->InitSelection(offset);
    EXPECT_NE(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_NE(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: AdjustPlaceholderSelection001
 * @tc.desc: test AdjustPlaceholderSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, AdjustPlaceholderSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    int32_t start = 10;
    int32_t end = 20;
    Offset touchPos(11.0f, 11.0f);
    richEditorPattern->AdjustPlaceholderSelection(start, end, touchPos);
    EXPECT_NE(start, end);
}

/**
 * @tc.name: AdjustPlaceholderSelection002
 * @tc.desc: test AdjustPlaceholderSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, AdjustPlaceholderSelection002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(300.0f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 10.0, 20.0, 30.0, 40.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    CaretMetricsF metrics = { { 10.0f, 50.0f }, 20.0f };
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(metrics), Return(true)));
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(metrics), Return(true)));
    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 40.0, 50.0, 60.0, 70.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);
    TestParagraphRect paragraphRectThi = { .start = 13, .end = 18, .rects = { { 80.0, 90.0, 100.0, 110.0 } } };
    TestParagraphItem paragraphItemThi = { .start = 13, .end = 18, .testParagraphRects = { paragraphRectThi } };
    AddParagraph(paragraphItemThi);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    int32_t start = 8;
    int32_t end = 10;
    Offset touchPos(8.0f, 350.0f);
    richEditorPattern->AdjustPlaceholderSelection(start, end, touchPos);

    for (auto iter : richEditorPattern->spans_) {
        iter->position = start;
    }
    richEditorPattern->AdjustPlaceholderSelection(start, end, touchPos);
    EXPECT_NE(start, end);
}

/**
 * @tc.name: AdjustWordSelection001
 * @tc.desc: test AdjustWordSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, AdjustWordSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 100;
    int32_t end = 200;
    bool ret = true;
    ret = richEditorPattern->AdjustWordSelection(start, end);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleClickSelection001
 * @tc.desc: test HandleClickSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleClickSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->bindManager_.Reset();
    OHOS::Ace::GestureEvent info;
    EXPECT_TRUE(richEditorPattern->HandleClickSelection(info));
}

/**
 * @tc.name: IsSelectAreaVisible001
 * @tc.desc: test selectArea inVisible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, IsSelectAreaVisible001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. test IsSelectAreaVisible
     */
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: IsSelectAreaVisible002
 * @tc.desc: test selectArea Visible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, IsSelectAreaVisible002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. test IsSelectAreaVisible
     */
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: GetSelectedSpanText001
 * @tc.desc: test GetSelectedSpanText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectedSpanText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string ori = u"12345";

    std::vector<int> start = { -1, 0, 15 };
    std::vector<int> end = { 10, -3 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto ret = richEditorPattern->GetSelectedSpanText(ori, start[i], end[j]);
            EXPECT_EQ(ret, u"");
        }
    }

    auto ret = richEditorPattern->GetSelectedSpanText(ori, 0, 1);
    EXPECT_EQ(ret, u"1");
}

/**
 * @tc.name: GetSelectedSpanText002
 * @tc.desc: test get select span text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectedSpanText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto ret = richEditorPattern->GetSelectedSpanText(INIT_VALUE_1, -1, 1);
    ret = richEditorPattern->GetSelectedSpanText(INIT_VALUE_1, -1, 10);
    ret = richEditorPattern->GetSelectedSpanText(INIT_VALUE_1, 0, 1);
    EXPECT_EQ(ret, u"h");
}

/**
 * @tc.name: CaretPositionSelectEmoji001
 * @tc.desc: test CaretPositionSelectEmoji
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, CaretPositionSelectEmoji001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretMoveIntent direction = CaretMoveIntent::Left;
    auto ret = richEditorPattern->CaretPositionSelectEmoji(direction);
    EXPECT_EQ(ret, richEditorPattern->caretPosition_ - 1);
}

/**
 * @tc.name: CaretPositionSelectEmoji002
 * @tc.desc: test CaretPositionSelectEmoji
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, CaretPositionSelectEmoji002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretMoveIntent direction = CaretMoveIntent::Right;
    auto ret = richEditorPattern->CaretPositionSelectEmoji(direction);
    EXPECT_EQ(ret, richEditorPattern->caretPosition_ + 1);
}

/**
 * @tc.name: CaretPositionSelectEmoji003
 * @tc.desc: test CaretPositionSelectEmoji
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, CaretPositionSelectEmoji003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretMoveIntent direction = CaretMoveIntent::Up;
    auto ret = richEditorPattern->CaretPositionSelectEmoji(direction);
    EXPECT_EQ(ret, richEditorPattern->caretPosition_);
}

/**
 * @tc.name: GetSelectSpansPositionInfo001
 * @tc.desc: test GetSelectSpansPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpansPositionInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    ClearSpan();
    AddSpan(INIT_VALUE_2);
    auto spanItem = richEditorPattern->spans_.back();
    spanItem->unicode = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    ClearSpan();
    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textSelector_.baseOffset = 7;
    richEditorPattern->textSelector_.destinationOffset = 8;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_FALSE(richEditorPattern->hasClicked_);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textSelector_.baseOffset = 5;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_FALSE(richEditorPattern->hasClicked_);
}

/**
 * @tc.name: GetSelectSpansPositionInfo002
 * @tc.desc: test GetSelectSpansPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpansPositionInfo002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start;
    int32_t end;
    SpanPositionInfo startPositionSpanInfo(-1, -1, -1, -1);
    SpanPositionInfo endPositionSpanInfo(-1, -1, -1, -1);
    ClearSpan();
    AddSpan(INIT_VALUE_2);
    auto spanItem = richEditorPattern->spans_.back();
    spanItem->unicode = 1;
    start = 1;
    end = 2;
    richEditorPattern->GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_NE(start, 1);
    ClearSpan();
    AddSpan(INIT_VALUE_2);
    spanItem = richEditorPattern->spans_.back();
    spanItem->spanItemType = SpanItemType::CustomSpan;
    start = 1;
    end = 2;
    richEditorPattern->GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_NE(start, 1);
    ClearSpan();
    AddSpan(INIT_VALUE_2);
    spanItem = richEditorPattern->spans_.back();
    spanItem->rangeStart = 2;
    start = 1;
    end = 2;
    richEditorPattern->GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(start, 1);
    ClearSpan();
    AddSpan(INIT_VALUE_2);
    spanItem = richEditorPattern->spans_.back();
    spanItem->position = 0;
    start = 1;
    end = 2;
    richEditorPattern->GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(start, 1);
}

/**
 * @tc.name: GetSelectSpansPositionInfo003
 * @tc.desc: test GetSelectSpansPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpansPositionInfo003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start;
    int32_t end;
    SpanPositionInfo startPositionSpanInfo(-1, -1, -1, -1);
    SpanPositionInfo endPositionSpanInfo(-1, -1, -1, -1);
    ClearSpan();
    AddSpan(INIT_VALUE_2);
    start = 2;
    end = 1;
    richEditorPattern->GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(start, 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    auto spanItem = richEditorPattern->spans_.back();
    spanItem->position = 2;
    start = 1;
    end = 3;
    richEditorPattern->GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(end, 3);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    start = 5;
    end = 6;
    richEditorPattern->GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(endPositionSpanInfo.spanIndex_, startPositionSpanInfo.spanIndex_);
}

/**
 * @tc.name: JudgeSelectType001
 * @tc.desc: test RichEditorPattern JudgeSelectType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, JudgeSelectType001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    richEditorPattern->previewLongPress_ = true;
    auto offset = Offset(50.0, -80.0);
    AddSpan("hello1");
    auto selectType = richEditorPattern->JudgeSelectType(offset).second;
    EXPECT_NE(selectType, SelectType::SELECT_FORWARD);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->editingLongPress_ = true;
    selectType = richEditorPattern->JudgeSelectType(offset).second;
    EXPECT_NE(selectType, SelectType::SELECT_FORWARD);
}

/**
 * @tc.name: GetAdjustedSelectionInfo001
 * @tc.desc: test GetAdjustedSelectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetAdjustedSelectionInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::vector<std::tuple<SelectSpanType, std::u16string, RefPtr<PixelMap>>> testTuples;
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u" ", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u"", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u" ", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u"", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u" ", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u"", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u" ", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u"", nullptr);
    std::list<ResultObject> resultObjectList;
    ResultObject obj;
    for (const auto& testcase : testTuples) {
        obj.type = std::get<0>(testcase);
        obj.valueString = std::get<1>(testcase);
        obj.valuePixelMap = std::get<2>(testcase);
        resultObjectList.emplace_back(obj);
    }

    SelectionInfo textSelectInfo;
    textSelectInfo.SetResultObjectList(resultObjectList);
    auto adjustedInfo = richEditorPattern->GetAdjustedSelectionInfo(textSelectInfo);
    EXPECT_FALSE(adjustedInfo.GetSelection().resultObjects.empty());
}

/**
 * @tc.name: GetSelectSpanSplit001
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpanSplit001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto newPlusFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newPlusFrameNode);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    EXPECT_TRUE(richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo).empty());
}

/**
 * @tc.name: GetSelectSpanSplit002
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpanSplit002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: GetSelectSpanSplit003
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpanSplit003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.front().spanIndex, 0);
}

/**
 * @tc.name: GetSelectSpanSplit004
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpanSplit004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    startPositionSpanInfo.spanOffset_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetSelectSpanSplit005
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpanSplit005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    contentNode->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: GetSelectSpanSplit006
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpanSplit006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    contentNode->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 1;
    endPositionSpanInfo.spanOffset_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: GetSelectSpanSplit007
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectSpanSplit007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    contentNode->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 2;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 3);
}

/**
 * @tc.name: HandleSelect001
 * @tc.desc: test HandleSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleSelect001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    richEditorPattern->HandleSelect(CaretMoveIntent::Home);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), richEditorPattern->textSelector_.GetStart());
}

/**
 * @tc.name: HandleSelect002
 * @tc.desc: test HandleSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleSelect002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    int32_t selectStart = 0;
    int32_t selectEnd = 2;
    SelectOverlayInfo selectInfo;
    auto pipeline = richEditorNode_->GetContext();
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    selectOverlayManager->selectOverlayInfo_.isUsingMouse = true;
    richEditorPattern->HandleSelect(info, selectStart, selectEnd);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: HandleSelect003
 * @tc.desc: test HandleSelect(Ctrl+Shift+Up/Down)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleSelect003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // Init paragraphs with test content
    std::vector<std::u16string> initValues = { INIT_VALUE_1, INIT_VALUE_2, INIT_VALUE_3 };
    ParagraphManager::ParagraphInfo info;
    for (const auto& value : initValues) {
        auto insertValue = value + TEST_INSERT_LINE_SEP;
        AddSpan(insertValue);
        info.start = info.end;
        info.end = info.start + insertValue.length();
        info.paragraph = AceType::MakeRefPtr<MockParagraph>();
        richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    }

    // caret at paragraph start
    richEditorPattern->caretPosition_ = 7;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 7);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 7);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 7);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 7);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);

    // caret in paragraph middle
    richEditorPattern->ResetSelection();
    richEditorPattern->caretPosition_ = 11;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 11);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 7);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 11);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);

    // caret at paragraph end
    richEditorPattern->ResetSelection();
    richEditorPattern->caretPosition_ = 13;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 13);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 7);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 13);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);

    // during preview text input
    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 13);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);
}

/**
 * @tc.name: TripleClickSection001
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, TripleClickSection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    GestureEvent info = GestureEvent();
    info.sourceTool_ = SourceTool::FINGER;
    richEditorPattern->TripleClickSection(info, 1, 10, 2);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection002
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, TripleClickSection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    GestureEvent info = GestureEvent();
    info.sourceTool_ = SourceTool::FINGER;
    richEditorPattern->TripleClickSection(info, 10, 10, 2);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection003
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, TripleClickSection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection004
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, TripleClickSection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection005
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, TripleClickSection005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 5, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: UpdateSelectionType
 * @tc.desc: test UpdateSelectionType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, UpdateSelectionType, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectionInfo textSelectInfo;
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);
    richEditorPattern->UpdateSelectionType(textSelectInfo);
    EXPECT_EQ(richEditorPattern->selectedType_, TextSpanType::NONE);
}

/**
 * @tc.name: FireOnSelectionChange001
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, FireOnSelectionChange001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = true;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange002
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, FireOnSelectionChange002, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange003
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, FireOnSelectionChange003, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = false;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_TRUE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: GetRectsForRange001
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetRectsForRange001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;

    int32_t start = 0;
    int32_t end = 10;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());

    start = -5;
    end = 10;
    result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());

    start = 0;
    end = -5;
    result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());

    start = 10;
    end = 0;
    result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: HandleKbVerticalSelection001
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleKbVerticalSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
    richEditorPattern->caretPosition_ = 0;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
}

/**
 * @tc.name: HandleKbVerticalSelection002
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleKbVerticalSelection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
}

/**
 * @tc.name: HandleKbVerticalSelection003
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleKbVerticalSelection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    options.value = TEST_INSERT_VALUE;
    richEditorPattern->AddTextSpan(options);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 0;

    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(false), 1);
}

/**
 * @tc.name: HandleKbVerticalSelection004
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleKbVerticalSelection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretPosition_ = 0;

    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(false), 0);
}

/**
 * @tc.name: HandleKbVerticalSelection005
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, HandleKbVerticalSelection005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;

    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(false), 0);
}

/**
 * @tc.name: CalculateTruncationLength001
 * @tc.desc: test CalculateTruncationLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, CalculateTruncationLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    std::string insertValue = "hello";
    int32_t start = 2;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 4;
    int32_t length = richEditorPattern->CalculateTruncationLength(StringUtils::Str8ToStr16(insertValue), start);
    EXPECT_EQ(length, 4);
}

/**
 * @tc.name: CalculateTruncationLength002
 * @tc.desc: test CalculateTruncationLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, CalculateTruncationLength002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    std::string insertValue = "hello";
    int32_t start = 2;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    int32_t length = richEditorPattern->CalculateTruncationLength(StringUtils::Str8ToStr16(insertValue), start);
    EXPECT_EQ(length, 2);
}

/**
 * @tc.name: GetSpanRangeByResultObject001
 * @tc.desc: test GetSpanRangeByResultObject function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSpanRangeByResultObject001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto rangeStart = 1;
    SpanPosition spanPosition;
    spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = rangeStart;
    ResultObject result;
    result.spanPosition = spanPosition;
    result.offsetInSpan[0] = 1;
    result.offsetInSpan[1] = 2;
    auto [selectStartResult, selectEndResult] = richEditorPattern->GetSpanRangeByResultObject(result);
    auto selectStart = 2;
    auto selectEnd = 3;
    EXPECT_EQ(selectStart, selectStartResult);
    EXPECT_EQ(selectEnd, selectEndResult);
}

/**
 * @tc.name: GetSpanRangeByResultObject002
 * @tc.desc: test GetSpanRangeByResultObject function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSpanRangeByResultObject002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPosition spanPosition;
    ResultObject result;
    result.spanPosition = spanPosition;
    result.offsetInSpan[0] = 1;
    result.offsetInSpan[1] = 2;
    auto [selectStartResult, selectEndResult] = richEditorPattern->GetSpanRangeByResultObject(result);
    auto selectStart = 1;
    auto selectEnd = 2;
    EXPECT_EQ(selectStart, selectStartResult);
    EXPECT_EQ(selectEnd, selectEndResult);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility001
 * @tc.desc: test UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, UpdateSelectionAndHandleVisibility001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->sourceTool_ = SourceTool::MOUSE;
    richEditorPattern->releaseInDrop_ = true;
    AddSpan("test--test");

    richEditorPattern->textSelector_.Update(5, 10);
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->insertValueLength_ = 5;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->UpdateSelectionAndHandleVisibility();
    ASSERT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    ASSERT_EQ(richEditorPattern->textSelector_.destinationOffset, 5);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility002
 * @tc.desc: test UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, UpdateSelectionAndHandleVisibility002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->sourceTool_ = SourceTool::MOUSE;
    richEditorPattern->releaseInDrop_ = true;
    AddSpan("test--test");

    richEditorPattern->textSelector_.Update(5, 10);
    richEditorPattern->lastCaretPosition_ = 5;
    richEditorPattern->insertValueLength_ = 5;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->UpdateSelectionAndHandleVisibility();
    ASSERT_EQ(richEditorPattern->textSelector_.baseOffset, 5);
    ASSERT_EQ(richEditorPattern->textSelector_.destinationOffset, 10);
}

/**
 * @tc.name: GetSelectArea001
 * @tc.desc: test GetSelectArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSelectArea001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };
    richEditorPattern->isShowPlaceholder_ = true;
    auto res = richEditorPattern->GetSelectArea(SelectRectsType::ALL_LINES);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::LEFT_TOP_POINT);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::RIGHT_BOTTOM_POINT);
    EXPECT_TRUE(res.IsValid());
}

/**
 * @tc.name: RichEditorController006
 * @tc.desc: test get span info
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectionTestNg, GetSpansInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    auto info1 = richEditorController->GetSpansInfo(1, 10);
    EXPECT_EQ(info1.selection_.selection[0], 1);
    EXPECT_EQ(info1.selection_.selection[1], 10);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 3);
    auto info2 = richEditorController->GetSpansInfo(10, 1);
    EXPECT_EQ(info2.selection_.selection[0], 1);
    EXPECT_EQ(info2.selection_.selection[1], 10);
    auto info3 = richEditorController->GetSpansInfo(-1, 10);
    EXPECT_EQ(info3.selection_.selection[0], 0);
    EXPECT_EQ(info3.selection_.selection[1], 10);
    auto info4 = richEditorController->GetSpansInfo(1, -10);
    EXPECT_EQ(info4.selection_.selection[0], 0);
    EXPECT_EQ(info4.selection_.selection[1], 1);
}

} // namespace OHOS::Ace::NG