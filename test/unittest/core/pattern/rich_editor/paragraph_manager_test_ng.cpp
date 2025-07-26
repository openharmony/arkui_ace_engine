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

using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorParagraphManagetTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorParagraphManagetTestNg::SetUp()
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

void RichEditorParagraphManagetTestNg::TearDown()
{
    richEditorNode_.Reset();
    MockParagraph::TearDown();
}

void RichEditorParagraphManagetTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetParagraphsRects001
 * @tc.desc: test GetParagraphsRects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetParagraphsRects001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    info.start = 3;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, TextDirection>> result =
        richEditorPattern->paragraphs_.GetParagraphsRects(1, 2);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: GetParagraphsRects002
 * @tc.desc: test GetParagraphsRects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetParagraphsRects002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, TextDirection>> result =
        richEditorPattern->paragraphs_.GetParagraphsRects(1, 2);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetParagraphsRects003
 * @tc.desc: test GetParagraphsRects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetParagraphsRects003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, TextDirection>> result =
        richEditorPattern->paragraphs_.GetParagraphsRects(1, 2, RectHeightPolicy::COVER_TEXT);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetParagraphsRects004
 * @tc.desc: test GetParagraphsRects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetParagraphsRects004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, TextDirection>> result =
        richEditorPattern->paragraphs_.GetParagraphsRects(1, 2, RectHeightPolicy::COVER_TEXT);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: GetTextBoxesForSelect001
 * @tc.desc: test GetTextBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxesForSelect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetTextBoxesForSelect(1, 2);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: GetTextBoxesForSelect002
 * @tc.desc: test GetTextBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxesForSelect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetTextBoxesForSelect(1, 2, RectHeightPolicy::COVER_TEXT);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetTextBoxesForSelect003
 * @tc.desc: test GetTextBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxesForSelect003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetTextBoxesForSelect(1, 2);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetTextBoxesForSelect004
 * @tc.desc: test GetTextBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxesForSelect004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetTextBoxesForSelect(1, 2);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: MakeBlankLineRectsInParagraph001
 * @tc.desc: test MakeBlankLineRectsInParagraph
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankLineRectsInParagraph001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    selectData.secondResult = true;
    RectF rectF;
    std::vector<RectF> rects;
    rects.push_back(rectF);
    richEditorPattern->paragraphs_.MakeBlankLineRectsInParagraph(rects, info, selectData);
    EXPECT_EQ(rects.size(), 0);
}

