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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
const Ace::TextDecoration TEXT_DECORATION_VALUE_2 = Ace::TextDecoration::UNDERLINE;
} // namespace

class RichEditorKeyboardShortcutTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
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
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 17);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::RightWord);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 21);
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
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 21);
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

    // during move caret
    richEditorPattern->floatingCaretState_.isFloatingCaretVisible = true;
    richEditorPattern->moveCaretState_.isMoveCaret = true;
    richEditorPattern->HandleSelect(CaretMoveIntent::Up);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->moveCaretState_.isMoveCaret);
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
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateTextColor, std::nullopt);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateFontWeight, Ace::FontWeight::BOLD);
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
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateTextColor, std::nullopt);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateItalicFontStyle, OHOS::Ace::FontStyle::ITALIC);
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
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateTextColor, std::nullopt);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateTextDecoration, TextDecoration::UNDERLINE);
}

/**
 * @tc.name: BeforeAddImage101
 * @tc.desc: test BeforeAddImage
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, BeforeAddImage101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateEventHub();
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto tempFunc1 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func1 = tempFunc1;
    eventHub->onWillChange_ = func1;
    auto tempFunc2 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func2 = tempFunc2;
    eventHub->onDidChange_ = func2;
    RichEditorChangeValue changeValue;
    ImageSpanOptions options;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    options.imagePixelMap = pixelMap;
    auto ret = richEditorPattern->BeforeAddImage(changeValue, options, 0);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: BeforeChangeText101
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, BeforeChangeText101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateEventHub();
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto tempFunc1 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func1 = tempFunc1;
    eventHub->onWillChange_ = func1;
    auto tempFunc2 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func2 = tempFunc2;
    eventHub->onDidChange_ = func2;
    RichEditorChangeValue changeValue;
    RichEditorPattern::OperationRecord record;
    RecordType type = RecordType::DEL_BACKWARD;
    int32_t delLength = 0;
    auto ret = richEditorPattern->BeforeChangeText(changeValue, record, type, delLength);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: GetTextThemeFontSize101
 * @tc.desc: test GetTextThemeFontSize
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, GetTextThemeFontSize101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    context->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    auto theme = context->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    auto ret = richEditorPattern->GetTextThemeFontSize();
    EXPECT_NE(ret, 0.0f);
}

/**
 * @tc.name: HandleSelectWrapper101
 * @tc.desc: test HandleSelectWrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, HandleSelectWrapper101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    OHOS::Ace::CaretMoveIntent direction = OHOS::Ace::CaretMoveIntent::Home;
    int32_t fixedPos = 0;
    auto ret = richEditorPattern->HandleSelectWrapper(direction, fixedPos);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: HandleTripleClickEvent
 * @tc.desc: test HandleTripleClickEvent001
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, HandleTripleClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TestParagraphRect paragraphRect = { .start = 0, .end = 2, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 2,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    GestureEvent info;
    int32_t start = 0;
    int32_t end = 0;
    for (auto item : paragraphItem.indexOffsetMap) {
        info.localLocation_ = item.second;
        richEditorPattern->HandleTripleClickEvent(info);
        start = std::min(richEditorPattern->GetTextContentLength(), paragraphItem.start);
        end = std::min(richEditorPattern->GetTextContentLength(), paragraphItem.start);
        EXPECT_TRUE(start == richEditorPattern->textSelector_.baseOffset);
        EXPECT_TRUE(end == richEditorPattern->textSelector_.destinationOffset);
    }
}

/**
 * @tc.name: PreferredParagraph001
 * @tc.desc: test PreferredParagraph
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, PreferredParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
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
}
/**
 * @tc.name: GetTextColorInJson001
 * @tc.desc: test GetTextColorInJson
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, GetTextColorInJson001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    std::optional<Color> value;
    auto ret = richEditorPattern->GetTextColorInJson(value);
    EXPECT_FALSE(ret.empty());
}

/**
 * @tc.name: GetPlaceHolderInJson001
 * @tc.desc: test GetPlaceHolderInJson
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, GetPlaceHolderInJson001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    host->AddChild(textframeNode);
    auto ret = richEditorPattern->GetPlaceHolderInJson();
    EXPECT_TRUE(ret.empty());
}

/**
 * @tc.name: CheckTripClickEvent001
 * @tc.desc: test CheckTripClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, CheckTripClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TimeStamp timeStamp1(std::chrono::nanoseconds(1000));
    richEditorPattern->clickInfo_.push_back(timeStamp1);
    TimeStamp timeStamp2(std::chrono::nanoseconds(2000));
    richEditorPattern->clickInfo_.push_back(timeStamp2);
    TimeStamp timeStamp3(std::chrono::nanoseconds(3000));
    richEditorPattern->clickInfo_.push_back(timeStamp3);
    GestureEvent info;
    TimeStamp timeStamp4(std::chrono::nanoseconds(4000));
    info.SetTimeStamp(timeStamp4);
    richEditorPattern->CheckTripClickEvent(info);
    EXPECT_NE(richEditorPattern->clickInfo_.size(), 4);
}

/**
 * @tc.name: HandleSelectPosition001
 * @tc.desc: test HandleSelectPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, HandleSelectPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretPosition_ = richEditorPattern->textSelector_.GetTextEnd();
    auto ret = richEditorPattern->HandleKbVerticalSelection(true);
    EXPECT_EQ(ret, 0);
    ret = richEditorPattern->HandleKbVerticalSelection(false);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: CalcLineEndPosition001
 * @tc.desc: test CalcLineEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, CalcLineEndPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->richTextRect_.y_ = 10.0f;
    richEditorPattern->contentRect_.y_ = 20.0f;
    auto ret = richEditorPattern->CalcLineEndPosition();
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GetDeletedSpan001
 * @tc.desc: test GetDeletedSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, GetDeletedSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    RichEditorChangeValue changeValue;
    int32_t innerPosition = 10;
    int32_t length = 1;
    RichEditorDeleteDirection direction = RichEditorDeleteDirection::BACKWARD;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->GetDeletedSpan(changeValue, innerPosition, length, direction);
    EXPECT_NE(innerPosition, 10);
}

/**
 * @tc.name: BeforeAddImage102
 * @tc.desc: test BeforeAddImage
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, BeforeAddImage102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateEventHub();
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto tempFunc1 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func1 = tempFunc1;
    eventHub->onWillChange_ = func1;
    auto tempFunc2 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func2 = tempFunc2;
    eventHub->onDidChange_ = func2;
    RichEditorChangeValue changeValue;
    ImageSpanOptions options;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    options.imagePixelMap = pixelMap;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 1;
    ImageSpanAttribute imageStyle;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto ret = richEditorPattern->BeforeAddImage(changeValue, options, 0);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: BeforeChangeText102
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, BeforeChangeText102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateEventHub();
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto tempFunc1 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func1 = tempFunc1;
    eventHub->onWillChange_ = func1;
    auto tempFunc2 = [](const RichEditorChangeValue&) { return true; };
    std::function<bool(const RichEditorChangeValue&)> func2 = tempFunc2;
    eventHub->onDidChange_ = func2;
    AddSpan(INIT_VALUE_1);
    RichEditorChangeValue changeValue;
    TextSpanOptions options;
    options.style = std::optional<TextStyle>(TextStyle(5));
    options.offset = 100;
    auto ret = richEditorPattern->BeforeChangeText(changeValue, options);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: GetDelPartiallySpanItem002
 * @tc.desc: test GetDelPartiallySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, GetDelPartiallySpanItem002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1->unicode = 0;
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<SpanItem>();
    spanItem2->unicode = 0;
    richEditorPattern->spans_.emplace_back(spanItem2);
    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);
    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    firstInfo.SetValue(u"test123\n");
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    std::u16string originalStr;
    int32_t originalPos = 0;
    int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
    firstInfo.SetEraseLength(firstLength);
    auto ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    EXPECT_NE(ret, nullptr);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<SpanItem>();
    spanItem3->unicode = 0;
    richEditorPattern->spans_.emplace_back(spanItem3);
    ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    EXPECT_NE(ret, nullptr);
    /**
     * @tc.steps: step4. change parameter and call function.
     */
    firstInfo.SetSpanIndex(1);
    ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: GetDeletedSpan002
 * @tc.desc: test GetDeletedSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, GetDeletedSpan002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    richEditorPattern->spans_.clear();
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    it->content = INIT_VALUE_3;
    it->position = 0;
    richEditorPattern->caretPosition_ = 1;

    RichEditorChangeValue changeValue;
    int32_t innerPosition = 10;
    int32_t length = 1;
    RichEditorDeleteDirection direction = RichEditorDeleteDirection::BACKWARD;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->GetDeletedSpan(changeValue, innerPosition, length, direction);
    EXPECT_EQ(length, 1);
}

