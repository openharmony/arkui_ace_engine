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

class RichEditorKeyboardShortcutTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    void AddParagraph(TestParagraphItem testParagraphItem);
};

void RichEditorKeyboardShortcutTestNg::SetUp()
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

void RichEditorKeyboardShortcutTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorKeyboardShortcutTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorKeyboardShortcutTestNg::AddParagraph(TestParagraphItem testParagraphItem)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testParagraphItem.start, .end = testParagraphItem.end });
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(offset, _)).WillRepeatedly(Return(index));
    }
    for (auto& cursorItem : testParagraphItem.testCursorItems) {
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFUp), Return(true)));
        float cursorHeight = 0.0f;
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, true),
            cursorItem.caretMetricsFDown.offset);
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, false),
            cursorItem.caretMetricsFUp.offset);
    }
    for (auto& paragraphRect : testParagraphItem.testParagraphRects) {
        EXPECT_CALL(*paragraph, GetRectsForRange(paragraphRect.start, paragraphRect.end, _))
            .WillRepeatedly(SetArgReferee<THIRD_PARAM>(paragraphRect.rects));
    }
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, OnKeyEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyEvent keyE;

    keyE.action = KeyAction::DOWN;
    keyE.code = KeyCode::KEY_TAB;
    EXPECT_FALSE(richEditorPattern->OnKeyEvent(keyE));

    // 2012 2015
    keyE.action = KeyAction::DOWN;
    std::vector<KeyCode> eventCodes = {
        KeyCode::KEY_DPAD_LEFT,
        KeyCode::KEY_DPAD_UP,
        KeyCode::KEY_DPAD_RIGHT,
        KeyCode::KEY_DPAD_DOWN,
    };
    std::vector<KeyCode> presscodes = {};
    keyE.pressedCodes = presscodes;
    for (auto eventCode : eventCodes) {
        keyE.pressedCodes.clear();
        keyE.pressedCodes.emplace_back(eventCode);
        keyE.code = eventCode;
        auto ret = richEditorPattern->OnKeyEvent(keyE);
        EXPECT_TRUE(ret) << "KeyCode: " + std::to_string(static_cast<int>(eventCode));
    }
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts001 about cursor move
 * @tc.desc: test the cursor move line start
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    richEditorPattern->paragraphs_.minParagraphFontSize = 19.0;
    EXPECT_EQ(richEditorPattern->paragraphs_.minParagraphFontSize.value(), 19.0);
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::Left);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 19);
    richEditorPattern->CursorMove(CaretMoveIntent::LeftWord);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 13);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::RightWord);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 24);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), textOptions.value.length());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::Home);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::End);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), textOptions.value.length());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::LineBegin);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts002 about cursor move
 * @tc.desc: test the cursor move line end and down
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->paragraphs_.minParagraphFontSize = 19.0;
    EXPECT_EQ(richEditorPattern->paragraphs_.minParagraphFontSize.value(), 19.0);
    AddSpan(INIT_VALUE_1);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    TestParagraphItem testParagraphItem = {
        .start = 0, .end = 6, .indexOffsetMap = { { 0, Offset(0, 5) }, { 6, Offset(50, 0) } }
    };
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 6 });
    CaretMetricsF metricsDown;
    CaretMetricsF metricsUp;
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        metricsDown.offset.SetX(offset.GetX());
        metricsDown.offset.SetY(offset.GetY());
        metricsUp.offset.SetX(offset.GetX());
        metricsUp.offset.SetY(offset.GetY());
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
        EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
        EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsUp), Return(true)));
    }
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->CursorMove(CaretMoveIntent::LineEnd);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 6);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->HandleSelect(CaretMoveIntent::LineEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->HandleSelect(CaretMoveIntent::Down);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts101 about Handle select
 * @tc.desc: test the select move position
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->paragraphs_.minParagraphFontSize = 19.0;
    EXPECT_EQ(richEditorPattern->paragraphs_.minParagraphFontSize.value(), 19.0);
    /**
     * @tc.steps: step2. add text span
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::Left);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 19);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::Right);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 21);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::LeftWord);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 19);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::RightWord);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 24);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), textOptions.value.length());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::LineBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts101 about Handle select
 * @tc.desc: test the select move position, up
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    style.SetTextColor(TEXT_COLOR_VALUE);
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetFontFamilies(FONT_FAMILY_VALUE);
    style.SetTextDecoration(TEXT_DECORATION_VALUE);
    style.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    EXPECT_EQ(richEditorPattern->caretPosition_, 20);
    richEditorPattern->paragraphs_.minParagraphFontSize = style.GetFontSize().ConvertToPx();
    richEditorPattern->HandleSelect(CaretMoveIntent::Up);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts201 about Handle delete comb
 * @tc.desc: test the delete comb
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts201, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleOnDeleteComb(true);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 19);
    richEditorPattern->HandleOnDeleteComb(false);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 19);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts202 about Handle Select FontStyle
 * @tc.desc: test the text font style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts202, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->textSelector_.Update(4, 20);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 4);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_B);
    EXPECT_EQ(richEditorController->updateSpanStyle_.updateFontWeight, Ace::FontWeight::BOLD);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts203 about Handle Select FontStyle
 * @tc.desc: test the text font style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts203, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->textSelector_.Update(4, 20);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 20);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_EQ(richEditorController->updateSpanStyle_.updateItalicFontStyle, OHOS::Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts204 about Handle Select FontStyle
 * @tc.desc: test the text font style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts204, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->textSelector_.Update(4, 20);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_U);
    EXPECT_EQ(richEditorController->updateSpanStyle_.updateTextDecoration, TextDecoration::UNDERLINE);
}
} // namespace OHOS::Ace::NG