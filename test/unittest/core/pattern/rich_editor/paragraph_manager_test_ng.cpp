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
} // namespace OHOS::Ace::NG
