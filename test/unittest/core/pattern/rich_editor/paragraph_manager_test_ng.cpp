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

/**
 * @tc.name: DidExceedMaxLinesInner001
 * @tc.desc: test DidExceedMaxLinesInner
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, DidExceedMaxLinesInner001, TestSize.Level1)
{
    RefPtr<ParagraphManager> pManager_ = AceType::MakeRefPtr<ParagraphManager>();;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, DidExceedMaxLinesInner).WillOnce(Return(true));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    pManager_->AddParagraph(std::move(paragraphInfo));
    EXPECT_TRUE(pManager_->DidExceedMaxLinesInner());
}

/**
 * @tc.name: GetDumpInfo001
 * @tc.desc: test GetDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, GetDumpInfo001, TestSize.Level1)
{
    RefPtr<ParagraphManager> pManager_ = AceType::MakeRefPtr<ParagraphManager>();;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetDumpInfo).WillRepeatedly(Return("test"));

    ParagraphManager::ParagraphInfo paragraphInfo2;
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    paragraphInfo2.paragraph = mockParagraph;
    paragraphInfo2.start = 10;
    paragraphInfo2.end = 20;
    pManager_->AddParagraph(std::move(paragraphInfo));
    pManager_->AddParagraph(std::move(paragraphInfo2));
    EXPECT_EQ(pManager_->GetDumpInfo(), "[test][test]");
}

/**
 * @tc.name: ParagraphManager001
 * @tc.desc: Test the paragraph manager GetHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager002, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager003, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager004, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager005, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager006, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager007, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager008, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager009, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager010, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, ParagraphManager011, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetLineMetrics001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetLineMetrics002, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetGlyphIndexByCoordinate001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetWordBoundary001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetLineMetricsByRectF001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, IsSelectLineHeadAndUseLeadingMargin001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, IsSelectLineHeadAndUseLeadingMargin002, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, IsSelectLineHeadAndUseLeadingMargin003, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetIndex001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetGlyphPositionAtCoordinate001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetParagraphInfo001, TestSize.Level1)
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
HWTEST_F(RichEditorParagraphManagetTestNg, GetParagraphLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::list<RefPtr<UINode>> spans;
    int32_t ret = richEditorPattern->GetParagraphLength(spans);
    ASSERT_EQ(ret, 0);
}

} // namespace OHOS::Ace::NG
