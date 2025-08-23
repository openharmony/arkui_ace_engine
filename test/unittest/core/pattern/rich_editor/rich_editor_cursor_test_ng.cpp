/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorCursorTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<RichEditorPattern> GetRichEditorPattern();
    void InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr);
};

void RichEditorCursorTestNg::SetUp()
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

void RichEditorCursorTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorCursorTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorCursorTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

void RichEditorCursorTestNg::InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr)
{
    EXPECT_CALL(mockDataDetectorMgr, GetCursorPosition(_, _))
            .WillRepeatedly([](const std::string &text, int8_t offset) -> int8_t {
                if (text.empty()) {
                    return DEFAULT_RETURN_VALUE;
                }
                if (text.length() <= WORD_LIMIT_LEN) {
                    return WORD_LIMIT_RETURN;
                } else {
                    return BEYOND_LIMIT_RETURN;
                }
            });

    EXPECT_CALL(mockDataDetectorMgr, GetWordSelection(_, _))
            .WillRepeatedly([](const std::string &text, int8_t offset) -> std::vector<int8_t> {
                if (text.empty()) {
                    return std::vector<int8_t> { -1, -1 };
                }

                if (text.length() <= WORD_LIMIT_LEN) {
                    return std::vector<int8_t> { 2, 3 };
                } else {
                    return std::vector<int8_t> { 0, 2 };
                }
            });
}

/**
 * @tc.name: GetRightTextOfCursor001
 * @tc.desc: test GetRightTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, GetRightTextOfCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"tesol";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    auto ret = richEditorPattern->GetRightTextOfCursor(2);
    EXPECT_EQ(ret, u"ol");

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = richEditorPattern->GetRightTextOfCursor(2);
    EXPECT_EQ(ret, u"es");
}

/**
 * @tc.name: GetRightTextOfCursor002
 * @tc.desc: test get right text of cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, GetRightTextOfCursor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto ret = richEditorPattern->GetRightTextOfCursor(3);
    EXPECT_EQ(ret, u"hel");
}

/**
 * @tc.name: GetTextIndexAtCursor001
 * @tc.desc: test get text index at cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, GetTextIndexAtCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 3;
    EXPECT_EQ(richEditorPattern->GetTextIndexAtCursor(), 3);
}

/**
 * @tc.name: AdjustCursorPosition001
 * @tc.desc: test AdjustCursorPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, AdjustCursorPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);
    int32_t pos = 0;
    richEditorPattern->AdjustCursorPosition(pos);
    EXPECT_EQ(pos, 0);
}

/**
 * @tc.name: CursorMoveLineBegin001
 * @tc.desc: test CursorMoveLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveLineBegin001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    EXPECT_FALSE(richEditorPattern->CursorMoveLineBegin());
}

/**
 * @tc.name: CursorMoveToParagraphBegin001
 * @tc.desc: test CursorMoveToParagraphBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveToParagraphBegin001, TestSize.Level2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphBegin());
    AddSpan(TEST_INSERT_LINE_SEP);
    richEditorPattern->caretPosition_ = 1;
    EXPECT_TRUE(richEditorPattern->CursorMoveToParagraphBegin());
}

/**
 * @tc.name: CursorMoveToParagraphEnd001
 * @tc.desc: test CursorMoveToParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveToParagraphEnd001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphEnd());
}

/**
 * @tc.name: CalcCursorOffsetByPosition001
 * @tc.desc: test CalcCursorOffsetByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CalcCursorOffsetByPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    float selectLineHeight = 0;
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    AddSpan("test");
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    richEditorPattern->spans_.clear();
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    ASSERT_EQ(richEditorPattern->GetTextContentLength() == 0, true);
}

/**
 * @tc.name: CalcCursorOffsetByPosition002
 * @tc.desc: test CalcCursorOffsetByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CalcCursorOffsetByPosition002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    float selectLineHeight = 0;
    ClearSpan();
    AddSpan("test");
    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<SpanNode>(V2::IMAGE_ETS_TAG, -1);
    std::list<RefPtr<UINode>> child = { customNode };
    host->ModifyChildren() = child;
    int32_t position = 2;
    bool downStreamFirst = true;
    bool needLineHighest = true;
    auto startOffset = richEditorPattern->paragraphs_.ComputeCursorOffset(
        position, selectLineHeight, downStreamFirst, needLineHighest);
    auto offset =
        richEditorPattern->CalcCursorOffsetByPosition(position, selectLineHeight, downStreamFirst, needLineHighest);
    EXPECT_EQ(startOffset, offset);
}

/**
 * @tc.name: CalcCursorOffsetByPosition003
 * @tc.desc: test CalcCursorOffsetByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CalcCursorOffsetByPosition003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    float selectLineHeight = 0;
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);
    ASSERT_EQ(richEditorPattern->GetTextContentLength(), 0);
    AddSpan("hello1");
    ASSERT_NE(richEditorPattern->GetTextContentLength(), 0);
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);
    ASSERT_EQ(richEditorPattern->GetContentHost()->GetChildren().empty(), false);
}

/**
 * @tc.name: CursorMoveUp003
 * @tc.desc: test RichEditorPattern CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveUp003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. get richeditor pattern and add add text span
     */
    AddSpan("");
    richEditorPattern->CursorMoveUp();
    AddSpan("hello1");
    bool res = richEditorPattern->CursorMoveUp();
    res = richEditorPattern->CursorMoveDown();
    ASSERT_EQ(res, true);
}

