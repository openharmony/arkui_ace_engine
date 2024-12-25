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

/**
 * @tc.name: InsertValueInStyledString001
 * @tc.desc: test InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, InsertValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_U16VALUE_3);
    richEditorPattern->InsertValueInStyledString(PREVIEW_TEXT_VALUE1);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: DeleteValueInStyledString001
 * @tc.desc: test DeleteValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, DeleteValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_U16VALUE_3);
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->DeleteValueInStyledString(0, 10, true, false);
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, OnModifyDone001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->clipboard_ = nullptr;
    richEditorPattern->OnModifyDone();
    EXPECT_TRUE(richEditorPattern->clipboard_);
}

/**
 * @tc.name: SetSelfAndChildDraggableFalse001
 * @tc.desc: test SetSelfAndChildDraggableFalse
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, SetSelfAndChildDraggableFalse001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t nodeId = 2;
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    RefPtr<FrameNode> customNode = AceType::MakeRefPtr<FrameNode>(V2::IMAGE_ETS_TAG, nodeId, pattern, false, false);
    auto eventHub = customNode->GetEventHub<EventHub>();
    RefPtr<EventHub> sharedEventHub = RefPtr<EventHub>(new EventHub());
    WeakPtr<EventHub> weakEventHub(sharedEventHub);
    eventHub->gestureEventHub_ = AceType::MakeRefPtr<GestureEventHub>(weakEventHub);
    eventHub->gestureEventHub_->isDragForbiddenForWholeSubTree_ = false;
    richEditorPattern->SetSelfAndChildDraggableFalse(customNode);
    EXPECT_TRUE(eventHub->gestureEventHub_->isDragForbiddenForWholeSubTree_);
}

/**
 * @tc.name: AfterContentChange001
 * @tc.desc: test AfterContentChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, AfterContentChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_.Reset();
    RichEditorChangeValue changeValue;
    richEditorPattern->AfterContentChange(changeValue);
    EXPECT_EQ(richEditorNode_, nullptr);
}

/**
 * @tc.name: DeleteSpans001
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, DeleteSpans001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RangeOptions options;
    options.start = 0;
    options.end = 1;
    richEditorPattern->isSpanStringMode_ = true;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_U16VALUE_3);
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    eventHub->SetOnWillChange([](const RichEditorChangeValue& value) -> bool { return false; });
    richEditorPattern->redoOperationRecords_.emplace_back();
    richEditorPattern->DeleteSpans(options);
    EXPECT_FALSE(richEditorPattern->redoOperationRecords_.empty());
}

/**
 * @tc.name: DeleteSpansOperation001
 * @tc.desc: test DeleteSpansOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, DeleteSpansOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = ImageSpanNode::GetOrCreateSpanNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorPattern->DeleteSpansOperation(0, 5);
    EXPECT_EQ(richEditorPattern->textForDisplay_.size(), 0);
}

/**
 * @tc.name: RemoveEmptySpanNodes001
 * @tc.desc: test RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, RemoveEmptySpanNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = ImageSpanNode::GetOrCreateSpanNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto newAddFrameNode = ImageSpanNode::GetOrCreateSpanNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newAddFrameNode);
    richEditorPattern->RemoveEmptySpanNodes();
    bool nonSpanNodeStillExists = false;
    for (const auto& child : richEditorNode_->children_) {
        if (child == newFrameNode) {
            nonSpanNodeStillExists = true;
            break;
        }
    }
    EXPECT_TRUE(nonSpanNodeStillExists);
}

/**
 * @tc.name: RemoveEmptySpanNodes002
 * @tc.desc: test RemoveEmptySpanNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, RemoveEmptySpanNodes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = SpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, nodeId);
    auto newAddFrameNode = SpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, nodeId);
    newAddFrameNode->GetSpanItem()->content = INIT_U16VALUE_3;
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newAddFrameNode);
    richEditorPattern->RemoveEmptySpanNodes();
    bool emptySpanNodeRemoved = true;
    for (const auto& child : richEditorNode_->children_) {
        auto spanNode = AceType::DynamicCast<SpanNode>(child);
        if (spanNode && spanNode->GetSpanItem()->content.empty()) {
            emptySpanNodeRemoved = false;
            break;
        }
    }
    EXPECT_TRUE(emptySpanNodeRemoved);
}

/**
 * @tc.name: ClearContent001
 * @tc.desc: test ClearContent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ClearContent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto child = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorPattern->ClearContent(child);
    EXPECT_EQ(child->spanItem_->content, u"");
}

/**
 * @tc.name: HandleSingleClickEvent002
 * @tc.desc: test RichEditorPattern HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleSingleClickEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info = GestureEvent();
    richEditorNode_->eventHub_->focusHub_->focusType_ = FocusType::DISABLE;
    richEditorPattern->caretVisible_ = false;
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: HandleSingleClickEvent003
 * @tc.desc: test RichEditorPattern HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleSingleClickEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info = GestureEvent();
    richEditorNode_.Reset();
    richEditorPattern->caretVisible_ = false;
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: HandleUserLongPressEvent001
 * @tc.desc: test HandleUserLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleUserLongPressEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto gestureEventFunc = [](GestureEvent& info) { return true; };
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->onLongPress = std::move(gestureEventFunc);
    richEditorPattern->spans_.push_back(spanItem);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserLongPressEvent(info);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleUserLongPressEvent002
 * @tc.desc: test HandleUserLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleUserLongPressEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserLongPressEvent(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleUserLongPressEvent003
 * @tc.desc: test HandleUserLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleUserLongPressEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserLongPressEvent(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleUserClickEvent001
 * @tc.desc: test HandleUserClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleUserClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto gestureEventFunc = [](GestureEvent& info) { return true; };
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->onClick = std::move(gestureEventFunc);
    richEditorPattern->spans_.push_back(spanItem);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserClickEvent(info);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleUserClickEvent002
 * @tc.desc: test HandleUserClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleUserClickEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserClickEvent(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleUserClickEvent003
 * @tc.desc: test HandleUserClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleUserClickEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserClickEvent(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ProcessInsertValue001
 * @tc.desc: test ProcessInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ProcessInsertValue001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string insertValue = "abc";
    richEditorPattern->isEditing_ = true;
    richEditorPattern->isSpanStringMode_ = false;
    auto size = richEditorPattern->operationRecords_.size();
    richEditorPattern->ProcessInsertValue(insertValue, OperationType::IME, true);
    EXPECT_TRUE(richEditorPattern->IsEditing());
    EXPECT_NE(size, richEditorPattern->operationRecords_.size());
}

/**
 * @tc.name: AddPlaceholderSpan001
 * @tc.desc: test AddPlaceholderSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, AddPlaceholderSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto builderNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    SpanOptionBase options = {};
    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    AddSpan("test");
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem);
    richEditorPattern->spans_.emplace_back(spanItem);
    richEditorPattern->spans_.emplace_back(spanItem);
    auto ret = richEditorPattern->AddPlaceholderSpan(builderNode, {});
    EXPECT_NE(ret, host->GetChildren().size());
}

/**
 * @tc.name: HandleDraggableFlag001
 * @tc.desc: test HandleDraggableFlag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleDraggableFlag001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHubRefPtr = AceType::MakeRefPtr<EventHub>();
    auto eventHubWeakPtr = AceType::WeakClaim(AceType::RawPtr(eventHubRefPtr));
    richEditorNode_->eventHub_->gestureEventHub_ = AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorNode_->eventHub_->gestureEventHub_->isTextDraggable_ = true;
    richEditorPattern->HandleDraggableFlag(true);
    EXPECT_FALSE(richEditorNode_->eventHub_->gestureEventHub_->isTextDraggable_);
}

/**
 * @tc.name: OnDragEnd001
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, OnDragEnd001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool isTestAddObject = false;
    ResultObject resultObject;
    if (richEditorPattern->recoverDragResultObjects_.empty()) {
        isTestAddObject = true;
        richEditorPattern->recoverDragResultObjects_.emplace_back(resultObject);
    }

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->showSelect_ = false;
    richEditorNode_.Reset();
    richEditorPattern->OnDragEnd(event);
    EXPECT_FALSE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: OnDragEnd002
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, OnDragEnd002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool isTestAddObject = false;
    ResultObject resultObject;
    if (richEditorPattern->recoverDragResultObjects_.empty()) {
        isTestAddObject = true;
        richEditorPattern->recoverDragResultObjects_.emplace_back(resultObject);
    }

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->showSelect_ = false;
    event->dragRet_ = DragRet::DRAG_SUCCESS;
    richEditorPattern->OnDragEnd(event);
    EXPECT_FALSE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: OnDragEnd003
 * @tc.desc: test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, OnDragEnd003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool isTestAddObject = false;
    ResultObject resultObject;
    if (richEditorPattern->recoverDragResultObjects_.empty()) {
        isTestAddObject = true;
        richEditorPattern->recoverDragResultObjects_.emplace_back(resultObject);
    }

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->showSelect_ = false;
    richEditorNode_->eventHub_->focusHub_->focusType_ = FocusType::DISABLE;
    richEditorPattern->OnDragEnd(event);
    EXPECT_FALSE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: GetImageStyleBySpanItem002
 * @tc.desc: test GetImageStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetImageStyleBySpanItem002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ImageSpanAttribute imageStyle;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    ImageSpanSize imageSize;
    imageSize.height = 1;
    imageStyle.size = imageSize;
    imageStyle.verticalAlign = VerticalAlign::TOP;
    imageStyle.objectFit = ImageFit::COVER;

    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanOptions option;
    option.imageAttribute = imageStyle;
    spanItem->options = option;
    auto imageSizeOp = spanItem->options.imageAttribute->size;
    auto ret = richEditorPattern->GetImageStyleBySpanItem(spanItem);
    EXPECT_NE(ret.size[RichEditorImageSize::SIZEHEIGHT], imageSizeOp->height->ConvertToPx());
}

/**
 * @tc.name: GetImageStyleBySpanItem003
 * @tc.desc: test GetImageStyleBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetImageStyleBySpanItem003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ImageSpanAttribute imageStyle;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    ImageSpanSize imageSize;
    imageSize.width = 1;
    imageStyle.size = imageSize;
    imageStyle.verticalAlign = VerticalAlign::TOP;
    imageStyle.objectFit = ImageFit::COVER;

    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ImageSpanOptions option;
    option.imageAttribute = imageStyle;
    spanItem->options = option;
    auto imageSizeOp = spanItem->options.imageAttribute->size;
    auto ret = richEditorPattern->GetImageStyleBySpanItem(spanItem);
    EXPECT_NE(ret.size[RichEditorImageSize::SIZEWIDTH], imageSizeOp->width->ConvertToPx());
}

/**
 * @tc.name: DeleteBackwardOperation002
 * @tc.desc: test DeleteBackwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, DeleteBackwardOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    richEditorPattern->caretPosition_ = 100;
    richEditorPattern->previewLongPress_ = true;
    richEditorNode_.Reset();
    auto ret = richEditorPattern->DeleteBackwardOperation(0);
    EXPECT_EQ(ret, u"");
}

/**
 * @tc.name: DeleteForwardOperation001
 * @tc.desc: test DeleteForwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, DeleteForwardOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t length = 1;
    AddSpan(EXCEPT_VALUE);
    richEditorNode_.Reset();
    auto ret = richEditorPattern->DeleteForwardOperation(length);
    EXPECT_EQ(ret, u"");
}

/**
 * @tc.name: DeleteForwardOperation002
 * @tc.desc: test DeleteForwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, DeleteForwardOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t length = 1;
    ClearSpan();
    richEditorPattern->caretPosition_ = 100;
    richEditorPattern->DeleteForwardOperation(length);
    EXPECT_TRUE(richEditorPattern->spans_.empty());
}
} // namespace OHOS::Ace::NG