/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::u16string TEST_INSERT_LINE_SPACE = u" ";
} // namespace


class RichEditorSelectActionTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<RichEditorPattern> GetRichEditorPattern();
    static void TearDownTestSuite();
};

void RichEditorSelectActionTestNg::SetUp()
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

void RichEditorSelectActionTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorSelectActionTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorSelectActionTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: GetAdjustedSelectionInfo001
 * @tc.desc: test GetAdjustedSelectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetAdjustedSelectionInfo001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::vector<std::tuple<SelectSpanType, std::u16string, RefPtr<PixelMap>>> testTuples;
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u" ", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u"", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u" ", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPEIMAGE, u"", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u" ", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u"", PixelMap::CreatePixelMap(nullptr));
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u" ", nullptr);
    testTuples.emplace_back(SelectSpanType::TYPESYMBOLSPAN, u"", nullptr);
    std::list<ResultObject> resultObjectList;
    ResultObject obj;
    for (const auto& testcase : testTuples) {
        obj.type = std::get<0>(testcase);
        obj.valueString = std::get<1>(testcase);
        obj.valuePixelMap = std::get<2>(testcase);
        resultObjectList.emplace_back(obj);
    }

    SelectionInfo textSelectInfo;
    textSelectInfo.SetResultObjectList(resultObjectList);
    auto adjustedInfo = richEditorPattern->GetAdjustedSelectionInfo(textSelectInfo);
    EXPECT_FALSE(adjustedInfo.GetSelection().resultObjects.empty());
}

