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
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components/text_field/textfield_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
const Dimension MAGNIFIERNODE_WIDTH = 127.0_vp;
const Dimension MAGNIFIERNODE_HEIGHT = 95.0_vp;
SelectionRangeInfo testSelectionRange(0, 0);
} // namespace

class RichEditorBaseTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    void TestMagnifier(const RefPtr<RichEditorPattern>& richEditorPattern,
        const RefPtr<MagnifierController>& controller, const OffsetF& localOffset);
    void InitMagnifierParams(const SizeF& frameSize);
};

void RichEditorBaseTestNg::SetUp()
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

void RichEditorBaseTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorBaseTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorBaseTestNg::InitMagnifierParams(const SizeF& frameSize)
{
    // set frameSize to RichEditor
    ASSERT_NE(richEditorNode_, nullptr);
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(frameSize);

    // set frameSize to RootNode
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto rootUINode = pipeline->GetRootElement();
    ASSERT_NE(rootUINode, nullptr);
    auto rootGeometryNode = rootUINode->GetGeometryNode();
    ASSERT_NE(rootGeometryNode, nullptr);
    rootGeometryNode->SetFrameSize(frameSize);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textfieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textfieldTheme));
}

/**
 * @tc.name: RichEditorModel001
 * @tc.desc: test create
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    EXPECT_EQ(static_cast<int32_t>(ViewStackProcessor::GetInstance()->elementsStack_.size()), 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel002
 * @tc.desc: test create
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel002, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetDraggable(true);
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode()->draggable_);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel003
 * @tc.desc: test set on ready
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel003, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = []() { testOnReadyEvent = 1; };
    richEditorModel.SetOnReady(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnReady();
    EXPECT_EQ(testOnReadyEvent, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel004
 * @tc.desc: test set about to IME input
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel004, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorInsertValue&) {
        testAboutToIMEInput = 1;
        return true;
    };
    richEditorModel.SetAboutToIMEInput(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorInsertValue info;
    EXPECT_TRUE(eventHub->FireAboutToIMEInput(info));
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel005
 * @tc.desc: test set on IME input complete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel005, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorAbstractSpanResult&) { testOnIMEInputComplete = 1; };
    richEditorModel.SetOnIMEInputComplete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorAbstractSpanResult info;
    eventHub->FireOnIMEInputComplete(info);
    EXPECT_EQ(testOnIMEInputComplete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel006
 * @tc.desc: test set about to delete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel006, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorDeleteValue&) {
        testAboutToDelete = 1;
        return true;
    };
    richEditorModel.SetAboutToDelete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorDeleteValue info;
    EXPECT_TRUE(eventHub->FireAboutToDelete(info));
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel007
 * @tc.desc: test set on delete complete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel007, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = []() { testOnDeleteComplete = 1; };
    richEditorModel.SetOnDeleteComplete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnDeleteComplete();
    EXPECT_EQ(testOnDeleteComplete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel009
 * @tc.desc: test set on text selection change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel009, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) {
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        testSelectionRange = *selectionRange;
    };
    richEditorModel.SetOnSelectionChange(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    // insert value 1
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(testSelectionRange.start_, 6);
    EXPECT_EQ(testSelectionRange.end_, 6);

    // insert value 2
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(testSelectionRange.start_, 12);
    EXPECT_EQ(testSelectionRange.end_, 12);

    // set caret position
    richEditorPattern->SetCaretPosition(3);
    EXPECT_EQ(testSelectionRange.start_, 3);
    EXPECT_EQ(testSelectionRange.end_, 3);

    // update selector
    richEditorPattern->textSelector_.Update(0, 10);
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 10);

    // update selector, reverse handle
    richEditorPattern->textSelector_.Update(10, 8);
    EXPECT_EQ(testSelectionRange.start_, 8);
    EXPECT_EQ(testSelectionRange.end_, 10);

    // select all
    richEditorPattern->HandleOnSelectAll();
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 12);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel012
 * @tc.desc: test placeholder styel value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel012, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    options.fontColor = TEXT_COLOR_VALUE;
    options.fontSize = FONT_SIZE_VALUE;
    options.fontStyle = ITALIC_FONT_STYLE_VALUE;
    options.fontWeight = FONT_WEIGHT_VALUE;
    options.fontFamilies = FONT_FAMILY_VALUE;
    richEditorModel.SetPlaceholder(options);

    auto richEditorNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode, AceType::MakeRefPtr<GeometryNode>(), richEditorNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    // test placeholder value and style is correct
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    auto spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 0);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel013
 * @tc.desc: test placeholder styel value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel013, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    richEditorModel.SetPlaceholder(options);

    auto richEditorNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode, AceType::MakeRefPtr<GeometryNode>(), richEditorNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    // test placeholder value and style is correct
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    auto spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 0);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel014
 * @tc.desc: test paragraph style wordBreak attribute
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel014, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;

    // test paragraph  style wordBreak default value
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::BREAK_WORD);

    // test paragraph style wordBreak value of WordBreak.NORMAL
    struct UpdateParagraphStyle style;
    style.wordBreak = WordBreak::NORMAL;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::NORMAL);

    // test paragraph style wordBreak value of WordBreak.BREAK_ALL
    style.wordBreak = WordBreak::BREAK_ALL;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::BREAK_ALL);
    
    // test paragraph style wordBreak value of WordBreak.BREAK_WORD
    style.wordBreak = WordBreak::BREAK_WORD;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::BREAK_WORD);
}

/**
 * @tc.name: RichEditorModel015
 * @tc.desc: test textstyle Color
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel015, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(richEditorTheme));
    richEditorTheme->textStyle_.SetTextColor(DEFAULT_TEXT_COLOR_VALUE);
    richEditorTheme->textStyle_.SetTextDecorationColor(DEFAULT_TEXT_COLOR_VALUE);

    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(textOptions);
    auto info1 = richEditorController->GetSpansInfo(1, 3);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info1.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle1.fontSize, 16);
    EXPECT_EQ(Color::FromString(textStyle1.fontColor), DEFAULT_TEXT_COLOR_VALUE);
    EXPECT_EQ(Color::FromString(textStyle1.decorationColor), DEFAULT_TEXT_COLOR_VALUE);

    ClearSpan();
    richEditorPattern->InsertValue(INIT_VALUE_2);
    auto info2 = richEditorController->GetSpansInfo(1, 2);
    ASSERT_NE(info2.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info2.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(Color::FromString(textStyle2.fontColor), DEFAULT_TEXT_COLOR_VALUE);
    EXPECT_EQ(Color::FromString(textStyle2.decorationColor), DEFAULT_TEXT_COLOR_VALUE);
}

/**
 * @tc.name: RichEditorModel016
 * @tc.desc: test paragraph style linebreakstrategy attribute
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel016, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;

    // test paragraph  style linebreakstrategy default value
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<LineBreakStrategy>(info[0].lineBreakStrategy), LineBreakStrategy::GREEDY);

    std::vector<LineBreakStrategy> strategies = { LineBreakStrategy::GREEDY, LineBreakStrategy::HIGH_QUALITY,
        LineBreakStrategy::BALANCED };
    struct UpdateParagraphStyle style;
    for (LineBreakStrategy strategy : strategies) {
        // test paragraph style linebreakstrategy
        style.lineBreakStrategy = strategy;
        richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
        info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
        EXPECT_EQ(static_cast<LineBreakStrategy>(info[0].lineBreakStrategy), strategy);
    }
}

/**
 * @tc.name: RichEditorModel017
 * @tc.desc: test GetRichEditorController、SetCustomKeyboard、BindSelectionMenu、SetPlaceholder.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel017, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create(true);
    auto richEditorNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorController = richEditorModel.GetRichEditorController();
    EXPECT_NE(richEditorController, nullptr);

    auto pattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto func = []() {};
    richEditorNode->pattern_ = nullptr;
    richEditorModel.SetCustomKeyboard(func, true);
    EXPECT_EQ(richEditorNode->GetPattern<RichEditorPattern>(), nullptr);

    std::function<void()> buildFunc = []() {};
    auto textSpanType = TextSpanType::TEXT;
    auto textResponseType = TextResponseType::LONG_PRESS;
    SelectMenuParam menuParam { .onAppear = [](int32_t, int32_t) {}, .onDisappear = []() {} };
    richEditorModel.BindSelectionMenu(textSpanType, textResponseType, buildFunc, menuParam);
    EXPECT_EQ(richEditorNode->GetPattern<RichEditorPattern>(), nullptr);

    richEditorNode->pattern_ = pattern;

    PlaceholderOptions options;
    options.value = std::nullopt;
    richEditorModel.SetPlaceholder(options);
    EXPECT_FALSE(options.value.has_value());
}

/**
 * @tc.name: KeyboardAvoidance001
 * @tc.desc: test for keyboardAvoidance
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, KeyboardAvoidance001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. setCustomKeyboard
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isEditing_ = true;

    auto func = []() {};
    richEditorModel.SetCustomKeyboard(func, true);
    EXPECT_TRUE(richEditorPattern->keyboardAvoidance_);

    /**
     * @tc.steps: step2. check keyboardAvoidance
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    EXPECT_TRUE(overlayManager->keyboardAvoidance_);
}

/**
 * @tc.name: RichEditorModel018
 * @tc.desc: test SetEnableHapticFeedback.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel018, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create(true);
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto pattern = richEditorNode->GetPattern<RichEditorPattern>();
    richEditorModel.SetEnableHapticFeedback(richEditorNode, false);
    EXPECT_FALSE(pattern->isEnableHapticFeedback_);
}

/**
 * @tc.name: RichEditorModel019
 * @tc.desc: test SetEnableAutoSpacing.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel019, TestSize.Level1)
{
    /**
     * @tc.steps: Create RichEditor node and Set EnableAutoSpacing True
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create(true);
    richEditorModel.SetEnableAutoSpacing(true);
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto pattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutProperty> layoutProperty = richEditorNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.expected: Get EnableAutoSpacing Value
     */
    EXPECT_EQ(textLayoutProperty->GetEnableAutoSpacing(), true);
    EXPECT_EQ(pattern->isEnableAutoSpacing_, true);

    /**
     * @tc.expected: Set EnableAutoSpacing False
     */
    RichEditorModelNG::SetEnableAutoSpacing(richEditorNode, false);

    /**
     * @tc.expected: Get EnableAutoSpacing Value
     */
    EXPECT_EQ(textLayoutProperty->GetEnableAutoSpacing(), false);
    EXPECT_EQ(pattern->isEnableAutoSpacing_, false);
}