/**
 * @tc.name: GetSelectArea101
 * @tc.desc: test GetSelectArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, GetSelectArea101, TestSize.Level1)
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
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 10.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    richEditorPattern->contentRect_ = { 0.0, 10.0, 500.0, 500.0 };
    richEditorPattern->isShowPlaceholder_ = true;
    auto res = richEditorPattern->GetSelectArea(SelectRectsType::ALL_LINES);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::LEFT_TOP_POINT);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::RIGHT_BOTTOM_POINT);
    EXPECT_TRUE(res.IsValid());
}

/**
 * @tc.name: SetCustomKeyboard001
 * @tc.desc: test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, SetCustomKeyboard001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = []() {};
    richEditorModel.SetCustomKeyboard(func, true);
    bool result =
        ViewStackProcessor::GetInstance()->GetMainFrameNode()->GetPattern<RichEditorPattern>()->keyboardAvoidance_;
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetEnterKeyType
 * @tc.desc: test SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, SetEnterKeyType, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetEnterKeyType(TextInputAction::NEW_LINE);
    richEditorNode_->MarkModifyDone();
    EXPECT_EQ(richEditorPattern->GetTextInputActionValue(richEditorPattern->GetDefaultTextInputAction()),
        TextInputAction::NEW_LINE);
    richEditorModel.SetEnterKeyType(TextInputAction::UNSPECIFIED);
    richEditorNode_->MarkModifyDone();
    EXPECT_EQ(richEditorPattern->GetTextInputActionValue(richEditorPattern->GetDefaultTextInputAction()),
        TextInputAction::NEW_LINE);
    ClearSpan();
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts205
 * @tc.desc: test HandleSelectFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts205, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. initialize style and add text span
     */
    TextStyle style;
    style.SetFontWeight(FONT_WEIGHT_BOLD);
    style.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    style.SetTextDecoration(TEXT_DECORATION_VALUE_2);

    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(contentNode->GetChildren().size(), 1);

    /**
     * @tc.steps: step3. test HandleSelectFontStyle when select nothing
     */
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_U);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetTextDecorationFirst(), TextDecoration::UNDERLINE);

    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_EQ(newSpan1->GetItalicFontStyle(), OHOS::Ace::FontStyle::ITALIC);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_B);
    EXPECT_EQ(newSpan1->GetFontWeight(), Ace::FontWeight::BOLD);

    /**
     * @tc.steps: step4. test HandleSelectFontStyle again when select text
     */
    richEditorPattern->textSelector_.Update(0, 6);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_U);
    auto newSpan2 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetTextDecorationFirst(), TextDecoration::NONE);

    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_EQ(newSpan2->GetItalicFontStyle(), OHOS::Ace::FontStyle::NORMAL);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_B);
    EXPECT_EQ(newSpan2->GetFontWeight(), Ace::FontWeight::NORMAL);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts206
 * @tc.desc: test HandleSelectFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts206, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. add text span without setting style
     */
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
    richEditorPattern->textSelector_.Update(0, 6);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);

    /**
     * @tc.steps: step3. test HandleSelectFontStyle
     */
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_U);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateTextDecoration, TextDecoration::UNDERLINE);

    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateItalicFontStyle, OHOS::Ace::FontStyle::ITALIC);

    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_B);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateFontWeight, Ace::FontWeight::BOLD);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts207 about Handle Select FontStyle
 * @tc.desc: test the text font style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, RichEditorKeyBoardShortCuts207, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. add different type span and select
     */
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    richEditorPattern->textSelector_.Update(4, 10);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);

    /**
     * @tc.steps: step3. test HandleSelectFontStyle
     */
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_U);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(1));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetTextDecorationFirst(), TextDecoration::UNDERLINE);

    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
    EXPECT_EQ(newSpan1->GetItalicFontStyle(), OHOS::Ace::FontStyle::ITALIC);

    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_B);
    auto newSpan2 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(3));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontWeight(), Ace::FontWeight::BOLD);

    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_R);
    EXPECT_EQ(newSpan2->GetFontWeight(), Ace::FontWeight::BOLD);
}

