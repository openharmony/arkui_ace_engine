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
SelectionRangeInfo testSelectionRange(0, 0);
const Dimension IMAGE_WIDTH = 50.0_vp;
const Dimension IMAGE_HEIGHT = 50.0_vp;
const ImageSpanSize TEST_IMAGE_SIZE_1 = { .width = 50.0_vp, .height = 50.0_vp };
} // namespace

class RichEditorControllerTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorControllerTest::SetUp()
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

void RichEditorControllerTest::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorControllerTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorModel010
 * @tc.desc: test set on text/image/symbol selection change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorModel010, TestSize.Level1)
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

    // insert value
    richEditorPattern->InsertValue(INIT_VALUE_1);

    // add image
    ImageSpanOptions imageSpanOptions;
    richEditorPattern->AddImageSpan(imageSpanOptions);
    richEditorPattern->HandleOnSelectAll();
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 7);

    // add symbol
    SymbolSpanOptions symbolSpanOptions;
    symbolSpanOptions.symbolId = SYMBOL_ID;
    auto richEditorController =  richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorController->AddSymbolSpan(symbolSpanOptions);
    richEditorPattern->HandleOnSelectAll();
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 9);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel011
 * @tc.desc: test placeholder appear and disappear
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorModel011, TestSize.Level1)
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

    // test placeholder appear when there is nothing in richEditor
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    auto spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 0);

    // test add Text then placeholder disappear
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_2;
    richEditorController->AddTextSpan(textOptions);
    layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 1);
    EXPECT_EQ(spanItemChildren.back()->GetSpanContent(), INIT_VALUE_2);

    // test when richEitor empty again,placeholder Appear again
    RangeOptions rangeoptions;
    richEditorController->DeleteSpans(rangeoptions);
    richEditorPattern->BeforeCreateLayoutWrapper();
    layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    spanItemChildren = layoutAlgorithm->GetSpans();
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
HWTEST_F(RichEditorControllerTest, RichEditorModel014, TestSize.Level1)
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
HWTEST_F(RichEditorControllerTest, RichEditorModel015, TestSize.Level1)
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
HWTEST_F(RichEditorControllerTest, RichEditorModel016, TestSize.Level1)
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
 * @tc.name: PreventDefault001
 * @tc.desc: test PreventDefault001 in ImageSpan and TextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, PreventDefault001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    // add imageSpan
    ClearSpan();
    ImageSpanOptions imageSpanOptions;
    GestureEventFunc callback2 = [](GestureEvent& info) {
        info.SetPreventDefault(true);
    };
    imageSpanOptions.userGestureOption.onClick = callback2;
    richEditorController->AddImageSpan(imageSpanOptions);

    /**
     * @tc.steps: step1. Click on imagespan
     */
    GestureEvent info2;
    info2.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info2);
    EXPECT_FALSE(richEditorPattern->HasFocus());
}


