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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorParagraphMgrTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorParagraphMgrTestNg::SetUp()
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

void RichEditorParagraphMgrTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorParagraphMgrTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: ParagraphManager001
 * @tc.desc: Test the paragraph manager GetHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial height
     */
    auto height = richEditorPattern->paragraphs_.GetHeight();
    EXPECT_EQ(height, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get height
     */
    height = richEditorPattern->paragraphs_.GetHeight();
    EXPECT_EQ(height, 0.0f);
}

/**
 * @tc.name: ParagraphManager002
 * @tc.desc: Test the paragraph manager GetMaxIntrinsicWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max intrinsic width
     */
    double maxIntrinsicWidth = richEditorPattern->paragraphs_.GetMaxIntrinsicWidth();
    EXPECT_EQ(maxIntrinsicWidth, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get maxIntrinsicWidth
     */
    maxIntrinsicWidth = richEditorPattern->paragraphs_.GetMaxIntrinsicWidth();
    EXPECT_EQ(maxIntrinsicWidth, 0.0f);
}

/**
 * @tc.name: ParagraphManager003
 * @tc.desc: Test the paragraph manager DidExceedMaxLines function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial exceed max lines
     */
    bool didExceedMaxLines = richEditorPattern->paragraphs_.DidExceedMaxLines();
    EXPECT_EQ(didExceedMaxLines, false);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test didExceedMaxLines
     */
    didExceedMaxLines = richEditorPattern->paragraphs_.DidExceedMaxLines();
    EXPECT_EQ(didExceedMaxLines, false);
}

/**
 * @tc.name: ParagraphManager004
 * @tc.desc: Test the paragraph manager GetLongestLine function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max intrinsic width
     */
    double longestLine = richEditorPattern->paragraphs_.GetLongestLine();
    EXPECT_EQ(longestLine, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get longest line
     */
    longestLine = richEditorPattern->paragraphs_.GetLongestLine();
    EXPECT_EQ(longestLine, 0.0f);
}

/**
 * @tc.name: ParagraphManager005
 * @tc.desc: Test the paragraph manager GetMaxWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max width
     */
    double maxWidth = richEditorPattern->paragraphs_.GetMaxWidth();
    EXPECT_EQ(maxWidth, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get max width
     */
    maxWidth = richEditorPattern->paragraphs_.GetMaxWidth();
    EXPECT_EQ(maxWidth, 0.0f);
}

/**
 * @tc.name: ParagraphManager006
 * @tc.desc: Test the paragraph manager GetTextWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max width
     */
    double maxTextWidth = richEditorPattern->paragraphs_.GetTextWidth();
    EXPECT_EQ(maxTextWidth, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get text width
     */
    maxTextWidth = richEditorPattern->paragraphs_.GetTextWidth();
    EXPECT_EQ(maxTextWidth, 0.0f);
}

/**
 * @tc.name: ParagraphManager007
 * @tc.desc: Test the paragraph manager GetTextWidthIncludeIndent function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial text width include indent
     */
    double textWidthIncludeIndent = richEditorPattern->paragraphs_.GetTextWidthIncludeIndent();
    EXPECT_EQ(textWidthIncludeIndent, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get text width include indent
     */
    textWidthIncludeIndent = richEditorPattern->paragraphs_.GetTextWidthIncludeIndent();
    EXPECT_EQ(textWidthIncludeIndent, 0.0f);
}

/**
 * @tc.name: ParagraphManager008
 * @tc.desc: Test the paragraph manager GetLineCount function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial line count
     */
    size_t dineCount = richEditorPattern->paragraphs_.GetLineCount();
    EXPECT_EQ(dineCount, 0);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get line count
     */
    dineCount = richEditorPattern->paragraphs_.GetLineCount();
    EXPECT_EQ(dineCount, 0);
}