/**
 * @tc.name: RichEditorModel020
 * @tc.desc: test SetSupportStyledUndo.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, RichEditorModel020, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create(false);
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto pattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isStyledUndoSupported_, false);
    richEditorModel.SetSupportStyledUndo(true);
    EXPECT_EQ(pattern->isStyledUndoSupported_, true);
    RichEditorModelNG::SetSupportStyledUndo(richEditorNode, false);
    EXPECT_EQ(pattern->isStyledUndoSupported_, false);
}

/**
 * @tc.name: CreateImageSourceInfo001
 * @tc.desc: test CreateImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, CreateImageSourceInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ImageSpanOptions info;
    auto ret = richEditorPattern->CreateImageSourceInfo(info);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: MagnifierTest001
 * @tc.desc: Test magnifier position.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, MagnifierTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto frameSize = SizeF(600.f, 400.f);
    InitMagnifierParams(frameSize);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paintOffset = richEditorPattern->GetTextPaintOffset();

    /**
     * @tc.steps: step1. localOffset is on the far left.
     */
    RefPtr<MagnifierController> controller = richEditorPattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    float offsetX = MAGNIFIER_OFFSETX.ConvertToPx();
    OffsetF localOffset(offsetX, 0.f);
    OffsetF magnifierOffset(0.f, 0.f);
    controller->SetLocalOffset(localOffset);
    ASSERT_NE(controller->magnifierFrameNode_, nullptr);
    auto geometryNode = controller->magnifierFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetX(), paintOffset.GetX() - 1.0f);

    /**
     * @tc.steps: step2. localOffset is in the normal area.
     */
    localOffset.SetX(MAGNIFIERNODE_WIDTH.ConvertToPx());
    controller->SetLocalOffset(localOffset);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetX(),
        paintOffset.GetX() + localOffset.GetX() - MAGNIFIERNODE_WIDTH.ConvertToPx() / 2);

    /**
     * @tc.steps: step3. localOffset is on the far right.
     */
    localOffset.SetX(frameSize.Width());
    controller->SetLocalOffset(localOffset);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetX(), paintOffset.GetX() + frameSize.Width() - MAGNIFIERNODE_WIDTH.ConvertToPx());
}