/**
 * @tc.name: RichEditorController003
 * @tc.desc: test get caret offset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    auto offset1 = richEditorController->GetCaretOffset();
    EXPECT_EQ(offset1, 1);
    richEditorPattern->caretPosition_ = 2;
    auto offset2 = richEditorController->GetCaretOffset();
    EXPECT_EQ(offset2, 2);
}

/**
 * @tc.name: RichEditorController004
 * @tc.desc: test set caret offset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorController->SetCaretOffset(2);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorController->SetCaretOffset(-1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
}

/**
 * @tc.name: RichEditorController005
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetTextShadows(SHADOWS);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateTextShadows = SHADOWS;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE;
    updateSpanStyle.updateItalicFontStyle = ITALIC_FONT_STYLE_VALUE;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT_VALUE;
    updateSpanStyle.updateFontFamily = FONT_FAMILY_VALUE;
    updateSpanStyle.updateTextDecoration = TEXT_DECORATION_VALUE;
    updateSpanStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(5, 10, textStyle, imageStyle);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(1));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan1->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan1->GetTextShadow(), SHADOWS);
    EXPECT_EQ(newSpan1->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan1->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecorationFirst(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
}

/**
 * @tc.name: RichEditorController006
 * @tc.desc: test get span info
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController006, TestSize.Level1)
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

/**
 * @tc.name: RichEditorController007
 * @tc.desc: test delete span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option1;
    option1.start = 5;
    option1.end = 10;
    richEditorController->DeleteSpans(option1);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option2;
    option2.start = 10;
    option2.end = 5;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option3;
    option3.start = -5;
    option3.end = 10;
    richEditorController->DeleteSpans(option3);
    EXPECT_EQ(contentNode->GetChildren().size(), 1);
}

/**
 * @tc.name: RichEditorController010
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController010, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");
    RefPtr<FrameNode> builderNode1 = nullptr;
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 0);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 1);
    ClearSpan();
}

/**
 * @tc.name: RichEditorController012
 * @tc.desc: test update symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_1);
    style.SetRenderStrategy(RENDER_STRATEGY_SINGLE);
    style.SetEffectStrategy(EFFECT_STRATEGY_NONE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);

    /**
     * @tc.steps: step4. update symbol span style
     */
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateSymbolFontSize = FONT_SIZE_VALUE_2;
    updateSpanStyle.updateSymbolFontWeight = FONT_WEIGHT_BOLD;
    updateSpanStyle.updateSymbolColor = SYMBOL_COLOR_LIST_2;
    updateSpanStyle.updateSymbolRenderingStrategy = RENDER_STRATEGY_MULTI_COLOR;
    updateSpanStyle.updateSymbolEffectStrategy = EFFECT_STRATEGY_SCALE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);

    ImageSpanAttribute imageStyle;
    style.SetFontSize(FONT_SIZE_VALUE_2);
    style.SetFontWeight(FONT_WEIGHT_BOLD);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_2);
    style.SetRenderStrategy(RENDER_STRATEGY_MULTI_COLOR);
    style.SetEffectStrategy(EFFECT_STRATEGY_SCALE);

    // update the first symbol span
    richEditorController->UpdateSpanStyle(0, 2, style, imageStyle);

    /**
     * @tc.steps: step5. test symbol span style
     */
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE_2);
    EXPECT_EQ(newSpan1->GetFontWeight(), FONT_WEIGHT_BOLD);
    EXPECT_EQ(newSpan1->GetSymbolColorList(), SYMBOL_COLOR_LIST_2);
    EXPECT_EQ(newSpan1->GetSymbolRenderingStrategy(), RENDER_STRATEGY_MULTI_COLOR);
    EXPECT_EQ(newSpan1->GetSymbolEffectStrategy(), EFFECT_STRATEGY_SCALE);

    auto newSpan2 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(1));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan2->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan2->GetSymbolColorList(), SYMBOL_COLOR_LIST_1);
    EXPECT_EQ(newSpan2->GetSymbolRenderingStrategy(), RENDER_STRATEGY_SINGLE);
    EXPECT_EQ(newSpan2->GetSymbolEffectStrategy(), EFFECT_STRATEGY_NONE);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController013
 * @tc.desc: test get symbol span info
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_1);
    style.SetRenderStrategy(RENDER_STRATEGY_SINGLE);
    style.SetEffectStrategy(EFFECT_STRATEGY_NONE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    auto index3 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index3, 2);
    auto index4 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index4, 3);

    /**
     * @tc.steps: step4. get symbol span info
     */
    auto info1 = richEditorController->GetSpansInfo(2, 5);
    EXPECT_EQ(info1.selection_.selection[0], 2);
    EXPECT_EQ(info1.selection_.selection[1], 5);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 2);

    auto info2 = richEditorController->GetSpansInfo(5, 2);
    EXPECT_EQ(info2.selection_.selection[0], 2);
    EXPECT_EQ(info2.selection_.selection[1], 5);
    EXPECT_EQ(info2.selection_.resultObjects.size(), 2);

    auto info3 = richEditorController->GetSpansInfo(-2, 5);
    EXPECT_EQ(info3.selection_.selection[0], 0);
    EXPECT_EQ(info3.selection_.selection[1], 5);
    EXPECT_EQ(info3.selection_.resultObjects.size(), 3);

    auto info4 = richEditorController->GetSpansInfo(2, -5);
    EXPECT_EQ(info4.selection_.selection[0], 0);
    EXPECT_EQ(info4.selection_.selection[1], 2);
    EXPECT_EQ(info4.selection_.resultObjects.size(), 1);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController014
 * @tc.desc: test delete symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    auto index3 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index3, 2);
    auto index4 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index4, 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    /**
     * @tc.steps: step4. delete single symbol span
     */
    RangeOptions option2;
    option2.start = 0;
    option2.end = 2;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    option2.start = 2;
    option2.end = 0;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    option2.start = -1;
    option2.end = 2;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(contentNode->GetChildren().size(), 1);

    option2.start = 2;
    option2.end = -1;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(contentNode->GetChildren().size(), 0);

    /**
     * @tc.steps: step5. add symbol span
     */
    auto index5 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index5, 0);

    /**
     * @tc.steps: step6. delete symbol span
     */
    option2.start = 0;
    option2.end = 1;
    richEditorController->DeleteSpans(option2); // delete half symbol span, will fail
    EXPECT_EQ(contentNode->GetChildren().size(), 0);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController015
 * @tc.desc: test get caret rect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController015, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto rect1 = richEditorController->GetCaretRect();
    EXPECT_EQ(rect1.GetOffset().GetX(), -1);
    EXPECT_EQ(rect1.GetOffset().GetY(), -1);
    EXPECT_EQ(rect1.Width(), -1);
    EXPECT_EQ(rect1.Height(), -1);
    richEditorPattern->caretTwinkling_ = true;
    auto rect2 = richEditorController->GetCaretRect();
    EXPECT_EQ(rect2.GetOffset().GetX(), 0);
    EXPECT_EQ(rect2.GetOffset().GetY(), 0);
    EXPECT_EQ(rect2.Width(), 0);
    EXPECT_EQ(rect2.Height(), 0);
}