/**
 * @tc.name: CursorMoveHome001
 * @tc.desc: test RichEditorPattern CursorMoveHome
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveHome001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    bool res = richEditorPattern->CursorMoveHome();
    ASSERT_EQ(res, false);
}

/**
 * @tc.name: CursorMoveLineEnd001
 * @tc.desc: test CursorMoveLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveLineEnd001, TestSize.Level1)
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
HWTEST_F(RichEditorCursorTestNg, CursorMoveLineEnd002, TestSize.Level1)
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
 * @tc.name: BeforeStatusCursorMove001
 * @tc.desc: test BeforeStatusCursorMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, BeforeStatusCursorMove001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);

    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->selectOverlayNode_ = overlayNode;
    richEditorPattern->textSelector_.Update(1, 2);
    EXPECT_FALSE(richEditorPattern->BeforeStatusCursorMove(true));
}

/**
 * @tc.name: CursorMoveEnd001
 * @tc.desc: test CursorMoveToParagraphBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveEnd001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphBegin());

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    EXPECT_TRUE(richEditorPattern->CursorMoveEnd());

    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    EXPECT_FALSE(richEditorPattern->CursorMoveEnd());
}

/**
 * @tc.name: CursorMoveUp001
 * @tc.desc: test CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveUp001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    EXPECT_TRUE(richEditorPattern->CursorMoveUp());
}

/**
 * @tc.name: CursorMoveUp002
 * @tc.desc: test CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveUp002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    OffsetF paintOffset = { -10, 1 };
    richEditorPattern->richTextRect_.SetOffset(paintOffset);
    EXPECT_TRUE(richEditorPattern->CursorMoveUp());
}

/**
 * @tc.name: CursorMoveDown001
 * @tc.desc: test CursorMoveDown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, CursorMoveDown001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    OffsetF paintOffset = { -10, 1 };
    richEditorPattern->richTextRect_.SetOffset(paintOffset);
    EXPECT_TRUE(richEditorPattern->CursorMoveDown());
}

/*
 * @tc.name: AdjustWordCursorAndSelect001
 * @tc.desc: test double click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, AdjustWordCursorAndSelect001, TestSize.Level1)
{
    using namespace std::chrono;
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(INIT_VALUE_1);
    int32_t pos = 3;

    MockDataDetectorMgr mockDataDetectorMgr;
    InitAdjustObject(mockDataDetectorMgr);

    richEditorPattern->lastAiPosTimeStamp_ = high_resolution_clock::now();
    richEditorPattern->lastClickTimeStamp_ = richEditorPattern->lastAiPosTimeStamp_ + seconds(2);
    int32_t spanStart = -1;
    std::string content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, 2);

    int32_t start = 1;
    int32_t end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 2);
    EXPECT_EQ(end, 3);

    AddSpan(INIT_VALUE_2);
    pos = 1;
    content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, 4);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 2);

    ClearSpan();
    pos = 2;
    content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, -1);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, -1);
    EXPECT_EQ(end, -1);
}

/*
 * @tc.name: AdjustWordCursorAndSelect001
 * @tc.desc: test double click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCursorTestNg, AdjustSelectorForEmoji001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ClearSpan();
    TextSpanOptions options = { .value = u"123👨‍👩‍👦‍👦456", .style = TEXT_STYLE_1 };
    richEditorPattern->AddTextSpan(options);
    int32_t index = 0;
    
    ParagraphManager::ParagraphInfo info;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    info.paragraph = mockParagraph;
    info.start = 0;
    info.end = 8;
    EXPECT_CALL(*mockParagraph, GetWordBoundary(_, _, _))
        .WillRepeatedly(Invoke([](int32_t index, int32_t& start, int32_t& end) -> bool {
            start = 3;
            end = 5;
            return true;
        }));
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    
    index = 4;
    richEditorPattern->AdjustSelectorForEmoji(index, HandleType::FIRST, SelectorAdjustPolicy::INCLUDE);
    EXPECT_EQ(index, 4);

    index = 4;
    richEditorPattern->AdjustSelectorForEmoji(index, HandleType::FIRST, SelectorAdjustPolicy::EXCLUDE);
    EXPECT_EQ(index, 4);

    index = 4;
    richEditorPattern->AdjustSelectorForEmoji(index, HandleType::SECOND, SelectorAdjustPolicy::INCLUDE);
    EXPECT_EQ(index, 4);

    index = 4;
    richEditorPattern->AdjustSelectorForEmoji(index, HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE);
    EXPECT_EQ(index, 4);
}

}