/**
 * @tc.name: MagnifierTest002
 * @tc.desc: Test magnifier position.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, MagnifierTest002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto frameSize = SizeF(600.f, 400.f);
    InitMagnifierParams(frameSize);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paintOffset = richEditorPattern->GetTextPaintOffset();

    /**
     * @tc.steps: step1. localOffset is on the top.
     */
    float offsetY = 1.f;
    OffsetF localOffset(100.f, offsetY);
    OffsetF magnifierOffset(0.f, 0.f);
    RefPtr<MagnifierController> controller = richEditorPattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    controller->SetLocalOffset(localOffset);
    ASSERT_NE(controller->magnifierFrameNode_, nullptr);
    auto geometryNode = controller->magnifierFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetY(), 0.f);

    /**
     * @tc.steps: step2. localOffset is in the normal area.
     */
    localOffset.SetY(MAGNIFIER_OFFSETY.ConvertToPx() + MAGNIFIERNODE_HEIGHT.ConvertToPx());
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    auto height = displayInfo->GetHeight();
    displayInfo->SetHeight(1280);
    controller->SetLocalOffset(localOffset);
    displayInfo->SetHeight(height);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetY(), paintOffset.GetY() + localOffset.GetY() - MAGNIFIERNODE_HEIGHT.ConvertToPx() / 2
        - MAGNIFIER_OFFSETY.ConvertToPx());

    /**
     * @tc.steps: step3. Test cases of magnifier.
     */
    TestMagnifier(richEditorPattern, controller, localOffset);
}