/**
 * @tc.name: RichEditorController017
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. test add span
     */
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 3);

    /**
     * @tc.steps: step3. test update span
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    TextStyle textStyle2;
    textStyle2.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;

    /**
     * @tc.cases: case. call UpdateSpanStyle(), cover branch end < 0
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(0, -1, textStyle, imageStyle);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch end > length
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE_2
     */
    richEditorController->UpdateSpanStyle(0, 20, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE_2);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE, cover branch start > end
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(10, 0, textStyle, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch start == end
     * @tc.expected: expect GetFontSize() is still equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(0, 0, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch start > length
     * @tc.expected: expect GetFontSize() is still equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(20, 30, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);
    ClearSpan();
}

/**
 * @tc.name: RichEditorController018
 * @tc.desc: test delete span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController018, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option4;
    option4.start = 5;
    option4.end = -10;
    richEditorController->DeleteSpans(option4);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option5;
    richEditorController->DeleteSpans(option5);
    EXPECT_TRUE(contentNode->GetChildren().empty());
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    option5.start = 100;
    option5.end = 10;
    richEditorController->DeleteSpans(option5);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    option5.start = 3;
    option5.end = 3;
    richEditorController->DeleteSpans(option5);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);
    ClearSpan();
    richEditorController->DeleteSpans(option5);
}

/**
 * @tc.name: RichEditorController019
 * @tc.desc: test UpdateImageStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. initalize span properties and add image span
     */
    AddImageSpan();
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    /**
     * @tc.steps: step3. test UpdateImageStyle
     */
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateImageWidth = IMAGE_WIDTH;
    updateSpanStyle.updateImageHeight = IMAGE_HEIGHT;
    updateSpanStyle.updateImageFit = ImageFit::CONTAIN;
    updateSpanStyle.updateImageVerticalAlign = VerticalAlign::BOTTOM;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    updateSpanStyle.borderRadius = borderRadius;
    updateSpanStyle.marginProp = marginProp;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);

    ImageSpanAttribute imageStyle;
    imageStyle.size = TEST_IMAGE_SIZE_1;
    imageStyle.verticalAlign = VerticalAlign::BOTTOM;
    imageStyle.objectFit = ImageFit::CONTAIN;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    TextStyle style;
    richEditorController->UpdateSpanStyle(0, 2, style, imageStyle);

    /**
     * @tc.steps: step4. test image span style
     */
    auto host = richEditorPattern->GetContentHost();
    ASSERT_NE(host, nullptr);
    auto child = host->GetChildren().begin();
    auto imageNode = AceType::DynamicCast<FrameNode>(*child);
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->calcLayoutConstraint_->selfIdealSize, TEST_IMAGE_SIZE_1.GetSize());
    EXPECT_EQ(imageLayoutProperty->GetVerticalAlignValue(), VerticalAlign::BOTTOM);
    EXPECT_EQ(imageLayoutProperty->GetImageFitValue(), ImageFit::CONTAIN);
    EXPECT_EQ(imageLayoutProperty->GetMarginProperty()->left->ToString(), CALC_LENGTH_CALC.ToString());

    auto imageRenderCtx = imageNode->GetRenderContext();
    ASSERT_NE(imageRenderCtx, nullptr);
    EXPECT_EQ(imageRenderCtx->GetBorderRadius(), borderRadius);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController021
 * @tc.desc: test AddTextSpan with UpdateParagraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. add span and initalize UpdateParagraphStyle
     */
    AddSpan("test");
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    TextStyle style;
    options.style = style;
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.wordBreak = WordBreak::NORMAL;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.paragraphSpacing = Dimension(10.0f, DimensionUnit::PX);
    options.paraStyle = paragraphStyle;

    /**
     * @tc.steps: step3. set userGestureOption
     */
    GestureEventFunc callback2 = [](GestureEvent& info) {};
    options.userGestureOption.onClick = callback2;

    /**
     * @tc.steps: step4. test AddTextSpan
     */
    auto index = richEditorPattern->AddTextSpan(options, true, 5);
    EXPECT_EQ(index, 5);
    auto info = richEditorController->GetSpansInfo(5, sizeof(INIT_VALUE_1));
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto textStyle = info.selection_.resultObjects.begin()->textStyle;
    EXPECT_EQ(textStyle.wordBreak, int(WordBreak::NORMAL));
    EXPECT_EQ(textStyle.textAlign, int(TextAlign::END));
    EXPECT_NE(textStyle.paragraphSpacing, std::nullopt);
    EXPECT_EQ(textStyle.paragraphSpacing.value().Value(), 10.0f);
}

/**
 * @tc.name: RichEditorController22
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerTest, RichEditorController22, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetTextShadows(SHADOWS);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateTextShadows = SHADOWS;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE;
    updateSpanStyle.updateItalicFontStyle = ITALIC_FONT_STYLE_VALUE;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT_VALUE;
    updateSpanStyle.updateFontFamily = FONT_FAMILY_VALUE;
    updateSpanStyle.updateTextDecoration = TEXT_DECORATION_VALUE;
    updateSpanStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(5, 10, textStyle, imageStyle);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
    auto newSpan2 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(3));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan2->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan2->GetTextShadow(), SHADOWS);
    EXPECT_EQ(newSpan2->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan2->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan2->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecorationFirst(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
}
}