/**
 * @tc.name: ParagraphManager009
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager009, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step2. test get index
     */
    auto textRect = richEditorPattern->GetTextRect();
    textRect.SetTop(textRect.GetY() - 0.0f);
    textRect.SetHeight(textRect.Height() - 0.0f);
    Offset offset = Offset(textRect.GetX(), textRect.GetY());
    bool clamp = false;
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(offset, clamp);
    EXPECT_EQ(paragraphsIndex, 0);

    /**
     * @tc.steps: step3. test get glyph index
     */
    int32_t glyphIndex = richEditorPattern->paragraphs_.GetGlyphIndexByCoordinate(offset, clamp);
    EXPECT_EQ(glyphIndex, 0);

    /**
     * @tc.steps: step4. test get word boundary
     */
    int32_t offset1 = 0;
    int32_t start = 0;
    int32_t end = 0;
    bool wordBoundary = richEditorPattern->paragraphs_.GetWordBoundary(offset1, start, end);
    EXPECT_EQ(wordBoundary, false);

    /**
     * @tc.steps: step5. test calc caret metrics
     */
    int32_t extent = 0;
    CaretMetricsF caretCaretMetric;
    TextAffinity textAffinity = TextAffinity::DOWNSTREAM;
    bool caretMetrics = richEditorPattern->paragraphs_.CalcCaretMetricsByPosition(extent, caretCaretMetric,
        textAffinity);
    EXPECT_EQ(caretMetrics, false);
}

/**
 * @tc.name: ParagraphManager010
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager010, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step2. test get line metrics
     */
    RectF rect = { 0.0, 0.0, 100.0, 100.0 };
    int32_t paragraphIndex = 0;
    LineMetrics lineMetrics = richEditorPattern->paragraphs_.GetLineMetricsByRectF(rect, paragraphIndex);
    EXPECT_EQ(lineMetrics.ascender, 0.0f);

    /**
     * @tc.steps: step3. test editable status
     */
    auto accessibilityProperty = richEditorPattern->CreateAccessibilityProperty();
    bool isEditable = accessibilityProperty->IsEditable();
    EXPECT_EQ(isEditable, true);
}

/**
 * @tc.name: ParagraphManager011
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, ParagraphManager011, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    bool clamp = true;
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(-1.0, -1.0), clamp);
    EXPECT_EQ(paragraphsIndex, 0);

    PositionWithAffinity finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(-1.0, -1.0));
    EXPECT_EQ(finalResult.position_, 0);
}

/**
 * @tc.name: GetLineMetrics001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetLineMetrics001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    TextLineMetrics textLineMetrics;
    textLineMetrics.lineNumber = 0;
    EXPECT_CALL(*paragraph, GetLineMetrics(_)).WillRepeatedly(Return(textLineMetrics));

    TextLineMetrics finalResult = richEditorPattern->paragraphs_.GetLineMetrics(0);
    EXPECT_EQ(finalResult.lineNumber, 0);

    finalResult = richEditorPattern->paragraphs_.GetLineMetrics(2);
    EXPECT_EQ(finalResult.lineNumber, 0);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 600.0, 600.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);
    finalResult = richEditorPattern->paragraphs_.GetLineMetrics(1);
    EXPECT_EQ(finalResult.lineNumber, 1);
}

/**
 * @tc.name: GetLineMetrics002
 * @tc.desc: test GetLineMetrics
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetLineMetrics002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t lineNumber = 3;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(3));
    richEditorPattern->spans_.push_back(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 2 });
    richEditorPattern->richTextRect_.SetRect(1, 1, 1, 1);
    auto lineMetrics1 = richEditorPattern->paragraphs_.GetLineMetrics(lineNumber);
    auto ret1 = richEditorPattern->GetLineMetrics(lineNumber);
    EXPECT_EQ(lineMetrics1.x, ret1.x);

    lineNumber = 1;
    richEditorPattern->richTextRect_.SetRect(1, 1, 1, 1);
    auto lineMetrics2 = richEditorPattern->paragraphs_.GetLineMetrics(lineNumber);
    auto ret2 = richEditorPattern->GetLineMetrics(lineNumber);
    EXPECT_NE(lineMetrics2.x, ret2.x);
}

/**
 * @tc.name: GetGlyphIndexByCoordinate001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetGlyphIndexByCoordinate001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(4));
    /**
     * @tc.steps: step2. test get glyph index
     */
    int32_t glyphIndex = richEditorPattern->paragraphs_.GetGlyphIndexByCoordinate(Offset(0.0, 1000.00), true);
    EXPECT_EQ(glyphIndex, 4);
}

/**
 * @tc.name: GetWordBoundary001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetWordBoundary001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step2. test get glyph index
     */
    int32_t glyphIndex = richEditorPattern->paragraphs_.GetWordBoundary(1000, paragraphItem.start, paragraphItem.end);
    EXPECT_EQ(glyphIndex, 0);
}

