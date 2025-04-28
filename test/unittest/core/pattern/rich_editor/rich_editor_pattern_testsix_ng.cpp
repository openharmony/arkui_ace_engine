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
#include "test/mock/core/render/mock_canvas_image.h"
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
 * @tc.name: InsertValueInStyledString001
 * @tc.desc: test InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, InsertValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_3);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->InsertValueInStyledString(PREVIEW_TEXT_VALUE1);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
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
    newAddFrameNode->GetSpanItem()->content = INIT_VALUE_3;
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
 * @tc.name: ProcessInsertValue001
 * @tc.desc: test ProcessInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ProcessInsertValue001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string insertValue = u"abc";
    richEditorPattern->isEditing_ = true;
    richEditorPattern->isSpanStringMode_ = false;
    auto size = richEditorPattern->operationRecords_.size();
    richEditorPattern->ProcessInsertValue(insertValue, OperationType::IME, true);
    EXPECT_TRUE(richEditorPattern->IsEditing());
    EXPECT_NE(size, richEditorPattern->operationRecords_.size());
}

/**
 * @tc.name: GetRightWordPosition004
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetRightWordPosition004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "text";
    AddSpan(firstText);
    std::string space = " ";
    std::string secondText = "content";
    AddSpan(space + secondText);
    for (auto iter = richEditorPattern->spans_.cbegin(); iter != richEditorPattern->spans_.cend(); iter++) {
        auto span = *iter;
        span->placeholderIndex = 0;
    }
    int32_t initCaretPosition = firstText.size();
    auto position =
        std::clamp(initCaretPosition + 1, 0, static_cast<int32_t>(richEditorPattern->GetTextContentLength()));
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), position);
}

/**
 * @tc.name: GetRightWordPosition005
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetRightWordPosition005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "text ";
    AddSpan(firstText);
    std::string secondText = "content";
    AddSpan(secondText);
    for (auto iter = richEditorPattern->spans_.cbegin(); iter != richEditorPattern->spans_.cend(); iter++) {
        auto span = *iter;
        span->placeholderIndex = 0;
    }
    int32_t initCaretPosition = firstText.size() + secondText.size() - 1;
    auto position =
        std::clamp(initCaretPosition + 1, 0, static_cast<int32_t>(richEditorPattern->GetTextContentLength()));
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), position);
}

/**
 * @tc.name: MouseRightFocus002
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, MouseRightFocus002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = PREVIEW_TEXT_VALUE2;
    spanItem->spanItemType = SpanItemType::IMAGE;
    spanItem->position = 0;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    MouseInfo info;
    info.SetGlobalLocation({ 0, 0 });
    richEditorPattern->MouseRightFocus(info);
    EXPECT_NE(richEditorPattern->selectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: FromStyledString002
 * @tc.desc: test FromStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, FromStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    Selection selection;
    RefPtr<SpanString> spanString;
    spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    spanString->spans_.front() = nullptr;
    spanString->spans_.emplace_back();

    selection = richEditorPattern->FromStyledString(spanString).GetSelection();
    EXPECT_EQ(selection.selection[0], 0);
    EXPECT_EQ(selection.selection[1], 0);
}

/**
 * @tc.name: BeforeChangeText001
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, BeforeChangeText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    RichEditorPattern::OperationRecord operationRecord;
    OHOS::Ace::NG::RecordType recodrType = OHOS::Ace::NG::RecordType::DEL_BACKWARD;
    auto eventHub = richEditorNode_->GetOrCreateEventHub<RichEditorEventHub>();
    eventHub->SetOnDidChange([](const RichEditorChangeValue& value) -> bool { return false; });
    auto ret = richEditorPattern->BeforeChangeText(changeValue, operationRecord, recodrType, 100);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: BeforeChangeText002
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, BeforeChangeText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    TextSpanOptions options;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem);
    options.offset = -1;
    auto eventHub = richEditorNode_->GetOrCreateEventHub<RichEditorEventHub>();
    eventHub->SetOnDidChange([](const RichEditorChangeValue& value) -> bool { return false; });
    auto ret = richEditorPattern->BeforeChangeText(changeValue, options);
    EXPECT_FALSE(richEditorPattern->spans_.empty());
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: BeforeAddImage001
 * @tc.desc: test BeforeAddImage
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, BeforeAddImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    ImageSpanOptions options;
    auto eventHub = richEditorNode_->GetOrCreateEventHub<RichEditorEventHub>();
    eventHub->SetOnDidChange([](const RichEditorChangeValue& value) -> bool { return false; });
    auto ret = richEditorPattern->BeforeAddImage(changeValue, options, 100);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateChildrenOffset003
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, UpdateChildrenOffset003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.emplace_back();
    richEditorPattern->UpdateChildrenOffset();
    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: UpdateChildrenOffset004
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, UpdateChildrenOffset004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);

    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    richEditorPattern->isSpanStringMode_ = true;

    std::list<RefPtr<UINode>>& childrens = host->ModifyChildren();
    auto childNode2 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childrens.emplace_back(childNode2);

    richEditorPattern->UpdateChildrenOffset();
    EXPECT_TRUE(childNode2->GetSpanItem());
}

/**
 * @tc.name: UpdateChildrenOffset005
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, UpdateChildrenOffset005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);

    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->isSpanStringMode_ = true;

    std::list<RefPtr<UINode>>& childrens = host->ModifyChildren();
    auto childNode2 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childNode2->imageSpanItem_ = nullptr;
    childrens.emplace_back(childNode2);

    richEditorPattern->UpdateChildrenOffset();
    EXPECT_FALSE(childNode2->GetSpanItem());
}

/**
 * @tc.name: CursorMoveLineEnd001
 * @tc.desc: test CursorMoveLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, CursorMoveLineEnd001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->CursorMoveLineEnd();
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: CursorMoveLineEnd002
 * @tc.desc: test CursorMoveLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, CursorMoveLineEnd002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->CursorMoveLineEnd();
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: HandleKbVerticalSelection003
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleKbVerticalSelection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    options.value = TEST_INSERT_VALUE;
    richEditorPattern->AddTextSpan(options);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 0;

    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(false), 1);
}

/**
 * @tc.name: HandleKbVerticalSelection004
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleKbVerticalSelection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretPosition_ = 0;

    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(false), 0);
}

/**
 * @tc.name: HandleKbVerticalSelection005
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleKbVerticalSelection005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;

    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(false), 0);
}

/**
 * @tc.name: CopyGestureOption002
 * @tc.desc: test CopyGestureOption
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, CopyGestureOption002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanNode> source = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    RefPtr<SpanNode> target = OHOS::Ace::NG::SpanNode::CreateSpanNode(2);
    GestureEventFunc func1 = [](GestureEvent& info) {};
    OnHoverFunc func2 = [](bool, HoverInfo& info) {};
    source->GetSpanItem()->SetOnClickEvent(std::move(func1));
    source->GetSpanItem()->SetLongPressEvent(std::move(func1));
    source->GetSpanItem()->SetDoubleClickEvent(std::move(func1));
    source->GetSpanItem()->SetHoverEvent(std::move(func2));
    richEditorPattern->CopyGestureOption(source, target);
    EXPECT_TRUE(target->GetSpanItem()->onDoubleClick);
    EXPECT_TRUE(target->GetSpanItem()->onHover);
}

/**
 * @tc.name: GetSameSpanItem001
 * @tc.desc: test GetSameSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetSameSpanItem001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->spanItemType = SpanItemType::IMAGE;
    auto childNode = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childNode->imageSpanItem_ = spanItem;
    richEditorNode_->children_.emplace_back(childNode);
    auto image = AceType::MakeRefPtr<MockCanvasImage>();
    auto imageNode = richEditorPattern->GetImageSpanNodeBySpanItem(spanItem);
    auto pattern = imageNode->GetPattern<ImagePattern>();
    pattern->image_ = image;
    auto pixelMap = image->GetPixelMap();
    richEditorPattern->GetSameSpanItem(spanItem);
    EXPECT_FALSE(pixelMap);
}

/**
 * @tc.name: GetSameSpanItem002
 * @tc.desc: test GetSameSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, GetSameSpanItem002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->spanItemType = SpanItemType::IMAGE;
    auto childNode = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childNode->imageSpanItem_ = spanItem;
    richEditorNode_->children_.emplace_back(childNode);
    auto image = AceType::MakeRefPtr<MockCanvasImage>();
    image->needPixelMap = true;
    auto imageNode = richEditorPattern->GetImageSpanNodeBySpanItem(spanItem);
    auto pattern = imageNode->GetPattern<ImagePattern>();
    pattern->image_ = image;
    auto pixelMap = image->GetPixelMap();
    richEditorPattern->GetSameSpanItem(spanItem);
    EXPECT_TRUE(pixelMap);
}

} // namespace OHOS::Ace::NG