/**
 * @tc.name: GetSelectSpanSplit001
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectSpanSplit001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto newPlusFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newPlusFrameNode);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    EXPECT_TRUE(richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo).empty());
}

/**
 * @tc.name: GetSelectSpanSplit002
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectSpanSplit002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::RICH_EDITOR_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: GetSelectSpanSplit003
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectSpanSplit003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorNode_->children_.push_back(spanNode);
    richEditorNode_->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.front().spanIndex, 0);
}

/**
 * @tc.name: GetSelectSpanSplit004
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectSpanSplit004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    startPositionSpanInfo.spanOffset_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetSelectSpanSplit005
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectSpanSplit005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    contentNode->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: GetSelectSpanSplit006
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectSpanSplit006, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    contentNode->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 1;
    endPositionSpanInfo.spanOffset_ = 1;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: GetSelectSpanSplit007
 * @tc.desc: test GetSelectSpanSplit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectSpanSplit007, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeNew = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    auto spanNodeAnother = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    contentNode->children_.push_back(spanNode);
    contentNode->children_.push_back(spanNodeNew);
    contentNode->children_.push_back(spanNodeAnother);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startPositionSpanInfo;
    SpanPositionInfo endPositionSpanInfo;
    endPositionSpanInfo.spanIndex_ = 2;
    auto result = richEditorPattern->GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    EXPECT_EQ(result.size(), 3);
}

/**
 * @tc.name: HandleSelect001
 * @tc.desc: test HandleSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, HandleSelect001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    richEditorPattern->HandleSelect(CaretMoveIntent::Home);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), richEditorPattern->textSelector_.GetStart());
}

/**
 * @tc.name: HandleSelect002
 * @tc.desc: test HandleSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, HandleSelect002, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    int32_t selectStart = 0;
    int32_t selectEnd = 2;
    SelectOverlayInfo selectInfo;
    auto pipeline = richEditorNode_->GetContext();
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    selectOverlayManager->selectOverlayInfo_.isUsingMouse = true;
    richEditorPattern->HandleSelect(info, selectStart, selectEnd);
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: HandleSelect003
 * @tc.desc: test HandleSelect(Ctrl+Shift+Up/Down)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, HandleSelect003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // Init paragraphs with test content
    std::vector<std::u16string> initValues = { INIT_VALUE_1, INIT_VALUE_2, INIT_VALUE_3 };
    ParagraphManager::ParagraphInfo info;
    for (const auto& value : initValues) {
        auto insertValue = value + TEST_INSERT_LINE_SEP;
        AddSpan(insertValue);
        info.start = info.end;
        info.end = info.start + insertValue.length();
        info.paragraph = AceType::MakeRefPtr<MockParagraph>();
        richEditorPattern->paragraphs_.paragraphs_.emplace_back(info);
    }

    // caret at paragraph start
    richEditorPattern->caretPosition_ = 7;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 7);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 7);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 7);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 7);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);

    // caret in paragraph middle
    richEditorPattern->ResetSelection();
    richEditorPattern->caretPosition_ = 11;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 11);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 7);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 11);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);

    // caret at paragraph end
    richEditorPattern->ResetSelection();
    richEditorPattern->caretPosition_ = 13;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 13);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 7);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 13);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);

    // during preview text input
    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 13);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 14);
}

/**
 * @tc.name: TripleClickSection001
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, TripleClickSection001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    GestureEvent info = GestureEvent();
    info.sourceTool_ = SourceTool::FINGER;
    richEditorPattern->TripleClickSection(info, 1, 10, 2);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection002
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, TripleClickSection002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    GestureEvent info = GestureEvent();
    info.sourceTool_ = SourceTool::FINGER;
    richEditorPattern->TripleClickSection(info, 10, 10, 2);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection003
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, TripleClickSection003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection004
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, TripleClickSection004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection005
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, TripleClickSection005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 5, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: UpdateSelectionType
 * @tc.desc: test UpdateSelectionType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, UpdateSelectionType, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectionInfo textSelectInfo;
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);
    richEditorPattern->UpdateSelectionType(textSelectInfo);
    EXPECT_EQ(richEditorPattern->selectedType_, TextSpanType::NONE);
}

/**
 * @tc.name: FireOnSelectionChange001
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, FireOnSelectionChange001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = true;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange002
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, FireOnSelectionChange002, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange003
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, FireOnSelectionChange003, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = false;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_TRUE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: GetRectsForRange001
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetRectsForRange001, TestSize.Level0)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;

    int32_t start = 0;
    int32_t end = 10;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());

    start = -5;
    end = 10;
    result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());

    start = 0;
    end = -5;
    result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());

    start = 10;
    end = 0;
    result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: HandleKbVerticalSelection001
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, HandleKbVerticalSelection001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
    richEditorPattern->caretPosition_ = 0;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
}

/**
 * @tc.name: HandleKbVerticalSelection002
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, HandleKbVerticalSelection002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->caretPosition_ = 1;
    EXPECT_EQ(richEditorPattern->HandleKbVerticalSelection(true), 0);
}

/**
 * @tc.name: HandleKbVerticalSelection003
 * @tc.desc: test HandleKbVerticalSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, HandleKbVerticalSelection003, TestSize.Level0)
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
HWTEST_F(RichEditorSelectActionTestNg, HandleKbVerticalSelection004, TestSize.Level0)
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
HWTEST_F(RichEditorSelectActionTestNg, HandleKbVerticalSelection005, TestSize.Level0)
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
 * @tc.name: CalculateTruncationLength001
 * @tc.desc: test CalculateTruncationLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, CalculateTruncationLength001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    std::string insertValue = "hello";
    int32_t start = 2;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 4;
    int32_t length = richEditorPattern->CalculateTruncationLength(StringUtils::Str8ToStr16(insertValue), start);
    EXPECT_EQ(length, 4);
}

/**
 * @tc.name: CalculateTruncationLength002
 * @tc.desc: test CalculateTruncationLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, CalculateTruncationLength002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    std::string insertValue = "hello";
    int32_t start = 2;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    int32_t length = richEditorPattern->CalculateTruncationLength(StringUtils::Str8ToStr16(insertValue), start);
    EXPECT_EQ(length, 2);
}

/**
 * @tc.name: GetSpanRangeByResultObject001
 * @tc.desc: test GetSpanRangeByResultObject function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSpanRangeByResultObject001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto rangeStart = 1;
    SpanPosition spanPosition;
    spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = rangeStart;
    ResultObject result;
    result.spanPosition = spanPosition;
    result.offsetInSpan[0] = 1;
    result.offsetInSpan[1] = 2;
    auto [selectStartResult, selectEndResult] = richEditorPattern->GetSpanRangeByResultObject(result);
    auto selectStart = 2;
    auto selectEnd = 3;
    EXPECT_EQ(selectStart, selectStartResult);
    EXPECT_EQ(selectEnd, selectEndResult);
}

/**
 * @tc.name: GetSpanRangeByResultObject002
 * @tc.desc: test GetSpanRangeByResultObject function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSpanRangeByResultObject002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPosition spanPosition;
    ResultObject result;
    result.spanPosition = spanPosition;
    result.offsetInSpan[0] = 1;
    result.offsetInSpan[1] = 2;
    auto [selectStartResult, selectEndResult] = richEditorPattern->GetSpanRangeByResultObject(result);
    auto selectStart = 1;
    auto selectEnd = 2;
    EXPECT_EQ(selectStart, selectStartResult);
    EXPECT_EQ(selectEnd, selectEndResult);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility001
 * @tc.desc: test UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, UpdateSelectionAndHandleVisibility001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->sourceTool_ = SourceTool::MOUSE;
    richEditorPattern->releaseInDrop_ = true;
    AddSpan("test--test");

    richEditorPattern->textSelector_.Update(5, 10);
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->insertValueLength_ = 5;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->UpdateSelectionAndHandleVisibility();
    ASSERT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    ASSERT_EQ(richEditorPattern->textSelector_.destinationOffset, 5);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility002
 * @tc.desc: test UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, UpdateSelectionAndHandleVisibility002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->sourceTool_ = SourceTool::MOUSE;
    richEditorPattern->releaseInDrop_ = true;
    AddSpan("test--test");

    richEditorPattern->textSelector_.Update(5, 10);
    richEditorPattern->lastCaretPosition_ = 5;
    richEditorPattern->insertValueLength_ = 5;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->UpdateSelectionAndHandleVisibility();
    ASSERT_EQ(richEditorPattern->textSelector_.baseOffset, 5);
    ASSERT_EQ(richEditorPattern->textSelector_.destinationOffset, 10);
}

/**
 * @tc.name: GetSelectArea001
 * @tc.desc: test GetSelectArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSelectArea001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };
    richEditorPattern->isShowPlaceholder_ = true;
    auto res = richEditorPattern->GetSelectArea(SelectRectsType::ALL_LINES);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::LEFT_TOP_POINT);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::RIGHT_BOTTOM_POINT);
    EXPECT_TRUE(res.IsValid());
}

/**
 * @tc.name: RichEditorController006
 * @tc.desc: test get span info
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, GetSpansInfo001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    auto info1 = richEditorController->GetSpansInfo(1, 10);
    EXPECT_EQ(info1.selection_.selection[0], 1);
    EXPECT_EQ(info1.selection_.selection[1], 10);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 3);
    auto info2 = richEditorController->GetSpansInfo(10, 1);
    EXPECT_EQ(info2.selection_.selection[0], 1);
    EXPECT_EQ(info2.selection_.selection[1], 10);
    auto info3 = richEditorController->GetSpansInfo(-1, 10);
    EXPECT_EQ(info3.selection_.selection[0], 0);
    EXPECT_EQ(info3.selection_.selection[1], 10);
    auto info4 = richEditorController->GetSpansInfo(1, -10);
    EXPECT_EQ(info4.selection_.selection[0], 0);
    EXPECT_EQ(info4.selection_.selection[1], 1);
}

/**
 * @tc.name: DeleteByRange001
 * @tc.desc: test DeleteByRange func
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, DeleteByRange001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    richEditorPattern->previewTextRecord_.needReplacePreviewText = true;
    richEditorPattern->previewTextRecord_.newPreviewContent = u"";
    richEditorPattern->previewTextRecord_.previewContent = INIT_VALUE_1;
    richEditorPattern->lastSelectionRange_ = { -1, -1 };
    auto value = richEditorPattern->lastSelectionRange_;
    richEditorPattern->DeleteByRange(nullptr, 1, 2);
    EXPECT_TRUE(value == richEditorPattern->lastSelectionRange_);
}

/**
 * @tc.name: MarkContentNodeForRender001
 * @tc.desc: test MarkContentNodeForRender func
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSelectActionTestNg, MarkContentNodeForRender001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->MarkContentNodeForRender();
    auto paintProp = richEditorNode_->GetPaintProperty<NG::Property>();
    ASSERT_TRUE(paintProp);
    auto changeFlag = paintProp->GetPropertyChangeFlag() | NG::PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(paintProp->GetPropertyChangeFlag(), changeFlag);
}
} // namespace OHOS::Ace::NG