/**
 * @tc.name: GetLineMetricsByRectF001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetLineMetricsByRectF001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItemSec);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));

    /**
     * @tc.steps: step2. test get glyph index
     */
    LineMetrics testMetrics = richEditorPattern->paragraphs_.GetLineMetricsByRectF(RectF(0.0, 100.0, 200.0, 300.0), 1);
    EXPECT_EQ(testMetrics.y, 800);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin001
 * @tc.desc: Test the paragraph manager IsSelectLineHeadAndUseLeadingMargin function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, IsSelectLineHeadAndUseLeadingMargin001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add paragraph and Mock func.
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ParagraphStyle testStyle = {};
    EXPECT_CALL(*paragraph, GetParagraphStyle())
        .WillRepeatedly(ReturnRef(testStyle));
    /**
     * @tc.steps: step2. test IsSelectLineHeadAndUseLeadingMargin fun
    */
    bool bRet = richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(paragraphItem.start);
    EXPECT_EQ(bRet, false);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin002
 * @tc.desc: Test the paragraph manager IsSelectLineHeadAndUseLeadingMargin function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, IsSelectLineHeadAndUseLeadingMargin002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add paragraph and Mock func.
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ParagraphStyle testStyle = {};
    testStyle.leadingMargin = LeadingMargin();
    EXPECT_CALL(*paragraph, GetParagraphStyle())
        .WillRepeatedly(ReturnRef(testStyle));
    /**
     * @tc.steps: step2. test IsSelectLineHeadAndUseLeadingMargin fun
    */
    int start = richEditorPattern->paragraphs_.paragraphs_.begin()->start;
    bool bRet = richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(start);
    EXPECT_EQ(bRet, false);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin003
 * @tc.desc: Test the paragraph manager IsSelectLineHeadAndUseLeadingMargin function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, IsSelectLineHeadAndUseLeadingMargin003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add paragraph and Mock func.
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ParagraphStyle testStyle = {};
    testStyle.leadingMargin = LeadingMargin();
    EXPECT_CALL(*paragraph, GetParagraphStyle())
        .WillRepeatedly(ReturnRef(testStyle));
    /**
     * @tc.steps: step2. test IsSelectLineHeadAndUseLeadingMargin fun
    */
    bool bRet = richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(paragraphRect.end);
    EXPECT_EQ(bRet, false);
}

/**
 * @tc.name: GetIndex001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
    PositionWithAffinity positionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));

    bool clamp = true;
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, -10.0), clamp);
    EXPECT_EQ(paragraphsIndex, 0);
    paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, 0.0), clamp);
    EXPECT_EQ(paragraphsIndex, 6);
    clamp = false;
    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 600.0, 600.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);
    paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, 900.0), clamp);
    EXPECT_EQ(paragraphsIndex, 13);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetGlyphPositionAtCoordinate001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
    PositionWithAffinity positionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, 0.0), false);
    EXPECT_EQ(paragraphsIndex, 6);

    PositionWithAffinity finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(0.0, 0.0));
    EXPECT_EQ(finalResult.position_, 2);
    finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(0.0, -10.0));
    EXPECT_EQ(finalResult.position_, 0);
    finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(0.0, 900.0));
    EXPECT_EQ(finalResult.position_, 2);
}

/**
 * @tc.name: GetParagraphInfo001
 * @tc.desc: test GetParagraphInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetParagraphInfo001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 24;
    ClearSpan();
    auto size = richEditorPattern->GetParagraphInfo(start, end).size();
    AddSpan(INIT_VALUE_2);
    AddSpan(INIT_VALUE_2 + u"\n");
    AddSpan(INIT_VALUE_2);
    AddSpan(INIT_VALUE_2);
    EXPECT_NE(size, richEditorPattern->GetParagraphInfo(start, end).size());
}

/**
 * @tc.name: GetParagraphLength001
 * @tc.desc: test RichEditorPattern GetParagraphLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphMgrTestNg, GetParagraphLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::list<RefPtr<UINode>> spans;
    int32_t ret = richEditorPattern->GetParagraphLength(spans);
    ASSERT_EQ(ret, 0);
}

} // namespace OHOS::Ace::NG