/**
 * @tc.name: ShiftMultipleSelection001
 * @tc.desc: test richEditor shift multiple selection function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorKeyboardShortcutTestNg, ShiftMultipleSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SHIFT_LEFT;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes.push_back(KeyCode::KEY_SHIFT_LEFT);
    keyEvent.pressedCodes.push_back(KeyCode::KEY_DPAD_RIGHT);
    richEditorPattern->UpdateShiftFlag(keyEvent);
    EXPECT_TRUE(richEditorPattern->shiftFlag_);

    MouseInfo mouseInfo;
    mouseInfo.button_ = MouseButton::LEFT_BUTTON;
    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    mouseInfo.SetGlobalLocation(Offset(0, 0));
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);
    richEditorPattern->textSelector_.Update(10, 20);
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);

    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    info.deviceType_ = SourceType::MOUSE;
    richEditorPattern->SetCaretPosition(10);
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);
    richEditorPattern->textSelector_.Update(10, 20);
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 10);

    keyEvent.action = KeyAction::UP;
    keyEvent.pressedCodes.pop_back();
    richEditorPattern->UpdateShiftFlag(keyEvent);
    EXPECT_TRUE(richEditorPattern->shiftFlag_);
    keyEvent.pressedCodes.pop_back();
    richEditorPattern->UpdateShiftFlag(keyEvent);
    EXPECT_FALSE(richEditorPattern->shiftFlag_);
}
} // namespace OHOS::Ace::NG