void RichEditorBaseTestNg::TestMagnifier(const RefPtr<RichEditorPattern>& richEditorPattern,
    const RefPtr<MagnifierController>& controller, const OffsetF& localOffset)
{
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    richEditorPattern->HandleBlurEvent();
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    richEditorPattern->HandleSurfaceChanged(1, 1, 1, 1, WindowSizeChangeReason::DRAG);
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutWrapper->skipMeasureContent_ = false;
    DirtySwapConfig config;
    config.frameSizeChange = true;

    richEditorPattern->selectOverlay_->isHandleMoving_ = true;
    richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(controller->GetShowMagnifier());

    richEditorPattern->selectOverlay_->isHandleMoving_ = false;
    richEditorPattern->isCursorAlwaysDisplayed_ = true;
    richEditorPattern->moveCaretState_.isMoveCaret = true;
    richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(controller->GetShowMagnifier());
    EXPECT_FALSE(richEditorPattern->isCursorAlwaysDisplayed_);
}

/**
 * @tc.name: UpdateMagnifierStateAfterLayout001
 * @tc.desc: test UpdateMagnifierStateAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, UpdateMagnifierStateAfterLayout001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<TextBase> textBase;
    richEditorPattern->selectOverlay_ = AceType::MakeRefPtr<RichEditorSelectOverlay>(textBase);
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->UpdateMagnifierStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: UpdateMagnifierStateAfterLayout002
 * @tc.desc: test UpdateMagnifierStateAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, UpdateMagnifierStateAfterLayout002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<TextBase> textBase;
    richEditorPattern->selectOverlay_ = AceType::MakeRefPtr<RichEditorSelectOverlay>(textBase);
    WeakPtr<Pattern> pattern;
    richEditorPattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern);
    richEditorPattern->magnifierController_->magnifierNodeExist_ = true;
    richEditorPattern->UpdateMagnifierStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, HandleSurfaceChanged001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->HandleSurfaceChanged(1, 1, 2, 2, WindowSizeChangeReason::DRAG);
    EXPECT_FALSE(richEditorPattern->originIsMenuShow_);
}

/**
 * @tc.name: HandleSurfaceChanged002
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestNg, HandleSurfaceChanged002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    richEditorPattern->HandleSurfaceChanged(0, 0, 0, 0, WindowSizeChangeReason::DRAG);

    EXPECT_EQ(richEditorPattern->magnifierController_->GetShowMagnifier(), false);
}

} // namespace OHOS::Ace::NG
