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
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

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
 * @tc.name: HandleUserTouchEvent001
 * @tc.desc: test HandleUserTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, HandleUserTouchEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    bool isTouchTrigger = false;
    firstSpanItem->onTouch = [&isTouchTrigger](TouchEventInfo& info) { isTouchTrigger = true; };
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    TouchEventInfo info = TouchEventInfo("default");
    TouchLocationInfo locationInfo = TouchLocationInfo(0);
    locationInfo.SetLocalLocation(Offset(3, 3));
    info.AddTouchLocationInfo(std::move(locationInfo));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    richEditorPattern->HandleUserTouchEvent(info);
    EXPECT_TRUE(isTouchTrigger);
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
 * @tc.name: MouseRightFocus003
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, MouseRightFocus003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = PREVIEW_TEXT_VALUE2;
    spanItem->spanItemType = SpanItemType::NORMAL;
    spanItem->position = 0;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->spans_.push_back(spanItem);
    MouseInfo info;
    info.SetGlobalLocation({ 0, 0 });
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->previewLongPress_ = true;
    focusHub->RequestFocusImmediately();
    EXPECT_EQ(richEditorPattern->isEditing_, false);
    richEditorPattern->MouseRightFocus(info);
    EXPECT_EQ(richEditorPattern->isEditing_, true);
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
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
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
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
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
 * @tc.name: ReportAfterContentChangeEvent001
 * @tc.desc: Test ReportAfterContentChangeEvent non-span string mode with content added
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ReportAfterContentChangeEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "abcd";
    AddSpan(firstText);
    std::string space = " ";
    std::string secondText = "content";
    AddSpan(space + secondText);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->textCache_ = "abcd";
    richEditorPattern->ReportAfterContentChangeEvent();
    EXPECT_EQ(richEditorPattern->textCache_, "abcd content");
}

/**
 * @tc.name: ReportAfterContentChangeEvent002
 * @tc.desc: Test ReportAfterContentChangeEvent in span mode with content removed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ReportAfterContentChangeEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textCache_ = "nihaodajia";
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(PREVIEW_TEXT_VALUE1);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->ReportAfterContentChangeEvent();
    EXPECT_EQ(richEditorPattern->textCache_, "nihao");
}

/**
 * @tc.name: ReportAfterContentChangeEvent003
 * @tc.desc: Test ReportAfterContentChangeEvent non-span string mode with content modified
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSixNg, ReportAfterContentChangeEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "abcd";
    AddSpan(firstText);
    std::string space = " ";
    std::string secondText = "content";
    AddSpan(space + secondText);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->textCache_ = "abcdefg";
    richEditorPattern->ReportAfterContentChangeEvent();
    EXPECT_EQ(richEditorPattern->textCache_, "abcd content");
}
} // namespace OHOS::Ace::NG
