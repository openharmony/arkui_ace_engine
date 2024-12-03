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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace
class RichEditorPatternTestSixNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestSixNg::SetUp()
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

void RichEditorPatternTestSixNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestSixNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetSelectSpanInfo001
 * @tc.desc: Test GetSelectSpanInfo function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ClickAISpan001, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 100));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_TRUE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}

/**
 * @tc.name: GetSelectSpanInfo001
 * @tc.desc: Test GetSelectSpanInfo function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ClickAISpan002, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 100));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->leftMousePress_ = true;
    EXPECT_TRUE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}

/**
 * @tc.name: GetSelectSpanInfo001
 * @tc.desc: Test GetSelectSpanInfo function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ClickAISpan003, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->leftMousePress_ = true;
    EXPECT_FALSE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}

/**
 * @tc.name: GetSelectSpanInfo001
 * @tc.desc: Test GetSelectSpanInfo function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ClickAISpan004, TestSize.Level1)
{
    PointF textOffset = {100.0, 100.0};
    AISpan aiSpan = {0, 10, "Test", TextDataDetectType::PHONE_NUMBER};
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 3;
    info.end = 10;
    EXPECT_CALL(*mockParagraph, GetHeight())
        .WillRepeatedly(Return(10.0f));
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->leftMousePress_ = false;
    EXPECT_FALSE(richEditorPattern->ClickAISpan(textOffset, aiSpan));
}
} // namespace OHOS::Ace::NG