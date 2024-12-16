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
#include "test/mock/core/common/mock_data_url_analyzer_mgr.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace
class RichEditorPatternTestSixNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    void InitDataUrlAnalyzer(MockDataUrlAnalyzerMgr& mockDataUrlAnalyzerMgr);
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

void RichEditorPatternTestSixNg::InitDataUrlAnalyzer(MockDataUrlAnalyzerMgr& mockDataUrlAnalyzerMgr)
{
    EXPECT_CALL(mockDataUrlAnalyzerMgr, AnalyzeUrls(_))
        .WillRepeatedly([](const std::string& text) -> std::vector<UrlEntity> {
            std::vector<UrlEntity> data;
            if (text.empty()) {
                return data;
            }
            UrlEntity urlEntity;
            urlEntity.text = text;
            urlEntity.charOffset = text.length();
            data.push_back(urlEntity);
            return data;
        });
}

/*
 * @tc.name: AnalyzeUrls001
 * @tc.desc: test url Analyzer
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, AnalyzeUrls001, TestSize.Level1)
{
    MockDataUrlAnalyzerMgr mockDataUrlAnalyzerMgr;
    InitDataUrlAnalyzer(mockDataUrlAnalyzerMgr);

    std::string text = "";
    std::vector<UrlEntity> data = mockDataUrlAnalyzerMgr.AnalyzeUrls(text);
    EXPECT_TRUE(data.empty());

    text = "test1";
    data = mockDataUrlAnalyzerMgr.AnalyzeUrls(text);
    EXPECT_FALSE(data.empty());
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

/**
 * @tc.name: GetThumbnailCallback002
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetThumbnailCallback002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    const OHOS::Ace::NG::ParagraphStyle expectedStyle;
    EXPECT_CALL(*mockParagraph, GetParagraphStyle()).WillRepeatedly(ReturnRef(expectedStyle));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = PREVIEW_TEXT_U16VALUE2;
    richEditorPattern->spans_.push_back(spanItem);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto newAddFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newAddFrameNode);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_U16VALUE_3);
    auto thumbnailCallback = richEditorPattern->GetThumbnailCallback();
    Offset point(10, 10);
    thumbnailCallback(point);
    EXPECT_FALSE(richEditorPattern->dragNode_->isLayoutDirtyMarked_);
}

/**
 * @tc.name: GetThumbnailCallback003
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetThumbnailCallback003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    richEditorNode_->GetPattern<TextPattern>()->placeholderIndex_.push_back(1);
    richEditorNode_->GetPattern<TextPattern>()->placeholderIndex_.push_back(2);
    richEditorNode_->GetPattern<TextPattern>()->placeholderIndex_.push_back(3);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    const OHOS::Ace::NG::ParagraphStyle expectedStyle;
    EXPECT_CALL(*mockParagraph, GetParagraphStyle()).WillRepeatedly(ReturnRef(expectedStyle));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = PREVIEW_TEXT_U16VALUE2;
    richEditorPattern->spans_.push_back(spanItem);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto newAddFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::PLACEHOLDER_SPAN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newAddFrameNode);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_U16VALUE_3);
    richEditorPattern->selectOverlay_->hostTextBase_.Reset();
    auto thumbnailCallback = richEditorPattern->GetThumbnailCallback();
    Offset point(10, 10);
    thumbnailCallback(point);
    EXPECT_FALSE(richEditorPattern->dragNode_->isLayoutDirtyMarked_);
}
} // namespace OHOS::Ace::NG