/**
 * @tc.name: MakeBlankLineRectsInParagraph002
 * @tc.desc: test MakeBlankLineRectsInParagraph
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankLineRectsInParagraph002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    selectData.relativeEnd = 1;
    RectF rectF;
    std::vector<RectF> rects;
    rects.push_back(rectF);
    richEditorPattern->paragraphs_.MakeBlankLineRectsInParagraph(rects, info, selectData);
    EXPECT_EQ(rects.size(), 1);
}

/**
 * @tc.name: MakeBlankLineRectsInParagraph003
 * @tc.desc: test MakeBlankLineRectsInParagraph
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankLineRectsInParagraph003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    std::vector<RectF> rects;
    richEditorPattern->paragraphs_.MakeBlankLineRectsInParagraph(rects, info, selectData);
    EXPECT_EQ(rects.size(), 0);
}

/**
 * @tc.name: MakeBlankLineRectsInParagraph004
 * @tc.desc: test MakeBlankLineRectsInParagraph
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankLineRectsInParagraph004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    RectF rectF;
    std::vector<RectF> rects;
    rects.push_back(rectF);
    richEditorPattern->paragraphs_.MakeBlankLineRectsInParagraph(rects, info, selectData);
    EXPECT_EQ(rects.size(), 1);
}

/**
 * @tc.name: GetRichEditorBoxesForSelect001
 * @tc.desc: test GetRichEditorBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetRichEditorBoxesForSelect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetRichEditorBoxesForSelect(1, 2);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: GetRichEditorBoxesForSelect002
 * @tc.desc: test GetRichEditorBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetRichEditorBoxesForSelect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetRichEditorBoxesForSelect(1, 2, RectHeightPolicy::COVER_TEXT);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetRichEditorBoxesForSelect003
 * @tc.desc: test GetRichEditorBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetRichEditorBoxesForSelect003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetRichEditorBoxesForSelect(1, 2);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetRichEditorBoxesForSelect004
 * @tc.desc: test GetRichEditorBoxesForSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetRichEditorBoxesForSelect004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> result =
        richEditorPattern->paragraphs_.GetRichEditorBoxesForSelect(1, 2);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: MakeBlankRectsInRichEditor001
 * @tc.desc: test MakeBlankRectsInRichEditor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankRectsInRichEditor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    selectData.secondResult = true;
    RectF rectF;
    std::vector<RectF> rects;
    rects.push_back(rectF);
    richEditorPattern->paragraphs_.MakeBlankRectsInRichEditor(rects, info, selectData);
    EXPECT_EQ(rects.size(), 0);
}

/**
 * @tc.name: MakeBlankRectsInRichEditor002
 * @tc.desc: test MakeBlankRectsInRichEditor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankRectsInRichEditor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    selectData.relativeEnd = 1;
    RectF rectF;
    std::vector<RectF> rects;
    rects.push_back(rectF);
    richEditorPattern->paragraphs_.MakeBlankRectsInRichEditor(rects, info, selectData);
    EXPECT_EQ(rects.size(), 1);
}

/**
 * @tc.name: MakeBlankRectsInRichEditor003
 * @tc.desc: test MakeBlankRectsInRichEditor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankRectsInRichEditor003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    std::vector<RectF> rects;
    richEditorPattern->paragraphs_.MakeBlankRectsInRichEditor(rects, info, selectData);
    EXPECT_EQ(rects.size(), 0);
}

/**
 * @tc.name: MakeBlankRectsInRichEditor004
 * @tc.desc: test MakeBlankRectsInRichEditor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, MakeBlankRectsInRichEditor004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    ParagraphManager::SelectData selectData;
    RectF rectF;
    std::vector<RectF> rects;
    rects.push_back(rectF);
    richEditorPattern->paragraphs_.MakeBlankRectsInRichEditor(rects, info, selectData);
    EXPECT_EQ(rects.size(), 1);
}

/**
 * @tc.name: RemoveBlankLineRectByHandler001
 * @tc.desc: test RemoveBlankLineRectByHandler
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, RemoveBlankLineRectByHandler001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::SelectData selectData;
    std::vector<RectF> rects;
    richEditorPattern->paragraphs_.RemoveBlankLineRectByHandler(rects, selectData);
    EXPECT_EQ(rects.size(), 0);
}

/**
 * @tc.name: RemoveBlankLineRectByHandler002
 * @tc.desc: test RemoveBlankLineRectByHandler
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, RemoveBlankLineRectByHandler002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ParagraphManager::SelectData selectData;
    RectF rectF;
    std::vector<RectF> rects;
    rects.push_back(rectF);
    richEditorPattern->paragraphs_.RemoveBlankLineRectByHandler(rects, selectData);
    EXPECT_EQ(rects.size(), 1);
}

/**
 * @tc.name: GetTextBoxes001
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 3;

    std::vector<RectF> res;
    auto ret = richEditorPattern->GetTextBoxes();
    EXPECT_EQ(ret, res);


    TextLineMetrics lineMetrics;
    richEditorPattern->GetLineCount();
    EXPECT_EQ(richEditorPattern->GetLineHeight(), 0.0f);
    EXPECT_EQ(richEditorPattern->GetLetterSpacing(), 0.0f);
    auto retLineMetrics = richEditorPattern->GetLineMetrics(-1);
    EXPECT_EQ(retLineMetrics.x, 0);

    auto retLineMetricsS = richEditorPattern->GetLineMetrics(2);
    EXPECT_EQ(retLineMetricsS.x, 0);

    int32_t scroll_from_update = 1;
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 1, 100, 160);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update)) << "Reach Top Boundary";

    EXPECT_EQ(richEditorPattern->MoveTextRect(0.0f), 0.0f);

    auto offsetF = OffsetF(0.0f, 0.5f);
    richEditorPattern->MoveCaretToContentRect(offsetF, 8.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    richEditorPattern->MoveCaretToContentRect(1.0f, 10);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    richEditorPattern->contentChange_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
}

/**
 * @tc.name: GetTextBoxes002
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 3;

    std::vector<RectF> res;
    auto ret = richEditorPattern->GetTextBoxes();
    EXPECT_EQ(ret, res);

    TextLineMetrics lineMetrics;
    richEditorPattern->GetLineCount();
    EXPECT_EQ(richEditorPattern->GetLineHeight(), 0.0f);
    EXPECT_EQ(richEditorPattern->GetLetterSpacing(), 0.0f);
    auto retLineMetrics = richEditorPattern->GetLineMetrics(-1);
    EXPECT_EQ(retLineMetrics.x, 0);

    auto retLineMetricsS = richEditorPattern->GetLineMetrics(2);
    EXPECT_EQ(retLineMetricsS.x, 0);

    int32_t scroll_from_update = 1;
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 1, 100, 160);
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update)) << "Reach Top Boundary";
}

/**
 * @tc.name: GetTextBoxes003
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxes003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;

    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([&](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    const OHOS::Ace::NG::ParagraphStyle expectedStyle;
    LeadingMargin leadingMarginOne;
    EXPECT_CALL(*mockParagraph, GetParagraphStyle()).WillRepeatedly(ReturnRef(expectedStyle));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.paragraphStyle = expectedStyle;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->paragraphs_.AddParagraph(std::move(paragraphInfo));
    auto textBoxes = richEditorPattern->GetTextBoxes();
    EXPECT_NE(textBoxes.size(), 0);
}

/**
 * @tc.name: GetTextBoxes004
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetTextBoxes004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;

    ParagraphStyle paragraphStyle = {};
    paragraphStyle.leadingMargin = LeadingMargin();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfoOne;
    RefPtr<MockParagraph> mockParagraphOne = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraphOne, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([&](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    LeadingMargin leadingMarginOne;
    EXPECT_CALL(*mockParagraphOne, GetParagraphStyle()).WillRepeatedly(ReturnRef(paragraphStyle));
    paragraphInfoOne.paragraph = mockParagraphOne;
    paragraphInfoOne.paragraphStyle = paragraphStyle;
    paragraphInfoOne.start = 0;
    paragraphInfoOne.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfoOne);
    richEditorPattern->paragraphs_.AddParagraph(std::move(paragraphInfoOne));
    auto textBoxes = richEditorPattern->GetTextBoxes();
    EXPECT_NE(textBoxes.size(), 0);
}

} // namespace OHOS::Ace::NG
